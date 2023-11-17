#ifndef MODEL_TOKEN_H_
#define MODEL_TOKEN_H_

namespace s21 {

enum class TokenType {
  kWrong = -1,
  kEmpty = 0,
  kAssign = 1,
  kNumber = 2,
  kVar = 3,
  kUnaryOp = 4,
  kBinaryOp = 5,
  kFunction = 6,
  kLeftBracket = 7,
  kRightBracket = 8
};

enum class UnaryOperator { kMinus = 1, kPlus = 2 };

enum class BinaryOperator {
  kAdd = 1,
  kSub = 2,
  kMul = 3,
  kDiv = 4,
  kMod = 5,
  kPow = 6
};

enum class FunctionOperator {
  kCos = 1,
  kSin = 2,
  kTan = 3,
  kAcos = 4,
  kAsin = 5,
  kAtan = 6,
  kSqrt = 7,
  kLn = 8,
  kLog = 9,
  kF = 10
};

struct Token {
  TokenType type;
  union {
    double num;
    UnaryOperator unop;
    BinaryOperator biop;
    FunctionOperator func;
    int error;
  } value;
};

class AToken {
 public:
	TokenType type(void) const = 0;
	~TokenBase(void) = 0;
};

class WrongToken : AToken {
 public:
	TokenType type(void) const override { return kWrongToken; }

	~WrongToken(void) {}
};

class EmptyToken : AToken {
 public:
	TokenType type(void) const override { return kEmptyToken; }

	~EmptyToken(void) {}
};

class NumberToken : AToken {
 public:
	NumberToken(double value = 0.0) : value_(value) {}

	TokenType type(void) const override { return kNumber; }

	double value(void) const { return value_; }

  ~NumberToken(void) {}

 private:
	double value_;
};

class AssignToken : AToken {
 public:
	TokenType type(void) const override { return kAssignToken; }

	~AssignToken(void) {}
};

template <typename UnaryOperator>
class UnopToken : AToken {
 public:
	TokenType type(void) const override { return kUnaryOpToken; }

	void Apply(NumberToken *num) const { num.value() = unop_(num.value()); }

 private:
	UnaryOperator unop_;
};

class <typename BinaryOperator>
class BinopToken : AToken {
 public:
	TokenType type(void) const override { return kBinaryOpToken; }

  void Apply(NumberToken *num1, NumberToken *num2 ) const {
		num1.value() = binop_(num1.value(), num2.value());
	}

 private:
	BinaryOperator binop_;
};

}  // namespace s21

#endif  // MODEL_TOKEN_H_
