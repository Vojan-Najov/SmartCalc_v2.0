#include "view.h"
#include "./ui_view.h"

#include <QScrollBar>
#include <QChart>
#include <QLineSeries>

#include "credit_table.h"

View::View(Controller &controller, QWidget *parent)
    : QMainWindow(parent)
    , controller(controller)
    , ui(new Ui::View)
{
    QLocale::setDefault(QLocale::c());
    ui->setupUi(this);
    setWindowTitle("Smartcalc-v2.0");

    connect(ui->runButton, &QPushButton::clicked, this, &View::runCalc);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &View::runCalc);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &View::chooseItem);
    connect(ui->plotButton, &QPushButton::clicked, this, &View::plot);
    connect(ui->creditPushButton, &QPushButton::clicked, this, &View::Credit);

    const QStringList &lst = controller.getFuncNames();
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
        ui->comboBox->addItem(*it);
    }

    ui->creditTermComboBox->addItem("month");
    ui->creditTermComboBox->addItem("year");
    ui->creditTypeComboBox->addItem("annuity");
    ui->creditTypeComboBox->addItem("differentiated");
}

View::~View()
{
    delete ui;
}

void View::runCalc() {
    QString expr = ui->lineEdit->text().trimmed();
    ui->lineEdit->clear();
    if (expr.isEmpty()) {
        return;
    }

    QString answer = controller.calc(expr);
    ui->listWidget->addItem(QString(">") + expr);
    ui->listWidget->addItem(answer);
    if (answer.startsWith("func")) {
        ui->comboBox->addItem(*++answer.split(' ').begin());
        //ui->comboBox->addItem(expr);
    }

    QScrollBar *bar = ui->listWidget->verticalScrollBar();
    bar->setMaximum(bar->maximum() + 4 * ui->listWidget->fontInfo().pixelSize());
    bar->setValue(bar->maximum());

    ui->lineEdit->clear();

}

void View::chooseItem(QListWidgetItem *item)
{
    QString str = item->text();
    if (str.front() == '>') {
        str.remove(0, 1);
    }
    ui->lineEdit->setText(str);
}

void View::plot()
{
    ui->statusbar->clearMessage();

    QString funcname = ui->comboBox->currentText();
    double emin = ui->emin->value();
    double emax = ui->emax->value();
    double dmin = ui->dmin->value();
    double dmax = ui->dmax->value();

    if (!(dmin < dmax && emin < emax)) {
        ui->statusbar->showMessage("Incorrect rages");
        return;
    }

    qDebug() << "start";
    std::vector<std::pair<double, double>> plot = controller.getPlot(funcname, emin, emax, dmin, dmax);
    if (plot.empty()) {
        ui->statusbar->showMessage("Plot error");
        return;
    }
    qDebug() << "have vector";

    QChart *chart = new QChart{};
    chart->legend()->hide();

    QLineSeries *series = new QLineSeries{};
    bool flag = false;
    for (auto it = plot.cbegin(); it != plot.cend(); ++it) {
        if (std::isnan(it->second)) {
            qDebug() << "new series";
            if (flag) {
                chart->addSeries(series);
                series = new QLineSeries{};
                chart->createDefaultAxes();
                flag = false;
            }
            continue;
        }
        *series << QPointF(it->first, it->second);
        flag = true;

    }
    qDebug() << "have series";
    // QChart *chart = new QChart{};

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(dmin, dmax);
    chart->axes(Qt::Vertical).first()->setRange(emin, emax);
    chart->setTitle(funcname + "(x)");
    qDebug() << "have chart";
    ui->graphicsView->setChart(chart);
    qDebug() << "end";
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

    CreditTable tab = controller.CalcCredit(total, term, rate, isDifferentiated);

    for (int i = 0; i < term; ++i) {
        table->setItem(i, 0, new QTableWidgetItem(tab.GetStringMonthlyPayment(i)));
        table->setItem(i, 1, new QTableWidgetItem(tab.GetStringPrincipalPayment(i)));
        table->setItem(i, 2, new QTableWidgetItem(tab.GetStringInterestPayment(i)));
        table->setItem(i, 3, new QTableWidgetItem(tab.GetStringBalanceOwed(i)));
    }
    table->setItem(term, 0, new QTableWidgetItem(tab.GetStringTotalPayment()));
    table->setItem(term, 1, new QTableWidgetItem(tab.GetStringTotalPrincipalPayment()));
    table->setItem(term, 2, new QTableWidgetItem(tab.GetStringTotalInterestPayment()));
}
