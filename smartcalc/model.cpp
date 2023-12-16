#include "model.h"

#include <QString>
#include <QStringList>
#include <QDebug>

Model::Model()
{
    std::list<std::string> lst = sc.GetFuncNames();
    qDebug() << "hello\n";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        funcnames << it->c_str();
        qDebug() << it->c_str();
    }
}

QString Model::calculateExpression(QString expr)
{
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
   QString lhs = strlist.front().trimmed();
   QString rhs = strlist.back();
   strlist = lhs.split(" ", Qt::SkipEmptyParts);
   if (strlist.front() != "var" && strlist.front() != "func") {
       return QString("Error: unlnown keyword ") + strlist.front();
   }
   if (!strlist.back()[0].isLetter() && strlist.back()[0].unicode() > 127) {
       return QString("Error: '") + strlist.back() + QString("' incorrect name of ") + strlist.front();
   }
   if (strlist.front() == "var") {
        sc.SetVariable(strlist.back().toLatin1(), rhs.toLatin1());
        if (sc.Error()) {
            return sc.ErrorMessage().c_str();
        }
        sc.CalculateExpression(strlist.back().toLatin1());
        return QString::number(sc.Result(),'g', 6);
   }
   if (strlist.front() == "func") {
        sc.SetFunction(strlist.back().toLatin1(), rhs.toLatin1());
        if (sc.Error()) {
            return sc.ErrorMessage().c_str();
        }
        funcnames << lhs.back();
        funcnames.sort();
        return QString("func ") + lhs.back() + QString(" defined");
   }
   return "TODO";
}

const QStringList &Model::getFuncNames() {
    return funcnames;
}

std::vector<std::pair<double, double>> Model::getPlot(const QString &funcname,
                                                      double emin, double emax,
                                                      double dmin, double dmax)
{
    //return sc.GetPlot(funcname.toLatin1(), std::make_pair(emin, emax), std::make_pair(dmin, dmax));
    //series->append(0, 6);
    //series->append(2, 4);
    //series->append(3, 8);
    //series->append(7, 4);
    //series->append(10, 5);
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    return sc.GetPlot(funcname.toLatin1(), {dmin, dmax}, {emin,emax});
    std::vector<std::pair<double, double>> vec{};
    vec.push_back({-10, std::nan("")});
    vec.push_back({0,6});
    vec.push_back({2,4});
    vec.push_back({3,8});
    vec.push_back({7,4});
    vec.push_back({10,5});
    vec.push_back({11,1});
    vec.push_back({13,3});
    vec.push_back({17,6});
    vec.push_back({18,3});
    vec.push_back({20,2});
    return vec;
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

