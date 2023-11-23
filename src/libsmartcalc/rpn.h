#ifndef LIBSMARTCALC_RPN_H_
#define LIBSMARTCALC_RPN_H_

#include <deque>
#include <memory>

#include "token.h"

namespace s21 {

namespace smartcalc {

class Rpn {
 public:
  using ConstIterator = std::deque<std::unique_ptr<AToken>>::const_iterator;

 public:
  ConstIterator begin(void) const noexcept;
  ConstIterator end(void) const noexcept;

 public:
  void Push(AToken *token);
  void Push(std::unique_ptr<AToken> &token_ptr);
  void Calculate(void);
  double Result(void) const noexcept;

 private:
  double result_ = 0.0;
  std::deque<std::unique_ptr<AToken>> rpn_;
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_RPN_H_
