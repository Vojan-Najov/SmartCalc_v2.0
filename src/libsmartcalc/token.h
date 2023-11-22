#ifndef LIBSMARTCALC_TOKEN_H_
#define LIBSMARTCALC_TOKEN_H_

#include <iostream>
#include <string>

namespace s21 {

namespace smartcalc {

enum class TokenType {
  Empty,
  Wrong,
  Number,
  UnaryOp,
  BinaryOp,
  // Var,
  Function,
  LeftBracket,
  RightBracket,
  Name,
};

class AToken {
 public:
  virtual TokenType Type(void) const noexcept = 0;
  virtual std::string Dump(void) const = 0;
  virtual ~AToken(void){};
};

class AValue : public AToken {
 public:
  virtual double Value(void) const noexcept = 0;
};

class EmptyToken : public AToken {
 public:
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  ~EmptyToken(void);
};

class WrongToken : public AToken {
 public:
  WrongToken(const std::string &str);
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  ~WrongToken(void);

 public:
  std::string errmsg;
};

class NumberToken : public AValue {
 public:
  NumberToken(double value) noexcept;
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  double Value(void) const noexcept override;
  ~NumberToken(void);

 private:
  double value_;
};

class UnaryOpToken : public AToken {
 public:
  using Unop = AToken *(*)(const AToken *token);

 public:
  UnaryOpToken(Unop unop) noexcept;
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  AToken *Apply(const AToken *token) const;
  ~UnaryOpToken(void);

 private:
  Unop unop_;
};

class BinaryOpToken : public AToken {
 public:
  using Binop = AToken *(*)(const AToken *lhs, const AToken *rhs);

 public:
  BinaryOpToken(Binop binop) noexcept;
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  AToken *Apply(const AToken *lhs, const AToken *rhs) const;
  int Precedence(void) const noexcept;
  bool LeftAssociative(void) const noexcept;
  ~BinaryOpToken(void);

 private:
  Binop binop_;
};

class FuncToken : public AToken {
 public:
  using Unop = AToken *(*)(const AToken *token);

 public:
  FuncToken(Unop unop) noexcept;
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  AToken *Apply(const AToken *token) const;
  ~FuncToken(void);

 private:
  Unop unop_;
};

class LeftBracketToken : public AToken {
 public:
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  ~LeftBracketToken(void);
};

class RightBracketToken : public AToken {
 public:
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  ~RightBracketToken(void);
};

class NameToken : public AToken {
 public:
  NameToken(const char *start, size_t n);
  TokenType Type(void) const noexcept override;
  std::string Dump(void) const override;
  const char *Name(void) const noexcept;
  ~NameToken(void);

 private:
  std::string name_;
};

std::ostream &operator<<(std::ostream &out, TokenType type);

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_TOKEN_H_
