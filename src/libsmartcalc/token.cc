#include "token.h"
#include "operations.h"

namespace s21 {

// EMPTY TOKEN

TokenType EmptyToken::Type(void) const noexcept {
	return TokenType::Empty;
}

std::string EmptyToken::Dump(void) const {
	return std::string{};
}

EmptyToken::~EmptyToken(void) {}

// WRONG TOKEN

WrongToken::WrongToken(const std::string &str) : errmsg{str} {}

TokenType WrongToken::Type(void) const noexcept {
	return TokenType::Wrong;
}

std::string WrongToken::Dump(void) const {
	return errmsg;
}

WrongToken::~WrongToken(void) {}

// NUMBER TOKEN

NumberToken::NumberToken(double value) noexcept : value_(value) {}

TokenType NumberToken::Type(void) const noexcept {
	return TokenType::Number;
}

std::string NumberToken::Dump(void) const {
	return std::to_string(value_);
}

double NumberToken::Value(void) const noexcept { return value_; }

NumberToken::~NumberToken(void) {}

// UNARY OP TOKEN

UnaryOpToken::UnaryOpToken(Unop unop) noexcept : unop_{unop} {}

TokenType UnaryOpToken::Type(void) const noexcept {
	return TokenType::UnaryOp;
}

std::string UnaryOpToken::Dump(void) const {
	const char *s = "unknow unop";

	if (unop_ == &unary_ops::plus) {
		s = "+";
	} else if (unop_ == &unary_ops::minus) {
		s = "-";
	} else if (unop_ == &unary_ops::sin) {
		s = "sin";
	} else if (unop_ == &unary_ops::cos) {
		s = "cos";
	}

	return std::string(s);
}

AToken *UnaryOpToken::Apply(const AToken *token) const {
	return unop_(token);
}

UnaryOpToken::~UnaryOpToken() {}

// BINARY OP TOKEN

BinaryOpToken::BinaryOpToken(Binop binop) noexcept : binop_{binop} {}

TokenType BinaryOpToken::Type(void) const noexcept {
	return TokenType::BinaryOp;
}

std::string BinaryOpToken::Dump(void) const {
	const char *s = "unknow binop";

	if (binop_ == &binary_ops::sum) {
		s = "+";
	} else if (binop_ == &binary_ops::sub) {
		s = "-";
	} else if (binop_ == &binary_ops::multiply) {
		s = "*";
	} else if (binop_ == &binary_ops::devide) {
		s = "/";
	} else if (binop_ == &binary_ops::power) {
		s = "^";
	} else if (binop_ == &binary_ops::module) {
		s = "%";
	}

	return std::string(s);
}

AToken *BinaryOpToken::Apply(const AToken *lhs, const AToken *rhs) const {
	return binop_(lhs, rhs);
}

BinaryOpToken::~BinaryOpToken() {}

// LEFT BRACKET TOKEN

TokenType LeftBracketToken::Type(void) const noexcept {
	return TokenType::LeftBracket;
}

std::string LeftBracketToken::Dump(void) const {
	return std::string("(");
}

LeftBracketToken::~LeftBracketToken(void) {}

// RIGHT BRACKET TOKEN

TokenType RightBracketToken::Type(void) const noexcept {
	return TokenType::RightBracket;
}

std::string RightBracketToken::Dump(void) const {
	return std::string(")");
}

RightBracketToken::~RightBracketToken(void) {}

}  // namespace s21

