#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "model.h"

class Controller
{
public:
    Controller(Model *model);

public:
    QString calc(QString expr);
    const QStringList &getFuncNames(void);
    std::vector<std::pair<double, double>> getPlot(const QString &funcname,
                                                   double emin, double emax,
                                                   double dmin, double dmax);
    QString calcCredit(double total, unsigned int term, double rate, bool isDifferentiated);

private:
    Model *model;
};

#endif // CONTROLLER_H
