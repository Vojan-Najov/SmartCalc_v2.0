#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <string>

#include "smartcalc.h"

namespace s21 {

class Model final {
 public:
	std::string RunExpression(const std::string &expr);
	// void calculate_credit(void);
	// void calculate_debit(void);

 private:
	Smartcalc sc_;
	// Debitcalc dc_;
	// Creditcalc cc_;
};

}  // namespace s21

#endif  // MODEL_MODEL_H_
