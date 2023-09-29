#ifndef MODEL_FUNCTION_H_
#define MODEL_FUNCTION_H_

#include <deque>

namespace s21 {

class Function final {
 public:
  void SetFuncton(std::deque<s21::Token> &&new_rpn) { rpn = new_rpn; }
  void UnsetFunction(void) { rpn.clear(); }

 private:
  std::deque<s21::Token> rpn;
};

}  // namespace s21

#endif  // MODEL_FUNCTION_H_
