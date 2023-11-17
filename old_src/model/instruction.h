#ifndef LIBSMARTCALC_INSTRUCTION_H_
#define LIBSMARTCALC_INSTRUCTION_H_

namespace s21 {

enum class InstructionType
{
	ERROR,
	EXPRESSION,
	VAR_ASSIGN,
	FUNC_DEF
};

struct Instruction
{
	InstructionType type;
	std::string name;
};

}  // namespace s21

#endif  // LIBSMARTCALC_INSTRUCTION_H_
