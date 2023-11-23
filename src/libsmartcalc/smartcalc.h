#ifndef LIBSMARTCALC_SMARTCALC_H_
#define LIBSMARTCALC_SMARTCALC_H_

#include <map>
#include <string>

#include "rpn.h"

namespace s21 {

class Smartcalc final {
 public:
  double CalculateExpression(const char *expr) const;
  bool SetVariable(const char *name, const char *expr);
  bool SetFunction(const char *name, const char *expr);

 private:
  std::map<std::string, smartcalc::Rpn> ns_;
};

}  // namespace s21

#endif  // LIBSMARTCALC_SMARTCALC_H_
