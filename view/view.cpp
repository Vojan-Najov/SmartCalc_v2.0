#include "view.h"
#include "./ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    setWindowTitle(QString("Smartcalc-v2.0"));
}

View::~View()
{
    delete ui;
}

