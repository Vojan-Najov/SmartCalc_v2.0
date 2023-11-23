#include "parser.h"

#include <iostream>

namespace s21 {

namespace smartcalc {

Parser::Parser(const char *expr) noexcept
    : lexer_{expr}, errmsg_{}, prev_token_{TokenType::Empty} {}

bool Parser::Error(void) const noexcept { return !errmsg_.empty(); }

const std::string &Parser::ErrorMessage(void) const noexcept { return errmsg_; }

Rpn Parser::ToRpn(void) {
  Rpn rpn;
  bool err_status = false;
  std::stack<std::unique_ptr<AToken>> stack;

  while (!lexer_.Empty() && !err_status) {
    AToken *token = lexer_.NextToken();

    if (token->Type() == TokenType::Wrong) {
      err_status = ToRpnHandleWrongToken(token);
    } else if (token->Type() == TokenType::Number) {
      err_status = ToRpnHandleNumberToken(token, rpn);
    } else if (token->Type() == TokenType::Function) {
      err_status = ToRpnHandleFuncToken(token, stack);
    } else if (token->Type() == TokenType::UnaryOp) {
      err_status = ToRpnHandleUnaryOpToken(token, stack);
    } else if (token->Type() == TokenType::BinaryOp) {
      err_status = ToRpnHandleBinaryOpToken(token, stack, rpn);
    } else if (token->Type() == TokenType::LeftBracket) {
      err_status = ToRpnHandleLeftBracketToken(token, stack);
    } else if (token->Type() == TokenType::RightBracket) {
      err_status = ToRpnHandleRightBracketToken(token, stack, rpn);
    }
  }

  if (!err_status && prev_token_ != TokenType::RightBracket &&
      prev_token_ != TokenType::Number) {
    errmsg_ = std::string{"parser: error near the end of the line"};
    // rpn.clear();
  }

  while (!stack.empty() && !err_status) {
    std::unique_ptr<AToken> &op = stack.top();
    if (op->Type() == TokenType::LeftBracket) {
      errmsg_ = std::string{"parser: unpaired brackets"};
      err_status = true;
    } else {
      // rpn.emplace(std::move(op));
      rpn.Push(op);
      stack.pop();
    }
  }

  return rpn;
}

bool Parser::ToRpnHandleWrongToken(AToken *token) {
  errmsg_ = std::move(static_cast<WrongToken *>(token)->errmsg);
  delete token;
  prev_token_ = TokenType::Wrong;
  return true;
}

bool Parser::ToRpnHandleNumberToken(AToken *token, Rpn &rpn) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  rpn.Push(token);
  prev_token_ = TokenType::Number;

  return false;
}

bool Parser::ToRpnHandleFuncToken(AToken *token,
                                  std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.emplace(token);
  prev_token_ = TokenType::Function;

  /*
          token = lexer_.NextToken();
          if (token->Type() != TokenType::LeftBracket) {
                  errmsg_ = std::string{"parser: error near token "} +
     stack.top()->Dump(); delete token; prev_token_ = TokenType::Wrong; return
     true;
          }

          stack.emplace(token);
          prev_token_ = TokenType::LeftBracket;
  */
  return false;
}

bool Parser::ToRpnHandleUnaryOpToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.emplace(token);
  prev_token_ = TokenType::UnaryOp;

  return false;
}

bool Parser::ToRpnHandleBinaryOpToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack, Rpn &rpn) {
  if (prev_token_ != TokenType::Number &&
      prev_token_ != TokenType::RightBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  while (!stack.empty()) {
    std::unique_ptr<AToken> &op = stack.top();
    if (op->Type() == TokenType::UnaryOp) {
      // rpn.Push(std::move(op));
      rpn.Push(op);
      stack.pop();
    } else if (op->Type() == TokenType::BinaryOp) {
      int cur_precedence = static_cast<BinaryOpToken *>(token)->Precedence();
      int op_precedence = static_cast<BinaryOpToken *>(op.get())->Precedence();
      bool left_associative =
          static_cast<BinaryOpToken *>(token)->LeftAssociative();

      if (op_precedence > cur_precedence ||
          ((op_precedence == cur_precedence) && left_associative)) {
        // rpn.Push(std::move(op));
        rpn.Push(op);
        stack.pop();
      } else {
        break;
      }
    } else {
      break;
    }
  }

  stack.emplace(token);
  prev_token_ = TokenType::BinaryOp;
  return false;
}

bool Parser::ToRpnHandleLeftBracketToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket &&
      prev_token_ != TokenType::Function) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.emplace(token);
  prev_token_ = TokenType::LeftBracket;

  return false;
}

bool Parser::ToRpnHandleRightBracketToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack, Rpn &rpn) {
  delete token;

  if (prev_token_ != TokenType::Number &&
      prev_token_ != TokenType::RightBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->Dump();
    prev_token_ = TokenType::Wrong;
    return true;
  }

  while (!stack.empty() && stack.top()->Type() != TokenType::LeftBracket) {
    // rpn.emplace(std::move(stack.top()));
    rpn.Push(stack.top());
    stack.pop();
  }

  if (stack.empty()) {
    errmsg_ = std::string{"parser: unpaired brackets"};
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.pop();
  if (!stack.empty() && stack.top()->Type() == TokenType::Function) {
    // rpn.emplace(std::move(stack.top()));
    rpn.Push(stack.top());
    stack.pop();
  }

  prev_token_ = TokenType::RightBracket;

  return false;
}

}  // namespace smartcalc

}  // namespace s21
