#include "model.h"

#include <QString>
#include <QStringList>
#include <QDebug>

Model::Model()
{
    std::list<std::string> lst = sc.GetFuncNames();
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        funcnames << it->c_str();
    }
}

QString Model::СalculateExpression(QString expr) {
   if (!expr.contains("=")) {
       sc.CalculateExpression(expr.toLatin1());
       if (sc.Error()) {
           return sc.ErrorMessage().c_str();
       }
       return QString::number(sc.Result(),'g', 6);
   }

   QStringList strlist = expr.split("=");
   if (strlist.size() > 2) {
       return "Error: no more than one assignment character is expected";
   }

   expr = strlist.back();
   strlist = strlist.front().trimmed().split(" ", Qt::SkipEmptyParts);
   if (strlist.size() != 2) {
       return "Error: incorrect instruction";
   }

   QString type = strlist.front();
   if (type != "var" && type != "func") {
       return QString("Error: unknown keyword ") + type;
   }

   QString name = strlist.back();
   if (!name[0].isLetter() && name[0].unicode() > 127) {
       return QString("Error: '") + name + QString("' incorrect name of ") + type;
   }

   if (type == "var") {
       sc.SetVariable(name.toLatin1(), expr.toLatin1());
       if (sc.Error()) {
           return sc.ErrorMessage().c_str();
       }
       return QString::number(sc.Result(),'g', 6);
   } else {
       sc.SetFunction(name.toLatin1(), expr.toLatin1());
       if (sc.Error()) {
           return sc.ErrorMessage().c_str();
       }
       funcnames << name;
       funcnames.sort();
       return QString("func ") + strlist.back() + QString(" defined");
   }
}

const QStringList &Model::getFuncNames() {
    return funcnames;
}

std::vector<std::pair<double, double>> Model::getPlot(const QString &funcname,
                                                      double emin, double emax,
                                                      double dmin, double dmax)
{
    return sc.GetPlot(funcname.toLatin1(), {dmin, dmax}, {emin,emax});
}

CreditTable Model::CalcAnnuityCredit(double total, size_t term, double rate) const {
    CreditTable table(term);

    double month_rate = rate / 100.0 / 12.0;
    double annuity_factor = month_rate * std::pow((month_rate + 1.0), (double)term)
                                       / (std::pow((month_rate + 1.0), (double)term) - 1.0);
    double monthly_payment = annuity_factor * total;

    double saldo = total;
    for (size_t i = 0; i < term; ++i) {
        double interest_payment = saldo * month_rate;
        double principal_payment = monthly_payment - interest_payment;
        saldo = saldo * (1.0 + month_rate) - monthly_payment;
        if (saldo < 0.0) saldo = 0.0;

        table.SetMonthlyPayment(i, monthly_payment);
        table.SetPrincipalPayment(i, principal_payment);
        table.SetInterestPayment(i, interest_payment);
        table.SetBalanceOwed(i, saldo);
    }

    return table;
}

CreditTable Model::CalcDifferetiatedCredit(double total, size_t term, double rate) const {
    CreditTable table(term);

    double month_rate = rate / 100.0 / 12.0;
    double saldo = total;
    double principal_payment = total / (double)term;

    for (size_t i = 0; i < term; ++i) {
        double interest_payment = saldo * month_rate;
        double monthly_payment = principal_payment + interest_payment;
        saldo -= principal_payment;
        if (saldo < 0.0) saldo = 0.0;

        table.SetMonthlyPayment(i, monthly_payment);
        table.SetPrincipalPayment(i, principal_payment);
        table.SetInterestPayment(i, interest_payment);
        table.SetBalanceOwed(i, saldo);
    }

    return table;
}

