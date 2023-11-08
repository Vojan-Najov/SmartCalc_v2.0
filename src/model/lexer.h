#ifndef LIBSMARTCALC_LEXER_H_
#define LIBSMARTCALC_LEXER_H_

#include <string>

// разделители - + * / : ^ % ( )  = mod ; \n

namespace s21 {

class Lexer final {
 public:
	Lexer(const char *str, std::string &errmsg);
	bool empty(void) noexcept;
	std::string next(void);
	bool valid_lexem(const char *lexem);
 private:
	const char *str_;
	std::string &errmsg_;
};

} // namespace s21

#endif // LIBSMARTCALC_LEXER_H_
