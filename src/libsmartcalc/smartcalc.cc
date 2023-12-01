#include <cmath>
#include <utility>

#include "smartcalc.h"
#include "token.h"
#include "operations.h"
#include "parser.h"

namespace s21 {

const double Smartcalc::PI = 3.1415926535;
const double Smartcalc::E = 2.7182818284;

Smartcalc::Smartcalc(void) : result_{0.0} {
  vars_.emplace("PI", PI);
  vars_.emplace("E", E);

  smartcalc::Rpn rpn{};

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::sin});
  funcs_["sin"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::cos});
  funcs_["cos"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::tan});
  funcs_["tan"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::asin});
  funcs_["asin"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::acos});
  funcs_["acos"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::atan});
  funcs_["atan"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::ln});
  funcs_["ln"] = std::move(rpn); 

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::unary_ops::log});
  funcs_["log"] = std::move(rpn); 
}

bool Smartcalc::CalculateExpression(const char *expr) {
  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
    errmsg_ = parser.ErrorMessage();
    return false;
  }

  if (!rpn.Calculate()) {
	return false;  // handle error
  }

  result_ = rpn.Result();
  return true;
}

bool Smartcalc::SetVariable(const char *name, const char *expr) {
  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
		errmsg_ = parser.ErrorMessage();
    return false;
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
		errmsg_ = parser.ErrorMessage();
    return false;
  }

  //	if (!rpn.Optimize()) {
  //		return false; // handle error
  //	}

  funcs_[name] = std::move(rpn);
  return true;
}

double Smartcalc::Result(void) const noexcept { return result_; }

bool Smartcalc::Error(void) const { return !errmsg_.empty(); }

std::string Smartcalc::ErrorMessage(void) const { return errmsg_; }

}  // namespace s21
