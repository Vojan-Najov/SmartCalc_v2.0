#include "view.h"
#include "./ui_view.h"

#include <QScrollBar>
#include <QChart>
#include <QLineSeries>

View::View(Controller *controller, QWidget *parent)
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
    connect(ui->creditPushButton, &QPushButton::clicked, this, &View::credit);

    const QStringList &lst = controller->getFuncNames();
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

    QString answer = controller->calc(expr);
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
    std::vector<std::pair<double, double>> plot = controller->getPlot(funcname, emin, emax, dmin, dmax);
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

void View::credit()
{
    QString info{};

    double total = ui->creditTotalSpinBox->value();
    info = "Total: " + ui->creditTotalSpinBox->textFromValue(total);

    unsigned int term = ui->creditTermSpinBox->value();
    if (ui->creditTermComboBox->currentText() == "year") {
        term *= 12;
    }
    info += ", term: " + ui->creditTermSpinBox->text() + " " + ui->creditTermComboBox->currentText();

    double rate = ui->creditRateSpinBox->value();
    info += ", rate: " + ui->creditRateSpinBox->textFromValue(rate);

    bool isDifferentiated = false;
    if (ui->creditTypeComboBox->currentText() == "differentiated") {
        isDifferentiated = true;
    }
    info += ", type: " + ui->creditTypeComboBox->currentText();

    ui->creditListWidget->addItem(info);
    ui->creditListWidget->addItem(controller->calcCredit(total, term, rate, isDifferentiated));

    // auto CreditTable = controller->calcCredit(total, term, rate, isDiffertiated)
}
