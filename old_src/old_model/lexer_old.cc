#include "lexer.h"

#include <cctype>
#include <cstdlib>
#include <cstring>

namespace s21 {

Lexer::Lexer(const char *str) : input_(str) {}

ErrorStatus Lexer::GetLexems(std::deque<Token> &lexems) const {
  const char *str = input_.c_str();
  ErrorStatus err_status = ErrorStatus::kNoError;
  Token prev_token = {.type = TokenType::kEmpty, .value = 0.0};

  while (err_status == ErrorStatus::kNoError && *str) {
    Token token;

    GetNextToken(str, token, prev_token, &str);

    if (token.type == TokenType::kWrong) {
      err_status = ErrorStatus::kBadToken;
    } else if (token.type != TokenType::kEmpty) {
      err_status = CheckLastTokens(token.type, prev_token.type);
      if (err_status == ErrorStatus::kNoError) {
        lexems.push_back(token);
      }
    }

    prev_token = token;
  }

  if (err_status == ErrorStatus::kNoError && lexems.empty()) {
    err_status = ErrorStatus::kNoTokens;
  }

  return err_status;
}

void Lexer::GetNextToken(const char *str, Token &token, const Token &prev_token,
                         const char **endptr) const {
  while (std::isspace(*str)) {
    ++str;
  }

  if (*str == '\0') {
    token.type = TokenType::kEmpty;
  } else if (*str == '(') {
    token.type = TokenType::kLeftBracket;
    ++str;
  } else if (*str == ')') {
    token.type = TokenType::kRightBracket;
    ++str;
  } else if (std::tolower(*str) == 'x') {
    token.type = TokenType::kVar;
    ++str;
  } else if (std::isdigit(*str) || (*str == '.' && std::isdigit(*(str + 1)))) {
    char *end_tmp;
    token.type = TokenType::kNumber;
    token.value.num = std::strtod(str, &end_tmp);
    str = end_tmp;
  } else if (std::strchr("-+*/:%^=", *str) != nullptr) {
    GetShortToken(*str, token, prev_token);
    ++str;
  } else {
    GetLongToken(str, token, &str);
  }

  *endptr = str;
}

void Lexer::GetShortToken(char smb, Token &token,
                          const Token &prev_token) const {
  token.type = TokenType::kBinaryOp;

  if (smb == '-' || smb == '+') {
    if (prev_token.type == TokenType::kNumber ||
        prev_token.type == TokenType::kVar ||
        prev_token.type == TokenType::kRightBracket) {
      if (smb == '-') {
        token.value.biop = BinaryOperator::kSub;
      } else {
        token.value.biop = BinaryOperator::kAdd;
      }
    } else {
      token.type = TokenType::kUnaryOp;
      if (smb == '-') {
        token.value.unop = UnaryOperator::kMinus;
      } else {
        token.value.unop = UnaryOperator::kPlus;
      }
    }
  } else if (smb == '*') {
    token.value.biop = BinaryOperator::kMul;
  } else if (smb == '/' || smb == ':') {
    token.value.biop = BinaryOperator::kDiv;
  } else if (smb == '%') {
    token.value.biop = BinaryOperator::kMod;
  } else if (smb == '^') {
    token.value.biop = BinaryOperator::kPow;
  } else if (smb == '=') {
    token.type = TokenType::kAssign;
  } else {
    token.type = TokenType::kWrong;
  }
}

void Lexer::GetLongToken(const char *str, Token &token,
                         const char **endptr) const {
  token.type = TokenType::kFunction;

  if (std::strncmp(str, "sin", 3) == 0) {
    token.value.func = FunctionOperator::kSin;
    str += 3;
  } else if (std::strncmp(str, "cos", 3) == 0) {
    token.value.func = FunctionOperator::kCos;
    str += 3;
  } else if (std::strncmp(str, "tan", 3) == 0) {
    token.value.func = FunctionOperator::kTan;
    str += 3;
  } else if (std::strncmp(str, "asin", 4) == 0) {
    token.value.func = FunctionOperator::kAsin;
    str += 4;
  } else if (std::strncmp(str, "acos", 4) == 0) {
    token.value.func = FunctionOperator::kAcos;
    str += 4;
  } else if (std::strncmp(str, "atan", 4) == 0) {
    token.value.func = FunctionOperator::kAtan;
    str += 4;
  } else if (std::strncmp(str, "sqrt", 4) == 0) {
    token.value.func = FunctionOperator::kSqrt;
    str += 4;
  } else if (std::strncmp(str, "ln", 2) == 0) {
    token.value.func = FunctionOperator::kLn;
    str += 2;
  } else if (std::strncmp(str, "log", 3) == 0) {
    token.value.func = FunctionOperator::kLog;
    str += 3;
  } else if (std::strncmp(str, "mod", 3) == 0) {
    token.type = TokenType::kBinaryOp;
    token.value.biop = BinaryOperator::kMod;
    str += 3;
  } else if (std::tolower(*str) == 'f') {
    token.value.func = FunctionOperator::kF;
    ++str;
  } else {
    token.type = TokenType::kWrong;
  }

  *endptr = str;
}

ErrorStatus Lexer::CheckLastTokens(TokenType cur_token,
                                   TokenType prev_token) const {
  ErrorStatus err_status = ErrorStatus::kNoError;

  if (cur_token == TokenType::kNumber || cur_token == TokenType::kVar) {
    if (prev_token == TokenType::kNumber || prev_token == TokenType::kVar ||
        prev_token == TokenType::kRightBracket) {
      err_status = ErrorStatus::kBadExpr;
    }
    if (prev_token == TokenType::kFunction) {
      err_status = ErrorStatus::kFuncWithoutBracket;
    }
  } else if (cur_token == TokenType::kAssign) {
    if (prev_token != TokenType::kVar && prev_token != TokenType::kFunction) {
      err_status = ErrorStatus::kBadExpr;
    }
  } else if (cur_token == TokenType::kUnaryOp) {
    if (prev_token == TokenType::kFunction) {
      err_status = ErrorStatus::kBadExpr;
    }
  } else if (cur_token == TokenType::kBinaryOp) {
    if (prev_token != TokenType::kNumber && prev_token != TokenType::kVar &&
        prev_token != TokenType::kRightBracket) {
      err_status = ErrorStatus::kBadExpr;
    }
  } else if (cur_token == TokenType::kFunction) {
    if (prev_token == TokenType::kNumber || prev_token == TokenType::kVar ||
        prev_token == TokenType::kFunction ||
        prev_token == TokenType::kRightBracket) {
      err_status = ErrorStatus::kBadExpr;
    }
  } else if (cur_token == TokenType::kLeftBracket) {
    if (prev_token == TokenType::kNumber || prev_token == TokenType::kVar ||
        prev_token == TokenType::kRightBracket) {
      err_status = ErrorStatus::kBadExpr;
    }
  } else if (cur_token == TokenType::kRightBracket) {
    if (prev_token != TokenType::kNumber && prev_token != TokenType::kVar &&
        prev_token != TokenType::kRightBracket) {
      err_status = ErrorStatus::kBadExpr;
    }
  }

  return err_status;
}

}  // namespace s21
