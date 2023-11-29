#include <utility>

#include "smartcalc.h"
#include "parser.h"

namespace s21 {

const double Smartcalc::PI = 3.1415926535;
const double Smartcalc::E = 2.7182818284;

Smartcalc::Smartcalc(void) {
	vars_.emplace("PI", PI);
	vars_.emplace("E", E);
}

double Smartcalc::CalculateExpression(const char *expr) const {
  // double result = 0.0;
  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_);
  //  if (parser.Error()) {
  //  }
  // if (rpn.Valid()) {
  //	result = rpn.Calculate();
  // }
  return 0.0;
}

bool Smartcalc::SetVariable(const char *name, const char *expr) {
  smartcalc::Parser parser(expr);
  (void)name;
  (void)expr;
  return false;
}

bool Smartcalc::SetFunction(const char *name, const char *expr) {
  smartcalc::Parser parser(expr);
  (void)name;
  (void)expr;
  return false;
}

}  // namespace s21
