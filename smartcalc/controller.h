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
    QString calc(QString expr);
    const QStringList &getFuncNames(void);
    std::vector<std::pair<double, double>> getPlot(const QString &funcname,
                                                   double emin, double emax,
                                                   double dmin, double dmax);

public:
    CreditTable CalcCredit(double total, size_t term, double rate, bool isDifferentiated) const;

private:
    Model &model;
};

#endif // CONTROLLER_H
