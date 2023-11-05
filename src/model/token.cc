#include "token.h"

inline TokenType WrongToken::type(void) const noexcept override
{
	return WRONG_TOKEN;
}


inline TokenType EmptyToken::type(void) const noexcept override
{
	return EMPTY_TOKEN;
}


inline TokenType DefinitionToken::type(void) const noexcept override
{
	return DEFINITION_TOKEN;
}


NumberToken::NumberToken(const double &value) noexcept : value_(value) {}

inline TokenType NumberToken::type(void) const noexcept override
{
	return NUMBER_TOKEN;
}

inline const double &TokenType::value(void) const noexcept { return value_; }


UnaryOpToken::UnaryOpToken(UnaryOp func) noexcept : func_(func) {}

inline TokenType UnaryOpToken::type(void) const noexcept override
{
	return UNARY_OP_TOKEN;
}

inline NumberToken *apply(const AToken *token) const {
	return new NumberToken(func_(token.value()));
}


BinaryOpToken::BinaryOpToken(BinaryOp func) const noexcept : func_(func) {}

inline TokenType BinaryOpToken::type(void) const noexcept override
{
	return BINARY_OP_TOKEN;
}

inline NumberToken *apply(const AToken *lhs, const AToken *rhs) const
{
	return new NumberToken(func_(lhs.value(), rhs.value()));
}

