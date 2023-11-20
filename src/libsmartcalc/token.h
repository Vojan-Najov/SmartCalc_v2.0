#ifndef LIBSMARTCALC_TOKEN_H_
#define LIBSMARTCALC_TOKEN_H_

#include <string>

namespace s21 {

enum class TokenType {
  Empty,
  Wrong,
  // Definition,
  Number,
  UnaryOp,
  BinaryOp,
  // Var,
  // Func,
  LeftBracket,
  RightBracket,
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
  ~BinaryOpToken(void);

 private:
  Binop binop_;
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

/*
class NameToken : AToken {
 public:
        NameToken(const char *start, const char *end);
        TokenType type(void) const noexcept override;
        const char *name(void) const noexcept;
 private:
        std::string name_;
};
*/

}  // namespace s21

#endif  // LIBSMARTCALC_TOKEN_H_
