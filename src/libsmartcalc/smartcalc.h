#ifndef LIBSMARTCALC_SMARTCALC_H_
#define LIBSMARTCALC_SMARTCALC_H_

namespace s21 {

class Smartcalc final {
 public:
  double CalculateExpression(const char *expr) const;
  bool SetVariable(const char *name, const char *expr);
  bool SetFunction(const char *name, const char *expr);
};

}  // namespace s21

#endif  // LIBSMARTCALC_SMARTCALC_H_
