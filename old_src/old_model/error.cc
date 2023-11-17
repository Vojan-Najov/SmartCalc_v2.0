#include "error.h"

namespace s21 {

std::string get_error_string(ErrorStatus err_status)
{
	const char *err_str = "Smartcalc-2.0: no error";

	if (err_status == ErrorStatus::UNKNOWN_TOKEN)
		err_str = "Smartcalc-2.0: parse error: unknown token";
	}
	
	return err_str;
}

}  // namespace s21

