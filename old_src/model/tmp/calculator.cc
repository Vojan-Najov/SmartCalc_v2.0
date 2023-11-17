#include "lexer.h"
#include "calculator.h"


Calculator::Calculator(void)
{
	
}

Calculator::calculate(const char *str)
{
	Lexer lexer{str, errmsg_};
	Parser parser{lexer, errmsg_};
	Instruction instr = parser.parse(vars_, funcs_);

	if (instr.type == InstructionType::EXPRESSION) {
		return calculate_expr(instr.tokens);
	} else if (instr.type == InstructionType::VAR_ASSIGN) {
		return assign_variable(instr);
	} else if (instr.type == InstructionType::FUNC_DEFINITION) 
		return defintion_user_function(instr);
	} else {
		return errmsg_;
	}
}
