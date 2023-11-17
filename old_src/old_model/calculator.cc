#include "calculator.h"

namespace s21 {

std::string Calculator::calculate_expr(const char *str)
{
	ErrorStatus err_status;
	std::deque<std::unique_ptr<AToken *>> lexems;

	err_status = split_to_lexems(str, lexems);
	if (err_status) {
		return error::get_error_string(err_status);
	}
	return tokens_to_string(lexems);
}

}  // namespace s21
