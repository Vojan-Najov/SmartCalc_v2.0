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

    const QStringList &lst = controller->getFuncNames();
    for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
        ui->comboBox->addItem(*it);
    }
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

    QLineSeries *series = new QLineSeries{};
    for (auto it = plot.cbegin(); it != plot.cend(); ++it) {
        *series << QPointF(it->first, it->second);
    }
    qDebug() << "have series";
    QChart *chart = new QChart{};
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(dmin, dmax);
    chart->axes(Qt::Vertical).first()->setRange(emin, emax);
    chart->setTitle(funcname + "(x)");
    qDebug() << "have chart";
    ui->graphicsView->setChart(chart);
    qDebug() << "end";
}
