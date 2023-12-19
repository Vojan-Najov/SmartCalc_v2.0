#include "smartcalc.h"

#include <cctype>
#include <cmath>
#include <utility>

#include "operations.h"
#include "parser.h"
#include "token.h"

namespace s21 {

const double Smartcalc::PI = 3.1415926535;
const double Smartcalc::E = 2.7182818284;

Smartcalc::Smartcalc(void) : result_{0.0} {
  vars_.emplace("PI", PI);
  vars_.emplace("E", E);

  smartcalc::Rpn rpn{};

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::sin});
  funcs_["sin"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::cos});
  funcs_["cos"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::tan});
  funcs_["tan"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::asin});
  funcs_["asin"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::acos});
  funcs_["acos"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::atan});
  funcs_["atan"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::ln});
  funcs_["ln"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::log});
  funcs_["log"] = std::move(rpn);

  rpn.Push(new smartcalc::VarToken{});
  rpn.Push(new smartcalc::FuncToken{&smartcalc::funcs::sqrt});
  funcs_["sqrt"] = std::move(rpn);
}

bool Smartcalc::CalculateExpression(const char *expr) {
  errmsg_.clear();

  smartcalc::Parser parser{expr};
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
    errmsg_ = parser.ErrorMessage();
    return false;
  }

  if (!rpn.Calculate()) {
    errmsg_ = rpn.ErrorMessage();
    return false;
  }

  result_ = rpn.Result();
  return true;
}

bool Smartcalc::SetVariable(const char *name, const char *expr) {
  errmsg_.clear();

  if (!*name || !std::isalpha(*name)) {
    errmsg_ = std::string{"'"} + std::string{name} +
              std::string{"' is invalid name for a variable"};
    return false;
  }

  if (funcs_.find(name) != funcs_.end()) {
    errmsg_ = std::string{"The name '"} + name + "' is defined as the function";
    return false;
  }

  smartcalc::Parser parser(expr);
  smartcalc::Rpn rpn = parser.ToRpn(vars_, funcs_);

  if (parser.Error()) {
    errmsg_ = parser.ErrorMessage();
    return false;
  }

  if (!rpn.Calculate()) {
    errmsg_ = rpn.ErrorMessage();
    return false;
  }

  result_ = rpn.Result();
  vars_[name] = result_;

  return true;
}

bool Smartcalc::SetFunction(const char *name, const char *expr) {
  errmsg_.clear();

  if (!*name || !std::isalpha(*name)) {
    errmsg_ = std::string{"'"} + std::string{name} +
              std::string{"' is invalid name for a function"};
    return false;
  }

  if (vars_.find(name) != vars_.end()) {
    errmsg_ = std::string{"The name '"} + std::string{name} +
              std::string{"' is defined as the variable"};
    return false;
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

std::list<std::string> Smartcalc::GetFuncNames(void) const {
  std::list<std::string> lst;
  std::map<std::string, smartcalc::Rpn>::const_iterator it = funcs_.cbegin();
  std::map<std::string, smartcalc::Rpn>::const_iterator last = funcs_.cend();
  for (; it != last; ++it) {
    lst.push_back(it->first);
  }
  return lst;
}

std::list<std::string> Smartcalc::GetVarNames(void) const {
  std::list<std::string> lst;
  std::map<std::string, double>::const_iterator it = vars_.cbegin();
  std::map<std::string, double>::const_iterator last = vars_.cend();
  for (; it != last; ++it) {
    lst.push_back(it->first);
  }
  return lst;
}

Smartcalc::Plot Smartcalc::GetPlot(const char *func,
                                   std::pair<double, double> d,
                                   std::pair<double, double> e) {
  (void)e;
  if (funcs_.find(func) != funcs_.end()) {
    errmsg_ = std::string{"Function '"} + std::string{func} +
              std::string{"' is not defined"};
  }

  const smartcalc::Rpn &rpn = funcs_[func];
  size_t count = 1.0e4;
  double step = (d.second - d.first) / 2.0 / (double)count;
  if (step < 1.0e-6) {
    step = 1.0e-5;
  }

  Plot plot{};
  plot.reserve(count);
  for (double x = d.first, y_prev = 0.0; x < d.second; x += step) {
    smartcalc::Rpn f{rpn};
    f.Calculate(x);
    double y = f.Result();
    if (f.Error() || std::isinf(y) ||
        (std::fabs(y - y_prev) / step > 1.e3 * (d.second - d.first))) {
      y = std::nan("");
    }

    plot.emplace_back(x, y);
    y_prev = y;
  }

  return plot;
}

}  // namespace s21
