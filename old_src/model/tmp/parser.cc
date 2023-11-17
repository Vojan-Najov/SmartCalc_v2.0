#include "parser.h"

namespace s21 {

namespace parser {

static std::string
tokens_to_string(const std::deque<std::unique_ptr<AToken*>> &tokens);

std::list<Instruction> lexems_to_instructions(const std::list<std::string> &lexems,
																							const std::list<Variable> &vars,
																							const std::list<Function> &funcs)
{
	(void) lexems;
	(void) vars;
	(void) funcs;

	return std::list<Instruction>{};
}

std::list<std::string>
instructions_to_strings(const std::list<Instruction> &instructions)
{
	std::list<std::string> strings;
	std::list<Instruction>::const_iterator it = instructions.cbegin();
	std::list<Instruction>::const_iterator last = instructions.cend();

	for (; it != last; ++it) {
		strings.push_back(tokens_to_string(*it));
	}

	return strings;
}

static std::string tokens_to_string(const std::deque<std::unique_ptr<AToken*>> &tokens)
{
	std::string str;
	std::deque<std::unique_ptr<AToken*>>::const_iterator it = tokens.cbegin();
	std::deque<std::unique_ptr<AToken*>>::const_iterator last = tokens.cend();

	for (; it != last; ++it) {
		str += std::to_string(***it);// it->dump();
	}

	return str;
}

}  // namespace parser

}  // namespace s21
