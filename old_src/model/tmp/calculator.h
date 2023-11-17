#ifndef MODEL_CALCULATOR_H_
#define MODEL_CALCULATOR_H_

#include <cmath>

namespace s21 {

class Calculator final
{
 public:
	Calculator(void);
 public:
	std::string calculate(const char *str);

 private:
	class Error;
	class Lexer;
	class Parser;
	class Instruction;

 private:
	std::map<std::string, double> vars_;
	std::map<std::string, std::shared_ptr<AToken *>> funcs_;

	std::map<std::string, std::shared_ptr<AToken *>> vars_;
};

std::pair<Expression, std::deque<...>> parser(...);
p = parser;
p.first.type == Expression
	result = calculate(p.second);
p.first.type == Assign
	result = calculate(p.second);
	vars_[p.first.name] = new NumberToken{result};
p.first.type == Definition
	make_simple(p.second);
	funcs_[p.first.name] = new UserFunction(p.second);

struct Expression {
	ExpressionType type;
	std::string name;
};

... calculate(...)
{
	error_.status = ErrorType::NO_ERROR;

	Instruction instr = parser_.parse(str);
	if (error_.status) {
		return error_.msg;
	}


	if (instr.type == InstructionType::Expression) {
		result_ = calculate_expr(inst.tokens);
		if (std::is_nanresult
	}
	
}

struct Calculator::Instruction
{
	InstructionType type;
	std::string name;
	std::deque<std::shared_ptr<AToken*>> tokens;
};

class Calculator::Lexer
{
 public:
	explicit Lexer(const char *str);
	std::bool empty(void) const;
	std::string next_lexem(void);
 private:
	const char *str_;
};

class Calculator::Parser
{
	static Instruction parse(const char *str);
};

Calculator::Calculator(void) : result_(std::nan("0"))
{
	funcs_["sin"] = new Function{&operations::sin};
	funcs_["cos"] = new Function{&operations::cos};
	funcs_["tan"] = new Function{&operations::tan};
	funcs_["asin"] = new Function{&operations::asin};
	funcs_["acos"] = new Function{&operations::acos};
	funcs_["atan"] = new Function{&operations::atan};
	funcs_["ln"] = new Function{&operations::ln};
	funcs_["log"] = new Function{&operations::log};
}

Calculator::~Calculator(void)
{
	std::map<std::string, Function>::iterator it = funcs_.begin();
	std::map<std::string, Function>::iterator last = funcs_.begin();

	for (; it != last; ++it) {
		delete it->second;
	}
}

std::pair<std::deque<...>> parser(...)

p = parser;
if p.front()->type == result
	


class AFunctional
{
 public:
	virtual NumberToken *call(AValuable *obj) = 0;
	virtual ~AFunctional(void) = 0;
};

class Function : AFunctional
{
 public:
	NumberToken *call(AValuable *obj) {
		return new NumberToken(fptr_(obj->value()));
	}

 private:
	double (*fptr_)(double, double);
};

}  // namespace s21

#endif  // MODEL_CALCULATOR_H_
