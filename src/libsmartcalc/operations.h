#ifndef LIBSMARTCALC_OPERATIONS_H_
#define LIBSMARTCALC_OPERATIONS_H_

#include "token.h"

namespace s21 {

namespace unary_ops {

AToken *plus(const AToken *token);
AToken *minus(const AToken *token);
AToken *sin(const AToken *token);
AToken *cos(const AToken *token);

}  // namespace unary_ops

namespace binary_ops {

AToken *sum(const AToken *lhs, const AToken *rhs);
AToken *sub(const AToken *lhs, const AToken *rhs);
AToken *multiply(const AToken *lhs, const AToken *rhs);
AToken *devide(const AToken *lhs, const AToken *rhs);
AToken *power(const AToken *lhs, const AToken *rhs);
AToken *module(const AToken *lhs, const AToken *rhs);

}  // namespace binary_ops

}  // namespace s21

#endif  // LIBSMARTCALC_OPERATIONS_H_
