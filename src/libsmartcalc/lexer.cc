#include "lexer.h"

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstring>

#include "operations.h"

namespace s21 {

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
  } else if (*expr_ && std::strchr("-+*/^%()", *expr_) != nullptr) {
    token = SingleCharacterLexem(*expr_);
    ++expr_;
  } else if (std::strncmp(expr_, "mod", 3) == 0) {
    token = SingleCharacterLexem('%');
    expr_ += 3;
  } else if (std::isdigit(*expr_)) {
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
  } else {
    const char *end = expr_;
    while (*end && !std::isspace(*end) &&
           std::strchr("-+*/^%()", *end) == nullptr &&
           std::strncmp(end, "mod", 3) != 0) {
      ++end;
    }
    // token = MultiCharacterLexem(expr_, end);
    expr_ = end;
  }

  prev_token_ = token->Type();
  while (std::isspace(*expr_)) {
    ++expr_;
  }

  return token;
}

AToken *Lexer::SingleCharacterLexem(char smb) const {
  AToken *token = nullptr;

  switch (smb) {
    case '-':
    case '+':
      if (prev_token_ == TokenType::Number) {
        token = smb == '+' ? new BinaryOpToken{&binary_ops::sum}
                           : new BinaryOpToken{&binary_ops::sub};
      } else {
        token = smb == '+' ? new UnaryOpToken{&unary_ops::plus}
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

  return token;
}

}  // namespace s21
