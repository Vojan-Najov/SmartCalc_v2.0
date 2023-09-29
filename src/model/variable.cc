#include "variable.h"

namespace s21 {

Variable::Variable(void) : value(0.0), saved_value(0.0), is_defined(false) {}

void Variable::SetValue(double x) {
  is_defined = true;
  value = x;
}

void Variable::UnsetValue(void) { is_defined = false; }

int Variable::GetValue(double &x) {
  if (is_defined) {
    x = value;
    return 0;
  }

  return 1;
}

void Variable::SaveValue(void) {
  if (is_defined) {
    is_saved = true;
    saved_value = value;
  }
}

void Variable::RestoreValue(void) {
  if (is_saved) {
    is_saved = false;
    value = saved_value;
  } else {
    is_defined = false;
  }
}

}  // namespace s21
