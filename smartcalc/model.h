#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QStringList>

#include "smartcalc.h"
#include "credit_table.h"

class Model
{
public:
    Model();

public:
    QString calculateExpression(QString expr);
    const QStringList &getFuncNames();
    std::vector<std::pair<double, double>> getPlot(const QString &funcname,
                                                   double emin, double emax,
                                                   double dmin, double dmax);
    QString calcCredit(double total, unsigned int term, double rate, bool isDifferentiated);

public:
    CreditTable CalcAnnuityCredit(double total, size_t term, double rate) const;
    CreditTable CalcDifferetiatedCredit(double total, size_t term, double rate) const;

private:
    s21::Smartcalc sc;
    QStringList funcnames;
};

#endif // MODEL_H
