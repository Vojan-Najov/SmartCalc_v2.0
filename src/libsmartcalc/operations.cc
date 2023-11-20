#include <cmath>

#include "token.h"

namespace s21 {

namespace unary_ops {

AToken *plus(const AToken *token) {
	double num = static_cast<const AValue *>(token)->Value();
	return new NumberToken{num};
}

AToken *minus(const AToken *token) {
	double num = static_cast<const AValue *>(token)->Value();
	return new NumberToken{-num};
}

AToken *sin(const AToken *token) {
	double num = static_cast<const AValue *>(token)->Value();
	return new NumberToken{std::sin(num)};
}

AToken *cos(const AToken *token) {
	double num = static_cast<const AValue *>(token)->Value();
	return new NumberToken{std::sin(num)};
}

}  // namespace unary_ops


namespace binary_ops {

AToken *sum(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{numl + numr};
}

AToken *sub(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{numl - numr};
}

AToken *multiply(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{numl * numr};
}

AToken *devide(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{numl / numr};
}

AToken *power(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{std::pow(numl, numr)};
}

AToken *module(const AToken *lhs, const AToken *rhs) {
	double numl = static_cast<const AValue *>(lhs)->Value();
	double numr = static_cast<const AValue *>(rhs)->Value();
	return new NumberToken{std::fmod(numl, numr)};
}


}  // namespace binary_ops

}  // namespace s21

