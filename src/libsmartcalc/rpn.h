#ifndef LIBSMARTCALC_RPN_H_
#define LIBSMARTCALC_RPN_H_

#include <memory>
#include <deque>

#include "token.h"

namespace s21 {

namespace smartcalc {

class Rpn {
 public:
	void Push(AToken *token);
	void Calculate(void);
	double Result(void) const noexcept;
 private:
	double result_ = 0.0;
	std::deque<std::unique_ptr<AToken>> rpn_;	
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_RPN_H_
