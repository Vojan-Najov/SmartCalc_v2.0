#include "view.h"

#include <QScrollBar>

#include "./ui_view.h"
#include "credit_table.h"

View::View(s21::Controller &controller, QWidget *parent)
    : QMainWindow(parent), controller(controller), ui(new Ui::View) {
  ui->setupUi(this);
  setWindowTitle("Smartcalc-v2.0");

  connect(ui->calcPushButton, &QPushButton::clicked, this, &View::Calc);
  connect(ui->calcLineEdit, &QLineEdit::returnPressed, this, &View::Calc);
  connect(ui->creditPushButton, &QPushButton::clicked, this, &View::Credit);
  connect(ui->plotButton, &QPushButton::clicked, this, &View::ConstructPlot);
  connect(ui->calcListWidget, &QListWidget::itemClicked, this,
          &View::CalcChooseItem);

  StringList lst = controller.GetFuncNames();
  for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
    ui->plotComboBox->addItem(it->c_str());
  }

  ui->creditTermComboBox->addItem("month");
  ui->creditTermComboBox->addItem("year");
  ui->creditTypeComboBox->addItem("annuity");
  ui->creditTypeComboBox->addItem("differentiated");
}

View::~View() { delete ui; }

void View::Calc() {
  QString expr = ui->calcLineEdit->text().trimmed();
  ui->calcLineEdit->clear();
  if (expr.isEmpty()) {
    return;
  }

  QString answer = controller.CalculateExpression(expr);
  ui->calcListWidget->addItem(QString(">") + expr);
  ui->calcListWidget->addItem(answer);

  QScrollBar *bar = ui->calcListWidget->verticalScrollBar();
  bar->setMaximum(bar->maximum() +
                  4 * ui->calcListWidget->fontInfo().pixelSize());
  bar->setValue(bar->maximum());

  if (answer.startsWith("func")) {
    ui->plotComboBox->clear();
    StringList lst = controller.GetFuncNames();
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
      ui->plotComboBox->addItem(it->c_str());
    }
  }
}

void View::CalcChooseItem(QListWidgetItem *item) {
  QString str = item->text();
  if (str.front() == '>') {
    str.remove(0, 1);
  }
  ui->calcLineEdit->setText(str);
}

void View::InitChart(QChart *chart, QString title, QValueAxis *axisX,
                     QValueAxis *axisY) const {
  chart->legend()->hide();
  chart->setTitle(title);
  chart->addAxis(axisX, Qt::AlignBottom);
  chart->addAxis(axisY, Qt::AlignLeft);
}

void View::ConstructPlot(void) {
  ui->statusbar->clearMessage();

  QString funcname = ui->plotComboBox->currentText();
  double dmin = ui->dmin->value();
  double dmax = ui->dmax->value();
  double emin = ui->emin->value();
  double emax = ui->emax->value();

  if (!CheckRanges(dmin, dmax, emin, emax)) {
    return;
  }

  Plot plot = controller.GetPlot(funcname, dmin, dmax, emin, emax);

  QValueAxis *axisX = new QValueAxis{};
  InitAxis(axisX, "X", 11, {dmin, dmax});
  QValueAxis *axisY = new QValueAxis{};
  InitAxis(axisY, "Y", 11, {emin, emax});

  QChart *chart = new QChart{};
  InitChart(chart, funcname + "(x)", axisX, axisY);

  QLineSeries *series = new QLineSeries{};
  bool series_filled = false;
  for (Plot::iterator it = plot.begin(), last = plot.end(); it != last; ++it) {
    double x = it->first, y = it->second;
    if (std::isnan(y)) {
      if (series_filled) {
        AddSeriesToChart(chart, series, axisX, axisY);
        series = new QLineSeries{};
        series_filled = false;
      }
    } else {
      *series << QPointF(x, y);
      series_filled = true;
    }
  }
  if (series_filled) {
    AddSeriesToChart(chart, series, axisX, axisY);
  }

  ui->graphicsView->setChart(chart);
}

void View::Credit(void) {
  double total = ui->creditTotalSpinBox->value();
  size_t term = ui->creditTermSpinBox->value();
  if (ui->creditTermComboBox->currentText() == "year") {
    term *= 12;
  }
  double rate = ui->creditRateSpinBox->value();
  bool isDifferentiated = false;
  if (ui->creditTypeComboBox->currentText() == "differentiated") {
    isDifferentiated = true;
  }

  QTableWidget *table = ui->creditTableWidget;
  table->clearContents();
  table->setRowCount(term + 1);

  s21::CreditTable tab =
      controller.CalcCredit(total, term, rate, isDifferentiated);

  for (int i = 0; i < term; ++i) {
    table->setItem(i, 0, new QTableWidgetItem(tab.GetStringMonthlyPayment(i)));
    table->setItem(i, 1,
                   new QTableWidgetItem(tab.GetStringPrincipalPayment(i)));
    table->setItem(i, 2, new QTableWidgetItem(tab.GetStringInterestPayment(i)));
    table->setItem(i, 3, new QTableWidgetItem(tab.GetStringBalanceOwed(i)));
  }
  table->setItem(term, 0, new QTableWidgetItem(tab.GetStringTotalPayment()));
  table->setItem(term, 1,
                 new QTableWidgetItem(tab.GetStringTotalPrincipalPayment()));
  table->setItem(term, 2,
                 new QTableWidgetItem(tab.GetStringTotalInterestPayment()));
}

bool View::CheckRanges(double dmin, double dmax, double emin,
                       double emax) const {
  if (!(dmin < dmax && emin < emax)) {
    ui->statusbar->showMessage("Incorrect rages");
    return false;
  }
  if (dmax - dmin > 100.0) {
    ui->statusbar->showMessage(
        "A range greater than 100 for the function definition area is not "
        "supported.");
    return false;
  }
  if (emax - emin > 100.0) {
    ui->statusbar->showMessage(
        "A range greater than 100 for the function value area is not "
        "supported.");
    return false;
  }
  return true;
}

void View::InitAxis(QValueAxis *axis, QString title, size_t tick_count,
                    std::pair<double, double> range) const {
  axis->setTitleText(title);
  axis->setTickCount(11);
  axis->setRange(range.first, range.second);
}

void View::AddSeriesToChart(QChart *chart, QLineSeries *series,
                            QValueAxis *axisX, QValueAxis *axisY) const {
  chart->addSeries(series);
  series->attachAxis(axisX);
  series->attachAxis(axisY);
}
