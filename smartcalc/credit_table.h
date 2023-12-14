#ifndef CREDITTABLE_H
#define CREDITTABLE_H

#include <QString>

class CreditTable
{
    enum {Month = 0, };
public:
    CreditTable();
public:
    QString monthly_payment;
    QString overpayment;
    QString total_payment;
private:
//    QList<
};

#endif // CREDITTABLE_H
