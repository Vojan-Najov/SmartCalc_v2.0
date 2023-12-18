#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QStringList>

#include "smartcalc.h"
#include "credit_table.h"

class Model
{
public:
    using StringList = std::list<std::string>;
    using Plot = std::vector<std::pair<double, double>>;
public:
    Model();

public:
    QString СalculateExpression(QString expr);
    Plot GetPlot(const QString &funcname, double dmin, double dmax, double emin, double emax);


    QString calcCredit(double total, unsigned int term, double rate, bool isDifferentiated);

public:
    StringList GetFuncNames() const;
    CreditTable CalcAnnuityCredit(double total, size_t term, double rate) const;
    CreditTable CalcDifferetiatedCredit(double total, size_t term, double rate) const;

private:
    s21::Smartcalc sc;
};

#endif // MODEL_H
