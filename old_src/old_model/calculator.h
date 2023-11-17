#ifndef MODEL_CALCULATOR_H_
#define MODEL_CALCULATOR_H_

#include <deque>
#include <string>
#include <utility>

#include "token.h"
#include "function.h"
#include "variable.h"

namespace s21 {

class Calculator final {
 public:
	using TokenDeque =
		std::deque<std::unique_ptr<AToken *>>;
	using TokenDequeIterator =
		std::deque<std::unique_ptr<AToken *>>::iterator;
	using TokenDequeConstIterator = 
		std::deque<std::unique_ptr<AToken *>>::const_iterator;

 public:
	std::string calculate_expr(const char *str);
	//...         calculate_graph(...);

 private:
	ErrorStatus split_to_lexems(const char *str, std::deque<AToken *> &tokens);
	AToken *get_short_token(const char * &str, TokenType prev_token_type);
	AToken *get_long_token(const char * &str);

  // int SplitToLexems(std::deque<Token> &lexems);
  // int ScanExprType(std::deque<Token> &lexems);
  // int ParseToRPN(std::deque<Token> &lexems, std::deque<Token> &rpn);
  // int AssignVar(std::deque<Token> &rpn);
  // int DefineFunc(std::deque<Token> &rpn);
  // int CalculateExpr(std::deque<Token> &rpn);
 private:
	std::string tokens_to_string(const std::deque<std::unique_ptr<AToken *>> &lexems);

 private:
  Variable var_;
  Function func_;
};

}  // namespace s21

#endif  // MODEL_CALCULATOR_H_
