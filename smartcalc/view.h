#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Controller &controller, QWidget *parent = nullptr);
    ~View();

private slots:
    void runCalc();
    void chooseItem(QListWidgetItem *item);
    void plot();
    void Credit(void);

private:
    Controller &controller;
    Ui::View *ui;
};
#endif // VIEW_H
