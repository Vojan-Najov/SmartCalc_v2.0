#ifndef MODEL_LEXER_H_
#define MODEL_LEXER_H_

#include <string>
#include <list>

// разделители - + * / : ^ % ( )  = mod ; \n

namespace s21 {

class Lexer final {
 public:
	Lexer(const char *str, std::string &errmsg);
	std::bool empty(void) const noexcept;
	std::string next(void);
 private:
	const char *str_;
	std::string &errmsg_;
};

namespace lexer {

std::list<std::string> str_to_lexems(const char *str);

std::string lexems_to_string(const std::list<std::string> &lexems);

} // namespace lexer

} // namespace s21

#endif // MODEL_LEXER_H_
