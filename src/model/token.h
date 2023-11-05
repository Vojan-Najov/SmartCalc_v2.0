#ifndef CALC_TOKEN_H_
#define CALC_TOKEN_H_

enum class TokenType
{
	WRONG_TOKEN = -1,
	EMPTY_TOKEN = 0,
	DEFINITION_TOKEN,
	NUMBER_TOKEN,
	VAR_TOKEN,
	UNARY_OP_TOKEN,
	BINARY_OP_TOKEN,
	LEFT_BRACKET_TOKEN,
	RIGHT_BRACKET_TOKEN
};

class AToken
{
 public:
	TokenType type(void) const noexcept = 0;
	~AToken(void) = 0;
};

class WrongToken : AToken
{
 public:
	TokenType type(void) const noexcept override;
};

class EmptyToken : AToken
{
 public:
	TokenType type(void) const noexcept overrife;
};

class DefinitionToken : AToken
{
 public:
	TokenType type(void) const noexcept override;
};

class NumberToken : AToken
{
 public:
	explicit NumberToken(const double &value) noexcept;

	TokenType type(void) const noexcept override;

	const double &value(void) const noexcept;

 private:
	double value_;
};

class UnaryOpToken: AToken
{
 public:
	using UnaryOp = double (*)(double);

	UnaryOpToken(UnaryOp func) noexcept;

	TokenType type(void) const override;

	NumberToken *apply(const AToken &token) const;

 private:
	UnaryOp func_;
};

class BinaryOpToken : AToken
{
 public:
	using BinaryOp = double (*)(double, double);

	BinaryOpToken(BinaryOp func) noexcept;

	TokenType type(void) const noexcept override;

	NumberToken *apply(const AToken &lhs, const AToken &rhs) const;

 private:
	BinaryOp func_;
};

class LeftBracketToken : AToken
{
 public:
	TokenType type(void) const noexcept override { return LEFT_BRACKET_TOKEN; }
};

class RightBracketToken : AToken
{
 public:
	TokenType type(void) const noexcept override { return RIGHT_BRACKET_TOKEN; }
};

/*
template <typename Tp>
class VarToken : AToken
{
 public:
	TokenType type(void) const noexcept override;

	const Tp &value(void) const noexcept { return var.value(); }

 private:
	Variable<Tp> var; 
};
*/



#endif  // CALC_TOKEN_H_
