#ifndef LIBSMARTCALC_SMARTCALC_H_
#define LIBSMARTCALC_SMARTCALC_H_

#include <map>
#include <string>

#include "rpn.h"

namespace s21 {

class Smartcalc final {
 public:
  static const double PI;
  static const double E;

 public:
  Smartcalc(void);

 public:
  double CalculateExpression(const char *expr);
  bool SetVariable(const char *name, const char *expr);
  bool SetFunction(const char *name, const char *expr);

 public:
	bool Error(void) const;
	std::string ErrorMessage(void) const;

 private:
	std::string errmsg_;
  std::map<std::string, double> vars_;
  std::map<std::string, smartcalc::Rpn> funcs_;
};

}  // namespace s21

#endif  // LIBSMARTCALC_SMARTCALC_H_
