#include "controller.h"

namespace s21 {

std::string Controller::RunExpression(const std::string &expr) {
	return model_.RunExpression(expr);
}

}  // namespace s21
