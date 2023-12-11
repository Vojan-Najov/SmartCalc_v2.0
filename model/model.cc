#include "model.h"

namespace s21 {

std::string Model::RunExpression(const std::string &expr) {
	size_t assign_idx =  expr.find("=");
	if (assign_idx == std::string::npos) {
		if (!sc_.CalculateExpression(expr.c_str())) {
			return sc_.ErrorMessage();
		} else {
			return std::to_string(sc_.Result());
		}
	}
	return "todo";
}

}  // namespace s21
