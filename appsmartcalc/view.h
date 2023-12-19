#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QValueAxis>
#include <QChart>
#include <QLineSeries>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    using StringList = Controller::StringList;
    using Plot = Controller::Plot;
public:
    View(Controller &controller, QWidget *parent = nullptr);
    ~View();

private slots:
    void Calc(void);
    void CalcChooseItem(QListWidgetItem *item);
    void ConstructPlot();
    void Credit(void);

private:
    bool CheckRanges(double dmin, double dmax, double emin, double emax) const;
    void InitAxis(QValueAxis *axis, QString title, size_t tick_count, std::pair<double, double> range) const;
    void InitChart(QChart *chart, QString title, QValueAxis *axisX, QValueAxis *axisY) const;
    void AddSeriesToChart(QChart *chart, QLineSeries *series, QValueAxis *axisX, QValueAxis *axisY) const;

private:
    Controller &controller;
    Ui::View *ui;
};
#endif // VIEW_H
