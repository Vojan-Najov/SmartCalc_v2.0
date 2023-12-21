#include "controller.h"

#include <vector>

Controller::Controller(Model &model) : model(model) {}

QString Controller::CalculateExpression(QString expr) {
  return model.СalculateExpression(std::move(expr));
}

Controller::StringList Controller::GetFuncNames(void) const {
  return model.GetFuncNames();
}

Controller::Plot Controller::GetPlot(const QString &funcname, double dmin,
                                     double dmax, double emin, double emax) {
  return model.GetPlot(funcname, dmin, dmax, emin, emax);
}

CreditTable Controller::CalcCredit(double total, size_t term, double rate,
                                   bool isDifferentiated) const {
  if (!isDifferentiated) {
    return model.CalcAnnuityCredit(total, term, rate);
  }
  return model.CalcDifferetiatedCredit(total, term, rate);
}
