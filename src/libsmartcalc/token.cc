#include "token.h"

#include "operations.h"

namespace s21 {

namespace smartcalc {

// EMPTY TOKEN

TokenType EmptyToken::Type(void) const noexcept { return TokenType::Empty; }

std::string EmptyToken::Dump(void) const { return std::string{}; }

EmptyToken::~EmptyToken(void) {}

// WRONG TOKEN

WrongToken::WrongToken(const std::string &str) : errmsg{str} {}

TokenType WrongToken::Type(void) const noexcept { return TokenType::Wrong; }

std::string WrongToken::Dump(void) const { return errmsg; }

WrongToken::~WrongToken(void) {}

// NUMBER TOKEN

NumberToken::NumberToken(double value) noexcept : value_(value) {}

TokenType NumberToken::Type(void) const noexcept { return TokenType::Number; }

std::string NumberToken::Dump(void) const { return std::to_string(value_); }

double NumberToken::Value(void) const noexcept { return value_; }

NumberToken::~NumberToken(void) {}

// UNARY OP TOKEN

UnaryOpToken::UnaryOpToken(Unop unop) noexcept : unop_{unop} {}

TokenType UnaryOpToken::Type(void) const noexcept { return TokenType::UnaryOp; }

std::string UnaryOpToken::Dump(void) const {
  const char *s = "unknow unop";

  if (unop_ == &unary_ops::plus) {
    s = "+";
  } else if (unop_ == &unary_ops::minus) {
    s = "-";
  }

  return std::string(s);
}

AToken *UnaryOpToken::Apply(const AToken *token) const { return unop_(token); }

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

int BinaryOpToken::Precedence(void) const noexcept {
  int prec = -1;

  if (binop_ == &binary_ops::sum) {
    prec = 1;
  } else if (binop_ == &binary_ops::sub) {
    prec = 1;
  } else if (binop_ == &binary_ops::multiply) {
    prec = 2;
  } else if (binop_ == &binary_ops::devide) {
    prec = 2;
  } else if (binop_ == &binary_ops::power) {
    prec = 2;
  } else if (binop_ == &binary_ops::module) {
    prec = 2;
  }

  return prec;
}

bool BinaryOpToken::LeftAssociative(void) const noexcept {
  return binop_ == &binary_ops::power ? false : true;
}

BinaryOpToken::~BinaryOpToken() {}

// Func TOKEN

FuncToken::FuncToken(Unop unop) noexcept : unop_{unop} {}

TokenType FuncToken::Type(void) const noexcept { return TokenType::Function; }

std::string FuncToken::Dump(void) const {
  const char *s = "unknow function";

  if (unop_ == &unary_ops::sin) {
    s = "sin";
  } else if (unop_ == &unary_ops::cos) {
    s = "cos";
  } else if (unop_ == &unary_ops::tan) {
    s = "tan";
  } else if (unop_ == &unary_ops::asin) {
    s = "asin";
  } else if (unop_ == &unary_ops::acos) {
    s = "acos";
  } else if (unop_ == &unary_ops::atan) {
    s = "atan";
  } else if (unop_ == &unary_ops::ln) {
    s = "ln";
  } else if (unop_ == &unary_ops::log) {
    s = "log";
  }

  return std::string(s);
}

AToken *FuncToken::Apply(const AToken *token) const { return unop_(token); }

FuncToken::~FuncToken() {}

// LEFT BRACKET TOKEN

TokenType LeftBracketToken::Type(void) const noexcept {
  return TokenType::LeftBracket;
}

std::string LeftBracketToken::Dump(void) const { return std::string("("); }

LeftBracketToken::~LeftBracketToken(void) {}

// RIGHT BRACKET TOKEN

TokenType RightBracketToken::Type(void) const noexcept {
  return TokenType::RightBracket;
}

std::string RightBracketToken::Dump(void) const { return std::string(")"); }

RightBracketToken::~RightBracketToken(void) {}

// NAME TOKEN

NameToken::NameToken(const char *str, size_t n) : name_(str, n) {}

TokenType NameToken::Type(void) const noexcept { return TokenType::Name; }

std::string NameToken::Dump(void) const { return name_; }

const char *NameToken::Name(void) const noexcept { return name_.c_str(); }

NameToken::~NameToken(void) {}

// OVERLOAD OPERATOR<< FOR OSTREAM

std::ostream &operator<<(std::ostream &out, TokenType type) {
  if (type == TokenType::Empty) {
    out << "{TokenType:: empty}";
  } else if (type == TokenType::Wrong) {
    out << "{TokenType:: wrong}";
  } else if (type == TokenType::Number) {
    out << "{TokenType:: number}";
  } else if (type == TokenType::UnaryOp) {
    out << "{TokenType:: unary_op}";
  } else if (type == TokenType::BinaryOp) {
    out << "{TokenType:: binary_op}";
  } else if (type == TokenType::Function) {
    out << "{TokenType:: function}";
  } else if (type == TokenType::LeftBracket) {
    out << "{TokenType:: left_bracket}";
  } else if (type == TokenType::RightBracket) {
    out << "{TokenType:: right_bracket}";
  } else if (type == TokenType::Name) {
    out << "{TokenType:: name}";
  } else {
    out << "{TokenType:: unknown}";
  }

  return out;
}

}  // namespace smartcalc

}  // namespace s21
