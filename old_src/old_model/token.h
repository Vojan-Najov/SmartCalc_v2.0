#ifndef MODEL_TOKEN_H_
#define MODEL_TOKEN_H_

#include "variable.h"

namespace s21 {

enum class TokenType
{
	WRONG = -1,
	EMPTY = 0,
	DEFINITION,
	NUMBER,
	UNARY_OP,
	BINARY_OP,
	VAR,
	FUNC,
	LEFT_BRACKET,
	RIGHT_BRACKET
};

namespace unary_operator {
enum UnaryOpType {
	NOOP = -1,
	MINUS = 1,
	PLUS,
	SIN,
	COS,
	TAN,
	ASIN,
	ACOS,
	ATAN,
	LN,
	LOG
};
}  // namespace unary_operator

namespace binary_operator {
enum BinaryOpType {
	NOOP = -1,
	SUM = 1,
	SUB,
	MULT,
	DIV,
	MOD,
	POW,
};
}  // namespace binary_operator

class AToken
{
 public:
	virtual TokenType type(void) const noexcept = 0;
	virtual std::string dump(void) const noexcept = 0;
	virtual ~AToken(void) = 0;
};

class DefinitionToken : AToken
{
 public:
	TokenType type(void) const noexcept override;
	std::string dump(void) const override;
};

class NumberToken : AToken
{
 public:
	explicit NumberToken(double value) noexcept;

	TokenType type(void) const noexcept override;

	std::string dump(void) const override;

	virtual double value(void) const noexcept;

 private:
	double value_;
};

class VarToken : NumberToken
{
 public:
	explicit VarToken(const Variable &var);

  TokenType type(void) const noexcept override;

	std::string dump(void) const override;

	double value(void) const noexcept override;

 private:
	const Variable &var_;
};

class UnaryOpToken : AToken
{
 public:
	using UnaryOp = double (*)(double);

	UnaryOpToken(UnaryOp func) noexcept;

	TokenType type(void) const noexcept override;

	std::string dump(void) const noexcept override;

	NumberToken *apply(const NumberToken *token) const;

 private:
	UnaryOp func_;
};




/*
class WrongToken : AToken
{
 public:
	TokenType type(void) const noexcept override;
};

class EmptyToken : AToken
{
 public:
	TokenType type(void) const noexcept override;
	const char *dump(void) override;
};
*/

class BinaryOpToken : AToken
{
 public:
	using BinaryOp = double (*)(double, double);

	BinaryOpToken(BinaryOp func) noexcept;

	TokenType type(void) const noexcept override;

	const char *dump(void) const noexcept override;

	NumberToken *apply(const NumberToken *lhs, const NumberToken *rhs) const;

 private:
	BinaryOp func_;
};

class BracketToken : AToken
{
 public:
	BracketToken(char smb);

	TokenType type(void) const noexcept override;

	const char *dump(void) const noexcept override;

 private:
	TokenType type_;
};

class VarToken : AToken
{
 public:
	VarToken(const Variable &var) noexcept;

	TokenType type(void) const noexcept override;

	const char *dump(void) const noexcept override;

	double value(void) const noexcept;

 private:
	Variable var_; 
};

/*
class FuncToken : AToken
{
 public:
	FuncToken(const Function &func) noexcept;

	TokenType type(void) const noexcept override;

	NumberToken *apply(const AToken *token) const noexcept;

 private:
	Function func_;
};
*/

}  // namespace s21

#endif  // MODEL_TOKEN_H_
