#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "model.h"
#include "credit_table.h"

class Controller
{
public:
    Controller(Model &model);

public:
    QString CalculateExpression(QString expr);

    std::vector<std::pair<double, double>> getPlot(const QString &funcname,
                                                   double emin, double emax,
                                                   double dmin, double dmax);

public:
    const QStringList &GetFuncNames(void) const;
    CreditTable CalcCredit(double total, size_t term, double rate, bool isDifferentiated) const;

private:
    Model &model;
};

#endif // CONTROLLER_H
