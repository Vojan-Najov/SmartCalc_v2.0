#ifndef LIBSMARTCALC_OPERATIONS_H_
#define LIBSMARTCALC_OPERATIONS_H_

#include "token.h"

namespace s21 {

namespace smartcalc {

namespace unary_ops {

AToken *plus(const NumberToken *token);
AToken *minus(const NumberToken *token);
AToken *ln(const NumberToken *token);
AToken *log(const NumberToken *token);
AToken *sin(const NumberToken *token);
AToken *cos(const NumberToken *token);
AToken *tan(const NumberToken *token);
AToken *asin(const NumberToken *token);
AToken *acos(const NumberToken *token);
AToken *atan(const NumberToken *token);

}  // namespace unary_ops

namespace binary_ops {

AToken *sum(const NumberToken *lhs, const NumberToken *rhs);
AToken *sub(const NumberToken *lhs, const NumberToken *rhs);
AToken *multiply(const NumberToken *lhs, const NumberToken *rhs);
AToken *devide(const NumberToken *lhs, const NumberToken *rhs);
AToken *power(const NumberToken *lhs, const NumberToken *rhs);
AToken *module(const NumberToken *lhs, const NumberToken *rhs);

}  // namespace binary_ops

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_OPERATIONS_H_
