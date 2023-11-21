#ifndef LIBSMARTCALC_LEXER_H_
#define LIBSMARTCALC_LEXER_H_

#include <string.h>

#include "token.h"

namespace s21 {

namespace smartcalc {

class Lexer final {
 public:
  Lexer(const char *expr) noexcept;
  bool Empty() const noexcept;
  AToken *NextToken(void);

 private:
  AToken *SingleCharacterLexem(void);
  AToken *NumericLexem(void);
  AToken *MultiCharacterLexem(void);

 private:
  const char *expr_;
  TokenType prev_token_;
};

}  // namespace smartcalc

}  // namespace s21

#endif  // LIBSMARTCALC_LEXER_H_
