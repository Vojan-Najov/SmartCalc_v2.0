#include <cstring>

#include "lexer.h"

namespace s21 {

Lexer::Lexer(const char *str, std::string &errmsg) : str_(str), errmsg_(errmsg)
{
	while (std::isspace(*str_)) ++str_;
}

bool Lexer::empty(void) noexcept
{
	return *str_ == '\0';
}

std::string Lexer::next(void)
{
	const char *end;
	std::string lexem;
	
	while (std::isspace(*str_)) {
		++str_;
	}

	if (*str_) {
 		if (std::strchr("-+*/^%()=", *str_) != nullptr) {
			lexem = std::string(1, *str_);
			++str_;
		} else if (std::strncmp(str_, "mod", 3) == 0) {
			lexem = std::string(1, '%');
			str_ += 3;
		} else {
			end = str_;
			while (*end && !std::isspace(*end) &&
  	         std::strchr("-+*/:^%()=;", *end) == nullptr &&
  	         std::strncmp(end, "mod", 3) != 0) {
				++end;
			}
			lexem = std::string{str_, end};
			if (!valid_lexem(lexem.c_str())) {
				errmsg_ = std::string{"Smartcalc-v2.0: "} +
									lexem + std::string{"invalid lexem."};
			}
			str_ = end;
		}
	}

	while (std::isspace(*str_)) {
		++str_;
	}

	return lexem;
}

bool Lexer::valid_lexem(const char *lexem)
{
	(void) lexem;
	//if (std::isdigt(*lexem)) { }
	return true;
}

} // namespace s21

