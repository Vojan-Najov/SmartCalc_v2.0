#ifndef LIBSMARTCALC_SMARTCALC_H_
#define LIBSMARTCALC_SMARTCALC_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "rpn.h"

namespace s21 {

class Smartcalc final {
 public:
  static const double PI;
  static const double E;

 public:
  using Plot = std::vector<std::pair<double, double>>;

 public:
  Smartcalc(void);

 public:
  bool CalculateExpression(const char *expr);
  bool SetVariable(const char *name, const char *expr);
  bool SetFunction(const char *name, const char *expr);
  Plot GetPlot(const char *func, std::pair<double, double> d,
               std::pair<double, double> e);

 public:
  double Result(void) const noexcept;
  bool Error(void) const;
  std::string ErrorMessage(void) const;
  std::list<std::string> GetVarNames(void) const;
  std::list<std::string> GetFuncNames(void) const;

 private:
  double result_;
  std::string errmsg_;
  std::map<std::string, double> vars_;
  std::map<std::string, smartcalc::Rpn> funcs_;
};

}  // namespace s21

#endif  // LIBSMARTCALC_SMARTCALC_H_
