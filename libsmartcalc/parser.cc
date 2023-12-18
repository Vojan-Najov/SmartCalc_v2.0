#include "parser.h"

#include <iostream>

namespace s21 {

namespace smartcalc {

Parser::Parser(const char *expr, bool x_is_var) noexcept
    : expr_{expr},
      errmsg_{},
      prev_token_{TokenType::Empty},
      x_is_var_{x_is_var} {}

bool Parser::Error(void) const noexcept { return !errmsg_.empty(); }

std::string Parser::ErrorMessage(void) const { return errmsg_; }

void Parser::SetExpr(const char *expr) noexcept {
  expr_ = expr;
  prev_token_ = TokenType::Empty;
}

void Parser::XisVar(bool flag) noexcept { x_is_var_ = flag; }

Rpn Parser::ToRpn(const VarMap &vars, const FuncMap &funcs) {
  Rpn rpn{};
  Lexer lexer{expr_};
  bool err_status = false;
  std::stack<std::unique_ptr<AToken>> stack{};

  if (lexer.Empty()) {
    err_status = true;
    errmsg_ = std::string{"parser: empty input"};
  }

  while (!lexer.Empty() && !err_status) {
    AToken *token = lexer.NextToken();

    if (token->type == TokenType::Name) {
      token = ToRpnHandleNameToken(token, vars, funcs);
    }

    if (token->type == TokenType::Wrong) {
      err_status = ToRpnHandleWrongToken(token);
    } else if (token->type == TokenType::Number) {
      err_status = ToRpnHandleNumberToken(token, rpn);
    } else if (token->type == TokenType::Var) {
      err_status = ToRpnHandleVarToken(token, rpn);
    } else if (token->type == TokenType::UnaryOp) {
      err_status = ToRpnHandleUnaryOpToken(token, stack);
    } else if (token->type == TokenType::BinaryOp) {
      err_status = ToRpnHandleBinaryOpToken(token, stack, rpn);
    } else if (token->type == TokenType::Function ||
               token->type == TokenType::RpnFunction) {
      err_status = ToRpnHandleFuncToken(token, stack);
    } else if (token->type == TokenType::LeftBracket) {
      err_status = ToRpnHandleLeftBracketToken(token, stack);
    } else if (token->type == TokenType::RightBracket) {
      err_status = ToRpnHandleRightBracketToken(token, stack, rpn);
    }
  }

  if (!err_status && prev_token_ != TokenType::RightBracket &&
      prev_token_ != TokenType::Number && prev_token_ != TokenType::Var) {
    err_status = true;
    errmsg_ = std::string{"parser: error near the end of the line"};
    rpn.Clear();
  }

  while (!stack.empty() && !err_status) {
    std::unique_ptr<AToken> &op = stack.top();
    if (op->type == TokenType::LeftBracket) {
      errmsg_ = std::string{"parser: unpaired brackets"};
      err_status = true;
      rpn.Clear();
    } else {
      rpn.Push(op);
      stack.pop();
    }
  }

  prev_token_ = TokenType::Empty;

  return rpn;
}

bool Parser::ToRpnHandleWrongToken(AToken *token) {
  errmsg_ = std::string{"parser: unknown token "} +
            std::move(static_cast<WrongToken *>(token)->errmsg);
  delete token;
  prev_token_ = TokenType::Wrong;
  return true;
}

bool Parser::ToRpnHandleNumberToken(AToken *token, Rpn &rpn) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  rpn.Push(token);
  prev_token_ = TokenType::Number;

  return false;
}

bool Parser::ToRpnHandleVarToken(AToken *token, Rpn &rpn) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  rpn.Push(token);
  prev_token_ = TokenType::Var;

  return false;
}

bool Parser::ToRpnHandleUnaryOpToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
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
  BinaryOpToken *binop = static_cast<BinaryOpToken *>(token);

  if (prev_token_ != TokenType::Number && prev_token_ != TokenType::Var &&
      prev_token_ != TokenType::RightBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  while (!stack.empty()) {
    std::unique_ptr<AToken> &op = stack.top();
    if (op->type == TokenType::UnaryOp) {
      rpn.Push(op);
      stack.pop();
    } else if (op->type == TokenType::BinaryOp) {
      int cur_precedence = binop->precedence();
      int op_precedence = static_cast<BinaryOpToken *>(op.get())->precedence();
      bool left_associative = binop->left_associative();
      if (op_precedence > cur_precedence ||
          ((op_precedence == cur_precedence) && left_associative)) {
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

bool Parser::ToRpnHandleFuncToken(AToken *token,
                                  std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
    delete token;
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.emplace(token);
  prev_token_ = TokenType::Function;

  return false;
}

bool Parser::ToRpnHandleLeftBracketToken(
    AToken *token, std::stack<std::unique_ptr<AToken>> &stack) {
  if (prev_token_ != TokenType::Empty && prev_token_ != TokenType::UnaryOp &&
      prev_token_ != TokenType::BinaryOp &&
      prev_token_ != TokenType::Function &&
      prev_token_ != TokenType::LeftBracket) {
    errmsg_ = std::string{"parser: error near token "} + token->dump();
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

  if (prev_token_ != TokenType::Number && prev_token_ != TokenType::Var &&
      prev_token_ != TokenType::RightBracket) {
    errmsg_ = std::string{"parser: error near token )"};
    prev_token_ = TokenType::Wrong;
    return true;
  }

  while (!stack.empty() && stack.top()->type != TokenType::LeftBracket) {
    rpn.Push(stack.top());
    stack.pop();
  }

  if (stack.empty()) {
    errmsg_ = std::string{"parser: unpaired brackets"};
    prev_token_ = TokenType::Wrong;
    return true;
  }

  stack.pop();
  if (!stack.empty() && (stack.top()->type == TokenType::Function ||
                         stack.top()->type == TokenType::RpnFunction)) {
    rpn.Push(stack.top());
    stack.pop();
  }

  prev_token_ = TokenType::RightBracket;

  return false;
}

AToken *Parser::ToRpnHandleNameToken(AToken *token, const VarMap &vars,
                                     const FuncMap &funcs) {
  NameToken *tn = static_cast<NameToken *>(token);

  if (x_is_var_ &&
      (tn->name == std::string{"x"} || tn->name == std::string{"X"})) {
    delete token;
    return new VarToken{};
  }

  VarMap::const_iterator vars_it = vars.find(tn->name);
  if (vars_it != vars.end()) {
    delete token;
    return new NumberToken{vars_it->second};
  }

  FuncMap::const_iterator funcs_it = funcs.find(tn->name);
  if (funcs_it != funcs.end()) {
    delete token;
    return new RpnFuncToken{funcs_it->second};
  }

  delete token;
  return new WrongToken{tn->name};
}

}  // namespace smartcalc

}  // namespace s21
