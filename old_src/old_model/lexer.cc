#include <cstring>
#include <cctype>
#include <cerrno>
#include <cstdlib>

#include "calculator.h"

namespace s21 {

ErrorStatus Calculator::split_to_lexems(const char *str,
                                        std::deque<std::unique_ptr<AToken *>> &lexems)
{
	AToken *token = nullptr;
	ErrorStatus err_status = ErrorStatus::NO_ERROR;
	TokenType prev_token_type = TokenType::EMPTY;

	while (*str && !err_status) {
		while (std::isspace(*str)) {
			++str;
		}
		if (!*str) {
			break;
		}

		if (std::isdigit(*str)) {
			token = take_numeric_lexem(str);
		} else if (std::strchr("-+*/:%^=()", *str) != nullptr) {
			token = take_short_lexem(str, prev_token_type);
		} else if (std::strchr("asctlm", *str) != nullptr) {
			// take long lexem;
		}

		if (token == nullptr) {
			if (errno == ERANGE) {
				err_status = ErrorStatus::NUMERIC_RANGE;
			} else {
				err_status = ErrorStatus::UNKNOWN_TOKEN;
			}
		} else {
			prev_token_type = token->type();
			lexems.emplace_back(token);
		}
	}

	return err_status;
}

AToken *Calculator::take_numeric_lexem(const char * &str)
{
	double num;
	char *end{};

	errno = 0;
	num = std::strtod(str, &end);
	if (errno == ERANGE) {
		return nullptr;
	}

	str = end; // mb str = end + 1
	return new NumberToken{num};
}

AToken *Calculator::take_short_lexem(const char * &str, TokenType prev_token_type)
{
	
}

AToken *Calculator::get_short_token(const char * &str, TokenType prev_token_type)
{
	AToken *token = nullptr;

	switch (std::tolower(*str)) {
		case '-':
		case '+':
			if (prev_token_type == TokenType::NUMBER ||
					prev_token_type == TokenType::VAR || prev_token_type == RIGHT_BRACKET) {
				if (*str == '-') {
					token = new BinaryOpToken(&operations::subtract)
				} else {
					token = new BinaryOpToken(&operations::sum);
				}
			} else {
				if (*str == '-') {
					token = new UnaryOpToken(&operations::minus);
				} else {
					token = new UnaryOpToken(&operations::plus);
				}
			}
			break;
		case '*':
			token = new BinaryOpToken(&operations::multiply);
			break;
		case '/'
		case ':'
			token = new BinaryOpToken(&operations::divide);
			break;
		case '%':
			token = new BinaryOpToken(&std::fmod);
			break;
		case '^':
			token = new BinaryOpToken(&std::pow);
			break;
		case '=':
			token = new DefinitonToken();
			break;
		case 'x':
			// token = new VarToken();
			break;
		case 'f':
			// token = new FuncToken();
			break;
		case '(':
			token = new BracketToken('(');
			break;
		case ')':
			token = new BracketToken(')');
			break;
	}
	++str;

	return token;
}

AToken *Calculator::get_long_token(const char * &str)
{
	AToken *token = nullptr;

	if (*str == 'a') {
		if (!std::strncmp(str + 1, "sin", 3)) {
			str += 4;
			token = new UnaryOpToken(&std::asin);
		} else if (!std::strncmp(str + 1, "cos", 3))
			str += 4;
			token = new UnaryOpToken(&std::acos);			
		} else if (!std::strncmp(str + 1, "tan", 3))
			str += 4;
			token = new UnaryOpToken(&std::atan);
		}
	} else if (*str == 'l') {
		if (*(str + 1) == 'n') {
			str += 2;
			token = new UnaryOpToken(&std::log10);
		} else if (*(str + 1) == 'o' && *(str + 2) == 'g') {
			str += 3;
			token = new UnaryOpToken(&std::log);
		}
	} else if (!std::strncmp(str, "sin", 3)) {
		str += 3;
		token = new UnaryOpToken(&std::sin);		
	} else if (!std::strncmp(str, "cos", 3))
		str += 3;
		token = new UnaryOpToken(&std::cos);
	} else if (!std::strncmp(str, "tan", 3))
		str += 3;
		token = new UnaryOpToken(&std::tan);
	} else if (!std::strncmp(str, "sqrt", 4)) {
		str += 4;
		token = new UnaryOpToken(&std::sqrt);
	} else if (!std::strncmp(str, "mod", 3)) {
		str += 3;
		token = new BinaryOpToken(&std::fmod);
	}

	return token;
}

inline std::string Calculator::tokens_to_string(const TokenDeque &lexems) const 
{
	std::string s;
	TokenDequeConstIterator it = lexems.cbegin();
	TokenDequeConstIterator last = lexems.cend();

	while (it != last) {
		AToken *token = it->get();
		s += token->dump();
	}
}

}  // namespace s21

