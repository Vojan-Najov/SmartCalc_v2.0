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
  Rpn(void);
  Rpn(const Rpn &rpn);
  Rpn(Rpn &&rpn);
  Rpn &operator=(const Rpn &other);
  Rpn &operator=(Rpn &&other);
  ~Rpn(void);

 public:
  ConstIterator begin(void) const noexcept;
  ConstIterator end(void) const noexcept;

 public:
  void Push(AToken *token);
  void Push(std::unique_ptr<AToken> &token_ptr);
  bool Calculate(void);
  bool Calculate(double var);
  double Result(void) const noexcept;
  void Clear(void);

 private:
  using Iterator = std::deque<std::unique_ptr<AToken>>::iterator;

 private:
  double result_ = 0.0;
  std::deque<std::unique_ptr<AToken>> rpn_;
};

/*
 *  RPN FUNCTION TOKEN
 */
class RpnFuncToken : public AToken {
 public:
  RpnFuncToken(const Rpn &rpn);
  ~RpnFuncToken(void);

 public:
  RpnFuncToken *clone(void) const override;
  std::string dump(void) const override;

 private:
  Rpn rpn_;
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_RPN_TOKEN_H_
