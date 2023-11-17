#include "token.h"

namespace s21 {

inline TokenType DefinitionToken::type(void) const noexcept
{
	return TokenType::DEFINITION;
}

inline std::string DefinitionToken::dump(void) const 
{
	return "=";
}


NumberToken::NumberToken(double value) noexcept : value_(value) {}

inline TokenType NumberToken::type(void) const noexcept
{
	return TokenType::NUMBER;
}

inline std::string NumberToken::dump(void) const
{
	return std::to_string(value_);
}

inline double NumberToken::value(void) const noexcept { return value_; }


VarToken::VarToken(const Variable &var) : var_(var) {}

inline TokenType VarToken::type(void) const noexcept
{
	return TokenType::VAR;
}

inline std::string VarToken::dump(void) const
{
	return "x";
}

inline double VarToken::value(void) const noexcept { return var_.value(); }


UnaryOpToken::UnaryOpToken(UnaryOp func) noexcept : func_(func) {}

inline TokenType UnaryOpToken::type(void) const noexcept 
{
	return TokenType::UNARY_OP;
}

inline std::string UnaryOpToken::dump(void) const
{
	const char *str = "noop";

	if (func_ == &operations::minus) {
		str = "-";
	} else if (func_ == &operations::plus) {
		str = "+";
	} else if (func_ == &operations::sin) {
		str = "sin";
	} else if (func_ == &operations::cos) {
		str = "cos";
	} else if (func_ == &operations::tan) {
		str = "tan";
	} else if (func_ == &operations::asin) {
		str = "asin";
	} else if (func_ == &operations::acos) {
		str = "acos";
	} else if (func_ == &operations::atan) {
		str = "atan";
	} else if (func_ == &operations::ln) {
		str = "ln";
	} else if (func_ == &operations::log) {
		str = "log";
	}

	return str;
}

inline NumberToken *UnaryOpToken::apply(const NumberToken *token) const {
	return new NumberToken(func_(token->value()));
}


BinaryOpToken::BinaryOpToken(BinaryOp func) noexcept : func_(func) {}

inline TokenType BinaryOpToken::type(void) const noexcept 
{
	return TokenType::BINARY_OP;
}

inline NumberToken *BinaryOpToken::apply(const NumberToken *lhs,
																				 const NumberToken *rhs) const
{
	return new NumberToken(func_(lhs->value(), rhs->value()));
}


BracketToken::BracketToken(char smb)
	: type_(smb == '(' ? TokenType::LEFT_BRACKET : TokenType::RIGHT_BRACKET)
{}

inline TokenType BracketToken::type(void) const noexcept
{
	return type_;
}


VarToken::VarToken(const Variable &var) noexcept : var_(var) {}

inline TokenType VarToken::type(void) const noexcept { return TokenType::NUMBER; }

inline double VarToken::value(void) const noexcept {
  double val;
	var_.GetValue(val);
	return val;
}


/*

inline TokenType WrongToken::type(void) const noexcept 
{
	return TokenType::WRONG;
}


inline TokenType EmptyToken::type(void) const noexcept
{
	return TokenType::EMPTY;
}




FuncToken::FuncToken(const Function &func) : func_(func) {}

inline TokenType FuncToken::type(void) const noexcept { return TokenType::FUNC; }

inline NumberToken *FuncToken::apply(AToken *token) const {
	return new NumberToken(token->value());
}
*/

}  // namespace s21 {
