#include <list>

#include "parser.h"

namespace s21 {

Parser::Parser(Lexer &lexer, std::string &errmsg) : lexer_(lexer), errmsg_(errmsg) {}

Instruction Parser::parse(void)
{
	std::string assign{"="};
	bool found_assign = false;
	std::list<std::string> left;
	std::list<std::string> right;
	Instruction instruction{InstructionType::ERROR, std::string()};

	errmsg_.clear();

	while (!lexer_.empty()) {
		std::string lexem = lexer_.next();
		if (!errmsg_.empty()) {
			return instruction;
		}
		if (lexem == assign && !found_assign) {
			found_assign = true;
		} else {
			found_assign ? right.push_back(std::move(lexem))
									 : left.push_back(std::move(lexem));
		}
	}

	if (found_assign) {
		instruction.name = std::move(parse_name(left));
		if (!errmsg_.empty()) {
			instruction.name.clear();
			return instruction;
		}
	} else {
		right = std::move(left);
	}

	instruction.tokens = std::move(parse_tokens(right));
	if (!errmsg_.empty()) {
		instruction.name.clear();
		instruction.tokens.clear();
		return instruction;
	}

	if (instruction.name[0] == '_') {
		instruction.type = InstructionType::FUNC_DEF;
	} else {
		instruction.type = InstructionType::VAR_ASSIGN;
	}
	
	return instruction;
}

}  // namespace s21
