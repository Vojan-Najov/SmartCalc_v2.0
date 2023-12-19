#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "model.h"
#include "credit_table.h"

class Controller
{
public:
    using StringList = Model::StringList;
    using Plot = Model::Plot;
public:
    Controller(Model &model);

public:
    QString CalculateExpression(QString expr);
    Plot GetPlot(const QString &funcname, double dmin, double dmax, double emin, double emax);

public:
    StringList GetFuncNames(void) const;
    CreditTable CalcCredit(double total, size_t term, double rate, bool isDifferentiated) const;

private:
    Model &model;
};

#endif // CONTROLLER_H
