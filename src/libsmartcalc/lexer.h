#ifndef LIBSMARTCALC_LEXER_H_
#define LIBSMARTCALC_LEXER_H_

#include <string.h>

#include "token.h"

namespace s21 {

class Lexer final {
 public:
	Lexer(const char *expr) noexcept;
	bool Empty() const noexcept;
	AToken *NextToken(void);

 private:
	AToken *SingleCharacterLexem(char smb) const;

 private:
	const char *expr_;
	TokenType prev_token_;
};

}  // namespace s21

#endif  // LIBSMARTCALC_LEXER_H_
