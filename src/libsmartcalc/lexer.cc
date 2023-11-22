#include "lexer.h"

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstring>

#include "operations.h"

namespace s21 {

namespace smartcalc {

Lexer::Lexer(const char *expr) noexcept
    : expr_{expr}, prev_token_{TokenType::Empty} {
  while (std::isspace(*expr_)) {
    ++expr_;
  }
}

bool Lexer::Empty(void) const noexcept { return *expr_ == '\0'; }

AToken *Lexer::NextToken(void) {
  AToken *token = nullptr;

  if (!*expr_) {
    token = new EmptyToken{};
  } else if (std::strchr("-+*/^%()", *expr_) != nullptr) {
    token = SingleCharacterLexem();
  } else if (std::strncmp(expr_, "mod", 3) == 0) {
    token = new BinaryOpToken{&binary_ops::module};
    expr_ += 3;
  } else if (std::isdigit(*expr_)) {
    token = NumericLexem();
  } else {
    token = MultiCharacterLexem();
  }

  prev_token_ = token->Type();
  while (std::isspace(*expr_)) {
    ++expr_;
  }

  return token;
}

AToken *Lexer::SingleCharacterLexem(void) {
  AToken *token = nullptr;

  switch (*expr_) {
    case '-':
    case '+':
      if (prev_token_ == TokenType::Number || prev_token_ == TokenType::Name ||
          prev_token_ == TokenType::RightBracket) {
        token = *expr_ == '+' ? new BinaryOpToken{&binary_ops::sum}
                              : new BinaryOpToken{&binary_ops::sub};
      } else {
        token = *expr_ == '+' ? new UnaryOpToken{&unary_ops::plus}
                              : new UnaryOpToken{&unary_ops::minus};
      }
      break;
    case '*':
      token = new BinaryOpToken{&binary_ops::multiply};
      break;
    case '/':
      token = new BinaryOpToken{&binary_ops::devide};
      break;
    case '^':
      token = new BinaryOpToken{&binary_ops::power};
      break;
    case '%':
      token = new BinaryOpToken{&binary_ops::module};
      break;
    case '(':
      token = new LeftBracketToken{};
      break;
    case ')':
      token = new RightBracketToken{};
      break;
    default:
      token = new WrongToken{"unknown unary op"};
  }
  if (*expr_) {
    ++expr_;
  }

  return token;
}

AToken *Lexer::NumericLexem(void) {
  AToken *token = nullptr;
  char *end{};
  errno = 0;
  double num = std::strtod(expr_, &end);

  if (errno == ERANGE) {
    token = new WrongToken(std::string(expr_, end - expr_) + ": huge value");
    errno = 0;
  } else {
    token = new NumberToken{num};
  }
  expr_ = end;

  return token;
}

AToken *Lexer::MultiCharacterLexem(void) {
  AToken *token = nullptr;
  const char *end = expr_;

  while (*end && !std::isspace(*end) &&
         std::strchr("-+*/^%()", *end) == nullptr &&
         std::strncmp(end, "mod", 3) != 0) {
    ++end;
  }

	size_t n = end - expr_;
  if (n == 2 && std::strncmp(expr_, "ln", 2) == 0) {
    token = new FuncToken{&unary_ops::ln};
  } else if (n == 3 && std::strncmp(expr_, "log", 3) == 0) {
    token = new FuncToken{&unary_ops::log};
  } else if (n == 3 && std::strncmp(expr_, "sin", 3) == 0) {
    token = new FuncToken{&unary_ops::sin};
  } else if (n == 3 && std::strncmp(expr_, "cos", 3) == 0) {
    token = new FuncToken{&unary_ops::cos};
  } else if (n == 3 && std::strncmp(expr_, "tan", 3) == 0) {
    token = new FuncToken{&unary_ops::tan};
  } else if (n == 4 && std::strncmp(expr_, "asin", 4) == 0) {
    token = new FuncToken{&unary_ops::asin};
  } else if (n == 4 && std::strncmp(expr_, "acos", 4) == 0) {
    token = new FuncToken{&unary_ops::acos};
  } else if (n == 4 && std::strncmp(expr_, "atan", 4) == 0) {
    token = new FuncToken{&unary_ops::atan};
  } else {
    token = new NameToken{expr_, n};
  }
  expr_ += n;

  return token;
}

}  // namespace smartcalc

}  // namespace s21
