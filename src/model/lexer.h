#ifndef MODEL_LEXER_H_
#define MODEL_LEXER_H_

#include <deque>
#include <string>

#include "error.h"
#include "token.h"

namespace s21 {

class Lexer final {
 public:
  Lexer(const char *str);

  ErrorStatus GetLexems(std::deque<Token> &lexems) const;

 private:
  void GetNextToken(const char *str, Token &token, const Token &prev_token,
                    const char **endptr) const;

  void GetShortToken(char smb, Token &token, const Token &prev_token) const;

  void GetLongToken(const char *str, Token &token, const char **endptr) const;

  ErrorStatus CheckLastTokens(TokenType cur_token, TokenType prev_toke) const;

 private:
  std::string input_;
};

}  // namespace s21

#endif  // MODEL_LEXER_H_
