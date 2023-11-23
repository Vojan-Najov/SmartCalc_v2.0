#ifndef LIBSMARTCALC_PARSER_H_
#define LIBSMARTCALC_PARSER_H_

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
  Parser(const char *expr) noexcept;
  bool Error(void) const noexcept;
  const std::string &ErrorMessage(void) const noexcept;
  Rpn ToRpn(void);

 private:
  bool ToRpnHandleWrongToken(AToken *token);
  bool ToRpnHandleNumberToken(AToken *token, Rpn &rpn);
  bool ToRpnHandleFuncToken(AToken *token,
                            std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleUnaryOpToken(AToken *token,
                               std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleBinaryOpToken(AToken *token,
                                std::stack<std::unique_ptr<AToken>> &stack,
                                Rpn &rpn);
  bool ToRpnHandleLeftBracketToken(AToken *token,
                                   std::stack<std::unique_ptr<AToken>> &stack);
  bool ToRpnHandleRightBracketToken(AToken *token,
                                    std::stack<std::unique_ptr<AToken>> &stack,
                                    Rpn &rpn);

 private:
  Lexer lexer_;
  std::string errmsg_;
  TokenType prev_token_;
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_PARSER_H_
