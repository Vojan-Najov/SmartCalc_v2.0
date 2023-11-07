#include <cstring>

#include "lexer.h"

namespace s21 {

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

