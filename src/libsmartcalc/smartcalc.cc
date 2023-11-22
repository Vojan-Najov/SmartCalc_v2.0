#include "smartcalc.h"
#include "parser.h"

namespace s21 {

double Smartcalc::CalculateExpression(const char *expr) const {
	// double result = 0.0;
	smartcalc::Parser parser(expr);
	//smartcalc::Rpn rpn = parser.ToRpn();
	// if (parser.Error()) {
	// }
	//if (rpn.Valid()) {
	//	result = rpn.Calculate();
	//}
	return 0.0;
}

bool Smartcalc::SetVariable(const char *name, const char *expr) {
	smartcalc::Parser parser(expr);
	(void) name;
	(void) expr;
	return false;
}

bool Smartcalc::SetFunction(const char *name, const char *expr) {
	smartcalc::Parser parser(expr);
	(void) name;
	(void) expr;
	return false;
}

}  // namespace s21
