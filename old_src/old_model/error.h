#ifndef MODEL_ERROR_H_
#define MODEL_ERROR_H_

#include <string.h>

namespace s21 {

enum class ErrorStatus {
	NO_ERROR = 0,
	UNKNOWN_TOKEN,
  kNoError = 0,
  kBadToken = 1,
  kNoTokens = 2,
  kBadExpr = 3,
  kFuncWithoutBracket = 4,
};

std::string get_error_string(ErrorStatus err_status);

}  // namespace s21

#endif  // MODEL_ERROR_H_
