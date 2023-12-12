#include "view.h"
#include "./ui_view.h"

#include <QScrollBar>

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
