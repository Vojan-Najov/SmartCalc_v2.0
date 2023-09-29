#ifndef MODEL_CALCULATOR_H_
#define MODEL_CALCULATOR_H_

#include <deque>
#include <string>
#include <utility>

#include "function.h"
#include "token.h"
#include "variable.h"

namespace s21 {

class Calculator final {
 public:
  std::string Execute(const char *str);
  int BuildGraph(std::pair<size_t, double *> &graph);

 private:
  // int SplitToLexems(std::deque<Token> &lexems);
  // int ScanExprType(std::deque<Token> &lexems);
  // int ParseToRPN(std::deque<Token> &lexems, std::deque<Token> &rpn);
  // int AssignVar(std::deque<Token> &rpn);
  // int DefineFunc(std::deque<Token> &rpn);
  // int CalculateExpr(std::deque<Token> &rpn);

 private:
  Variable var;
  Function func;
};

}  // namespace s21

#endif  // MODEL_CALCULATOR_H_
