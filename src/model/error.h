#ifndef MODEL_ERROR_H_
#define MODEL_ERROR_H_

namespace s21 {

enum class ErrorStatus {
  kNoError = 0,
  kBadToken = 1,
  kNoTokens = 2,
  kBadExpr = 3,
  kFuncWithoutBracket = 4,
};

}  // namespace s21

#endif  // MODEL_ERROR_H_
