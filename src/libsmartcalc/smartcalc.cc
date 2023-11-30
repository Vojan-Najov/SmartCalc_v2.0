#include "smartcalc.h"

#include <cmath>
#include <utility>

#include "parser.h"

namespace s21 {

const double Smartcalc::PI = 3.1415926535;
const double Smartcalc::E = 2.7182818284;

Smartcalc::Smartcalc(void) {
  vars_.emplace("PI", PI);
  vars_.emplace("E", E);
}

double Smartcalc::CalculateExpression(const char *expr) const {
  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
    return std::nan("");  // handle error
  }

  if (!rpn.Calculate()) {
    return std::nan("");  // handle error
  }

  return rpn.Result();
}

bool Smartcalc::SetVariable(const char *name, const char *expr) {
  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
    return false;  // handle error
  }

  if (!rpn.Calculate()) {
    return false;  // handle error
  }

  vars_[name] = rpn.Result();

  return true;
}

bool Smartcalc::SetFunction(const char *name, const char *expr) {
  if (vars_.find(name) != vars_.end()) {
    return false;  // handle error
  }

  smartcalc::Parser parser(expr, true);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);
  if (parser.Error()) {
    return false;  // handle error
  }

  //	if (!rpn.Optimize()) {
  //		return false; // handle error
  //	}

  funcs_[name] = std::move(rpn);
  return true;
}

}  // namespace s21
