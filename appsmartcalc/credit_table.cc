#include "credit_table.h"

namespace s21 {

CreditTable::CreditTable(size_t n) { tab.resize(n); }

void CreditTable::SetMonthlyPayment(size_t idx, double value) {
  tab[idx][0] = value;
}

double CreditTable::GetMonthlyPayment(size_t idx) const { return tab[idx][0]; }

QString CreditTable::GetStringMonthlyPayment(size_t idx) const {
  return QString::number(tab[idx][0], 'f', 2);
}

void CreditTable::SetPrincipalPayment(size_t idx, double value) {
  tab[idx][1] = value;
}

double CreditTable::GetPrincipalPayment(size_t idx) const {
  return tab[idx][1];
}

QString CreditTable::GetStringPrincipalPayment(size_t idx) const {
  return QString::number(tab[idx][1], 'f', 2);
}

void CreditTable::SetInterestPayment(size_t idx, double value) {
  tab[idx][2] = value;
}

double CreditTable::GetInterestPayment(size_t idx) const { return tab[idx][2]; }

QString CreditTable::GetStringInterestPayment(size_t idx) const {
  return QString::number(tab[idx][2], 'f', 2);
}

void CreditTable::SetBalanceOwed(size_t idx, double value) {
  tab[idx][3] = value;
}

double CreditTable::GetBalanceOwed(size_t idx) const { return tab[idx][3]; }

QString CreditTable::GetStringBalanceOwed(size_t idx) const {
  return QString::number(tab[idx][3], 'f', 2);
}

double CreditTable::GetTotalPayment(void) const {
  double total = 0.0;
  for (auto it = tab.begin(), last = tab.end(); it != last; ++it) {
    total += (*it)[0];
  }
  return total;
}

QString CreditTable::GetStringTotalPayment(void) const {
  return QString::number(GetTotalPayment(), 'f', 2);
}

double CreditTable::GetTotalPrincipalPayment(void) const {
  double total = 0.0;
  for (auto it = tab.begin(), last = tab.end(); it != last; ++it) {
    total += (*it)[1];
  }
  return total;
}

QString CreditTable::GetStringTotalPrincipalPayment(void) const {
  return QString::number(GetTotalPrincipalPayment(), 'f', 2);
}

double CreditTable::GetTotalInterestPayment(void) const {
  double total = 0.0;
  for (auto it = tab.begin(), last = tab.end(); it != last; ++it) {
    total += (*it)[2];
  }
  return total;
}

QString CreditTable::GetStringTotalInterestPayment(void) const {
  return QString::number(GetTotalInterestPayment(), 'f', 2);
}

}  // namespace s21
