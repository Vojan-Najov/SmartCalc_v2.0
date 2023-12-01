#include "token.h"

#include "operations.h"

namespace s21 {

namespace smartcalc {

/*
 *  EMPTY TOKEN
 */

EmptyToken::EmptyToken(void) : AToken{TokenType::Empty} {}

EmptyToken::~EmptyToken(void) {}

EmptyToken *EmptyToken::clone(void) const { return new EmptyToken{}; }

std::string EmptyToken::dump(void) const { return ""; }

/*
 *  WRONG TOKEN
 */

WrongToken::WrongToken(const std::string &str)
    : AToken{TokenType::Wrong}, errmsg{str} {}

WrongToken::~WrongToken(void) {}

WrongToken *WrongToken::clone(void) const { return new WrongToken{errmsg}; }

std::string WrongToken::dump(void) const { return errmsg; }

/*
 *  NUMBER TOKEN
 */

NumberToken::NumberToken(double value)
    : AToken{TokenType::Number}, value{value} {}

NumberToken::~NumberToken(void) {}

NumberToken *NumberToken::clone(void) const { return new NumberToken{value}; }

std::string NumberToken::dump(void) const { return std::to_string(value); }

/*
 *  VAR TOKEN
 */

VarToken::VarToken(void) : AToken{TokenType::Var} {}

VarToken::~VarToken(void) {}

VarToken *VarToken::VarToken::clone(void) const { return new VarToken{}; }

std::string VarToken::dump(void) const { return "x"; };

/*
 *  UNARY OPERATOR TOKEN
 */

UnaryOpToken::UnaryOpToken(Unop unop)
    : AToken{TokenType::UnaryOp}, apply{unop} {}

UnaryOpToken::~UnaryOpToken() {}

UnaryOpToken *UnaryOpToken::clone(void) const {
  return new UnaryOpToken{apply};
}

std::string UnaryOpToken::dump(void) const {
  const char *s = "{unknow unop}";

  if (apply == &unary_ops::plus) {
    s = "+";
  } else if (apply == &unary_ops::minus) {
    s = "-";
  }

  return std::string{s};
}

/*
 *  BINARY OPERATOR TOKEN
 */

BinaryOpToken::BinaryOpToken(Binop binop)
    : AToken{TokenType::BinaryOp}, apply{binop} {}

BinaryOpToken::~BinaryOpToken() {}

BinaryOpToken *BinaryOpToken::clone(void) const {
  return new BinaryOpToken{apply};
}

std::string BinaryOpToken::dump(void) const {
  const char *s = "{unknow binop}";

  if (apply == &binary_ops::sum) {
    s = "+";
  } else if (apply == &binary_ops::sub) {
    s = "-";
  } else if (apply == &binary_ops::multiply) {
    s = "*";
  } else if (apply == &binary_ops::devide) {
    s = "/";
  } else if (apply == &binary_ops::power) {
    s = "^";
  } else if (apply == &binary_ops::modulo) {
    s = "%";
  }

  return std::string{s};
}

int BinaryOpToken::precedence(void) const noexcept {
  int prec = -1;

  if (apply == &binary_ops::sum) {
    prec = 1;
  } else if (apply == &binary_ops::sub) {
    prec = 1;
  } else if (apply == &binary_ops::multiply) {
    prec = 2;
  } else if (apply == &binary_ops::devide) {
    prec = 2;
  } else if (apply == &binary_ops::power) {
    prec = 2;
  } else if (apply == &binary_ops::modulo) {
    prec = 2;
  }

  return prec;
}

bool BinaryOpToken::left_associative(void) const noexcept {
  return apply == &binary_ops::power ? false : true;
}

/*
 *  FUNCTION TOKEN
 */

FuncToken::FuncToken(Func func) : AToken{TokenType::Function}, apply{func} {}

FuncToken::~FuncToken() {}

FuncToken *FuncToken::clone(void) const { return new FuncToken{apply}; }

std::string FuncToken::dump(void) const {
  const char *s = "unknow function";

  if (apply == &funcs::sin) {
    s = "sin";
  } else if (apply == &funcs::cos) {
    s = "cos";
  } else if (apply == &funcs::tan) {
    s = "tan";
  } else if (apply == &funcs::asin) {
    s = "asin";
  } else if (apply == &funcs::acos) {
    s = "acos";
  } else if (apply == &funcs::atan) {
    s = "atan";
  } else if (apply == &funcs::ln) {
    s = "ln";
  } else if (apply == &funcs::log) {
    s = "log";
  }

  return std::string(s);
}

/*
 *  LEFT BRACKET TOKEN
 */

LeftBracketToken::LeftBracketToken(void) : AToken{TokenType::LeftBracket} {}

LeftBracketToken::~LeftBracketToken(void) {}

LeftBracketToken *LeftBracketToken::clone(void) const {
  return new LeftBracketToken{};
}

std::string LeftBracketToken::dump(void) const { return "("; }

/*
 *  RIGHT BRACKET TOKEN
 */

RightBracketToken::RightBracketToken(void) : AToken{TokenType::RightBracket} {}

RightBracketToken *RightBracketToken::clone(void) const {
  return new RightBracketToken{};
}

std::string RightBracketToken::dump(void) const { return ")"; }

RightBracketToken::~RightBracketToken(void) {}

/*
 *  NAME TOKEN
 */

NameToken::NameToken(const char *str, size_t n)
    : AToken{TokenType::Name}, name(str, n) {}

NameToken::NameToken(const std::string &name)
    : AToken{TokenType::Name}, name(name) {}

NameToken::~NameToken(void) {}

NameToken *NameToken::clone(void) const { return new NameToken{name}; }

std::string NameToken::dump(void) const { return name; }

/*
 *  OVERLOAD OSTREAM OPERATOR << FOR TOKEN TYPE
 */

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
