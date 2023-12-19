#ifndef CREDITTABLE_H
#define CREDITTABLE_H

#include <QString>
#include <vector>
#include <array>

class CreditTable
{
public:
    CreditTable(size_t n);

public:
    void SetMonthlyPayment(size_t idx, double value);
    void SetPrincipalPayment(size_t idx, double value);
    void SetInterestPayment(size_t idx, double value);
    void SetBalanceOwed(size_t idx, double value);

public:
    double GetMonthlyPayment(size_t idx) const;
    double GetPrincipalPayment(size_t idx) const;
    double GetInterestPayment(size_t idx) const;
    double GetBalanceOwed(size_t idx) const;
    double GetTotalPayment(void) const;
    double GetTotalPrincipalPayment(void) const;
    double GetTotalInterestPayment(void) const;

    QString GetStringMonthlyPayment(size_t idx) const;
    QString GetStringPrincipalPayment(size_t idx) const;
    QString GetStringInterestPayment(size_t idx) const;
    QString GetStringBalanceOwed(size_t idx) const;
    QString GetStringTotalPayment(void) const;
    QString GetStringTotalPrincipalPayment(void) const;
    QString GetStringTotalInterestPayment(void) const;

private:
    std::vector<std::array<double, 4>> tab;
};

#endif // CREDITTABLE_H
