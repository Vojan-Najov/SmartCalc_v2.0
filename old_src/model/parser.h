#ifndef LIBSMARTCALC_PARSER_H_
#define LIBSMARTCALC_PARSER_H_

#include "lexer.h"
#include "instruction.h"

#include <string>

namespace s21 {

class Parser final
{
 public:
	Parser(Lexer &lexer, std::string &errmsg);

	Instruction parse(void);

 private:
	std::string parse_name(std::list<std::string> &lexems);
	

 private:
	Lexer &lexer_;
	std::string &errmsg_;
};

} // namespace s21

#endif  // LIBSMARTCALC_PARSER_H_

