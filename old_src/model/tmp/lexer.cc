#include <cstring>

#include "lexer.h"

namespace s21 {

Lexer::Lexer(const char *str, std::string &errmsg) : str_(str), errmsg_(errmsg) {}

inline std::bool Lexer::empty(void) const noexcept { return *str_ == '\0' }

std::string Lexer::next(void)
{
	const char *end;
	std::string lexem;
	
	while (std::isspace(*str_)) {
		++str_;
	}

  if (std::strchr("-+*/:^%()=", *str_) != nullptr) {
		res = std::to_string(*str_++);
	} else if (std::strncmp(str_, "mod", 3) == 0) {
		res = std::to_string('%');
		str_ += 3;
	} else {
		end = str_;
		while (*end && !std::isspace(*end) &&
           std::strchr("-+*/:^%()=;", *end) == nullptr &&
           std::strncmp(end, "mod", 3) != 0) {
			++end;
		}
			res = std::string{str_, end}
			str_ = end;
		}
	}
}

namespace lexer {

std::list<std::string> str_to_lexems(const char *str)
{
	const char *end;
	std::list<std::string> lexems;

	while (std::isspace(*str)) {
		++str;
	}

	while (*str) {
    if (std::strchr("-+*/:^%()=;", *str) != nullptr) {
			lexems.push_back(std::string{str, 1});
			++str;
		} else if (std::strncmp(str, "mod", 3) == 0) {
			lexems.push_back(std::string{"%"});
			str += 3;
		} else {
			end = str;
			while (*end && !std::isspace(*end) &&
             std::strchr("-+*/:^%()=;", *end) == nullptr &&
             std::strncmp(end, "mod", 3) != 0) {
			  ++end;
			}
			lexems.push_back(std::string{str, end});
			str = end;
		}

		while (std::isspace(*str)) {
			++str;
		}
	}

	return lexems;
}

std::string lexems_to_string(const std::list<std::string> &lexems)
{
	std::string str;
	std::list<std::string>::const_iterator it = lexems.cbegin();
	std::list<std::string>::const_iterator last = lexems.cend();

	for (; it != last; ++it) {
		str += *it;
	}
	
	return str;
}

} // namespace lexer

} // namespace s21

