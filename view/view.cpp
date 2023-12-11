#include "view.h"
#include "./ui_view.h"

#include <QScrollBar>

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    setWindowTitle(QString("Smartcalc-v2.0"));
    QLocale::setDefault(QLocale("C"));

    connect(ui->runButton, &QPushButton::clicked, this, &View::run);
}

View::~View()
{
    delete ui;
}


void View::run()
{
    ui->listWidget->addItem(QString(">") + ui->lineEdit->text());
    QString answer{QString::fromLatin1("123")};
    ui->listWidget->addItem(answer);
    //controller.calculate(ui->lineEdit->text().toLatin1()));

    QScrollBar *bar = ui->listWidget->verticalScrollBar();
    bar->setMaximum(bar->maximum() + 4 * ui->listWidget->fontInfo().pixelSize());
    bar->setValue(bar->maximum());

    ui->lineEdit->clear();
}

