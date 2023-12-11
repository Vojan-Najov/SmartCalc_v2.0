#ifndef LIBSMARTCALC_PARSER_H_
#define LIBSMARTCALC_PARSER_H_

#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <string>

#include "lexer.h"
#include "rpn.h"

namespace s21 {

namespace smartcalc {

class Parser final {
 public:
  using VarMap = std::map<std::string, double>;
  using FuncMap = std::map<std::string, Rpn>;

 public:
  Parser(const char *expr, bool x_is_var = false) noexcept;

 public:
  bool Error(void) const noexcept;
  std::string ErrorMessage(void) const;

 public:
  void SetExpr(const char *expr) noexcept;
  void XisVar(bool flag) noexcept;
  Rpn ToRpn(const VarMap &vars, const FuncMap &funcs);

 private:
  bool ToRpnHandleWrongToken(AToken *token);
  bool ToRpnHandleNumberToken(AToken *token, Rpn &rpn);
  bool ToRpnHandleVarToken(AToken *token, Rpn &rpn);
  bool ToRpnHandleUnaryOpToken(AToken *token,
                               std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleBinaryOpToken(AToken *token,
                                std::stack<std::unique_ptr<AToken>> &stack,
                                Rpn &rpn);
  bool ToRpnHandleFuncToken(AToken *token,
                            std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleLeftBracketToken(AToken *token,
                                   std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleRightBracketToken(AToken *token,
                                    std::stack<std::unique_ptr<AToken>> &stack,
                                    Rpn &rpn);
  AToken *ToRpnHandleNameToken(AToken *token, const VarMap &vars,
                               const FuncMap &funcs);

 private:
  const char *expr_;
  std::string errmsg_;
  TokenType prev_token_;
  bool x_is_var_;
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_PARSER_H_
