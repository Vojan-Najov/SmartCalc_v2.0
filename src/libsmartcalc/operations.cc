#include <cmath>

#include "token.h"

namespace s21 {

namespace smartcalc {

namespace unary_ops {

AToken *plus(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{num};
}

AToken *minus(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{-num};
}

AToken *ln(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::log(num)};
}

AToken *log(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::log10(num)};
}

AToken *sin(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::sin(num)};
}

AToken *cos(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::cos(num)};
}

AToken *tan(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::tan(num)};
}

AToken *asin(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::asin(num)};
}

AToken *acos(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::acos(num)};
}

AToken *atan(const NumberToken *token) {
  double num = token->value;
  return new NumberToken{std::atan(num)};
}

}  // namespace unary_ops

namespace binary_ops {

AToken *sum(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{numl + numr};
}

AToken *sub(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{numl - numr};
}

AToken *multiply(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{numl * numr};
}

AToken *devide(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{numl / numr};
}

AToken *power(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{std::pow(numl, numr)};
}

AToken *module(const NumberToken *lhs, const NumberToken *rhs) {
  double numl = lhs->value;
  double numr = rhs->value;
  return new NumberToken{std::fmod(numl, numr)};
}

}  // namespace binary_ops

}  // namespace smartcalc

}  // namespace s21
