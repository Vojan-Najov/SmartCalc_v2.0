#ifndef LIBSMARTCALC_TOKEN_H_
#define LIBSMARTCALC_TOKEN_H_

#include <iostream>
#include <string>

namespace s21 {

namespace smartcalc {

/*
 *  TOKEN TYPES
 */
enum class TokenType {
  Empty,
  Wrong,
  Number,
  Var,
  UnaryOp,
  BinaryOp,
  Function,
  LeftBracket,
  RightBracket,
  Name,
};

/*
 *  ABSTRACT TOKEN CLASS
 */
class AToken {
 public:
  const TokenType type;

 public:
  AToken(TokenType type) : type{type} {}
  virtual ~AToken(void) {}

 public:
  virtual AToken *clone(void) const = 0;
  virtual std::string dump(void) const = 0;
};

/*
 *  EMPTY TOKEN
 */
class EmptyToken : public AToken {
 public:
  EmptyToken(void);
  ~EmptyToken(void);

 public:
  EmptyToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  WRONG TOKEN
 */
class WrongToken : public AToken {
 public:
  std::string errmsg;

 public:
  WrongToken(const std::string &str);
  ~WrongToken(void);

 public:
  WrongToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  NUMBER TOKEN
 */
class NumberToken : public AToken {
 public:
  double value;

 public:
  NumberToken(double value);
  ~NumberToken(void);

 public:
  NumberToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  VAR TOKEN
 */
class VarToken : public AToken {
 public:
  VarToken(void);
  ~VarToken(void);

 public:
  VarToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  UNARY OPERATOR TOKEN
 */
class UnaryOpToken : public AToken {
 public:
  using Unop = AToken *(*)(const NumberToken *token);

 public:
  Unop apply;

 public:
  UnaryOpToken(Unop unop);
  ~UnaryOpToken(void);

 public:
  UnaryOpToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  BINARY OPERATOR TOKEN
 */
class BinaryOpToken : public AToken {
 public:
  using Binop = AToken *(*)(const NumberToken *lhs, const NumberToken *rhs);

 public:
  Binop apply;

 public:
  BinaryOpToken(Binop binop);
  ~BinaryOpToken(void);

 public:
  BinaryOpToken *clone(void) const override;
  std::string dump(void) const override;

 public:
  int precedence(void) const noexcept;
  bool left_associative(void) const noexcept;
};

/*
 * BUILT IN FUNCTION TOKEN
 */
class FuncToken : public AToken {
 public:
  using Func = AToken *(*)(const NumberToken *token);

 public:
  Func apply;

 public:
  FuncToken(Func func);
  ~FuncToken(void);

 public:
  FuncToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  LEFT BRACKET TOKEN
 */
class LeftBracketToken : public AToken {
 public:
  LeftBracketToken(void);
  ~LeftBracketToken(void);

 public:
  LeftBracketToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  RIGHT BRACKET TOKEN
 */
class RightBracketToken : public AToken {
 public:
  ~RightBracketToken(void);
  RightBracketToken(void);

 public:
  RightBracketToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  NAME TOKEN
 */
class NameToken : public AToken {
 public:
  std::string name;

 public:
  NameToken(const char *str, size_t n);
  NameToken(const std::string &name);
  ~NameToken(void);

 public:
  NameToken *clone(void) const override;
  std::string dump(void) const override;
};

/*
 *  OVERLOADING OSTREAM OPERATOR << TOKEN TYPE
 */
std::ostream &operator<<(std::ostream &out, TokenType type);

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_TOKEN_H_
