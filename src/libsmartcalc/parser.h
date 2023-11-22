#ifndef LIBSMARTCALC_PARSER_H_
#define LIBSMARTCALC_PARSER_H_

#include <memory>
#include <queue>
#include <stack>

#include "lexer.h"

namespace s21 {

namespace smartcalc {

class Parser final {
 public:
	Parser(const char *expr) noexcept;
	bool ToRpn(std::queue<std::unique_ptr<AToken>> &rpn);

 private:
	bool ToRpnHandleWrongToken(AToken *token);
	bool ToRpnHandleNumberToken(AToken *token,
                              std::queue<std::unique_ptr<AToken>> &rpn);
	bool ToRpnHandleFuncToken(AToken *token,
                            std::stack<std::unique_ptr<AToken>> &stack);
	bool ToRpnHandleUnaryOpToken(AToken *token,
                               std::stack<std::unique_ptr<AToken>> &stack);
	bool ToRpnHandleBinaryOpToken(AToken *token,
                                std::stack<std::unique_ptr<AToken>> &stack,
                                std::queue<std::unique_ptr<AToken>> &rpn);
	bool ToRpnHandleLeftBracketToken(AToken *token,
                                   std::stack<std::unique_ptr<AToken>> &stack);
	bool ToRpnHandleRightBracketToken(AToken *token,
                                    std::stack<std::unique_ptr<AToken>> &stack,
                                    std::queue<std::unique_ptr<AToken>> &rpn);

 private:
	Lexer lexer_;
	std::string errmsg_;
	TokenType prev_token_;
};

}  // namespace smartcalc

}  // namespace s21


#endif  // LIBSMARTCALC_PARSER_H_
