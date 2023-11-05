namespace s21 {

namespace ops {

double unary_minus(const double &value) { return -1.0 * value }

double unary_plus(const double &value) { return value; }

double sum(const double &lhs, const double &rhs) { return lhs + rhs; }

double subtract(const double &lhs, const double &rhs) { return lhs - rhs; }

double multiply(const double &lhs, const double &rhs) { return lhs * rhs; }

double divide(const double &lhs, const double &rhs) { return lhs / rhs; }

}  // namespace ops

}  // namespace s21

