#ifndef LIBSMARTCALC_SMARTCALC_H_
#define LIBSMARTCALC_SMARTCALC_H_

namespace s21 {

class Smartcalc final {
  double CalculateExpr(const char *expr);
  // ErrorStatus set_variable(const char *name, const char *expr);
  // ErrorStatus SetFunction(const char *name, const char *def);
};

}  // namespace s21

#endif  // LIBSMARTCALC_SMARTCALC_H_
