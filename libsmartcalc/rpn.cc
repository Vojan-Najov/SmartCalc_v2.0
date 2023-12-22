#include "rpn.h"

#include <stack>

namespace s21 {

namespace smartcalc {

Rpn::Rpn(void) : result_{0.0}, errmsg_{}, rpn_{} {}

Rpn::Rpn(const Rpn &copy)
    : result_{copy.result_}, errmsg_{copy.errmsg_}, rpn_{} {
  ConstIterator it = copy.begin();
  ConstIterator last = copy.end();
  for (; it != last; ++it) {
    rpn_.emplace_back((*it)->clone());
  }
}

Rpn::Rpn(Rpn &&other)
    : result_{other.result_},
      errmsg_{std::move(other.errmsg_)},
      rpn_{std::move(other.rpn_)} {
  other.result_ = 0.0;
}

Rpn &Rpn::operator=(const Rpn &other) {
  if (this != &other) {
    result_ = other.result_;
    errmsg_ = other.errmsg_;
    rpn_.clear();
    ConstIterator it = other.begin();
    ConstIterator last = other.end();
    for (; it != last; ++it) {
      rpn_.emplace_back((*it)->clone());
    }
  }

  return *this;
}

Rpn &Rpn::operator=(Rpn &&other) {
  if (this != &other) {
    result_ = other.result_;
    other.result_ = 0.0;
    errmsg_ = std::move(other.errmsg_);
    rpn_ = std::move(other.rpn_);
  }

  return *this;
}

Rpn::~Rpn(void) {}

Rpn::ConstIterator Rpn::begin(void) const noexcept { return rpn_.begin(); }

Rpn::ConstIterator Rpn::end(void) const noexcept { return rpn_.end(); }

bool Rpn::Error(void) const noexcept { return !errmsg_.empty(); }

std::string Rpn::ErrorMessage(void) const { return errmsg_; }

void Rpn::Push(AToken *token) { rpn_.emplace_back(token); }

void Rpn::Push(std::unique_ptr<AToken> &token_ptr) {
  rpn_.emplace_back(std::move(token_ptr));
}

bool Rpn::Calculate(void) {
  bool err_status = false;
  std::stack<std::unique_ptr<AToken>> stack;

  while (!rpn_.empty() && !err_status) {
    std::unique_ptr<AToken> token = std::move(rpn_.front());
    rpn_.pop_front();
    if (token->type == TokenType::Number) {
      stack.push(std::move(token));
    } else if (token->type == TokenType::UnaryOp) {
      err_status = CalculateHandleUnaryOp(token.get(), stack);
    } else if (token->type == TokenType::BinaryOp) {
      err_status = CalculateHandleBinaryOp(token.get(), stack);
    } else if (token->type == TokenType::Function) {
      err_status = CalculateHandleFunc(token.get(), stack);
    } else if (token->type == TokenType::RpnFunction) {
      err_status = CalculateHandleRpnFunc(token.get(), stack);
    }
  }
  if (err_status && !stack.empty()) {
    WrongToken *wt = static_cast<WrongToken *>(stack.top().get());
    errmsg_ = std::move(wt->errmsg);
    return false;
  }
  if (stack.empty()) {
    return CalculateError();
  }
  result_ = static_cast<NumberToken *>(stack.top().get())->value;
  stack.pop();

  if (!stack.empty()) {
    return CalculateError();
  }

  return true;
}

bool Rpn::Calculate(double var) {
  Iterator it = rpn_.begin();
  Iterator last = rpn_.end();

  for (; it != last; ++it) {
    if ((*it)->type == TokenType::Var) {
      std::unique_ptr<AToken> token_ptr{new NumberToken{var}};
      (*it) = std::move(token_ptr);
    }
  }

  return Calculate();
}

double Rpn::Result(void) const noexcept { return result_; }

void Rpn::Clear(void) { rpn_.clear(); }

bool Rpn::CalculateError(void) {
  rpn_.clear();
  errmsg_ = "Error: incorrect sequence of reverse polish notation";
  return false;
}

std::string Rpn::Dump(void) const {
  std::string str{};
  ConstIterator it = begin();
  ConstIterator last = end();
  while (it != last) {
    str += (*it)->dump();
    ++it;
    if (it != last) {
      str += " ";
    }
  }
  return str;
}

bool Rpn::CalculateHandleUnaryOp(AToken *token,
                                 std::stack<std::unique_ptr<AToken>> &stack) {
  UnaryOpToken *unop = static_cast<UnaryOpToken *>(token);

  if (stack.empty()) {
    stack.emplace(
        new WrongToken{"Error: incorrect sequence of reverse polish notation"});
    return true;
  }

  std::unique_ptr<AToken> value = std::move(stack.top());
  stack.pop();

  AToken *result = unop->apply(static_cast<NumberToken *>(value.get()));
  stack.emplace(result);

  return false;
}

bool Rpn::CalculateHandleBinaryOp(AToken *token,
                                  std::stack<std::unique_ptr<AToken>> &stack) {
  bool err_status = false;
  BinaryOpToken *binop = static_cast<BinaryOpToken *>(token);

  if (stack.empty()) {
    stack.emplace(
        new WrongToken{"Error: incorrect sequence of reverse polish notation"});
    return true;
  }
  std::unique_ptr<AToken> rhs = std::move(stack.top());
  stack.pop();

  if (stack.empty()) {
    stack.emplace(
        new WrongToken{"Error: incorrect sequence of reverse polish notation"});
    return true;
  }
  std::unique_ptr<AToken> lhs = std::move(stack.top());
  stack.pop();

  AToken *result = binop->apply(static_cast<NumberToken *>(lhs.get()),
                                static_cast<NumberToken *>(rhs.get()));
  if (result->type == TokenType::Wrong) {
    err_status = true;
  }
  stack.emplace(result);

  return err_status;
}

bool Rpn::CalculateHandleFunc(AToken *token,
                              std::stack<std::unique_ptr<AToken>> &stack) {
  bool err_status = false;
  FuncToken *func = static_cast<FuncToken *>(token);

  if (stack.empty()) {
    stack.emplace(
        new WrongToken{"Error: incorrect sequence of reverse polish notation"});
    return true;
  }
  std::unique_ptr<AToken> value = std::move(stack.top());
  stack.pop();

  AToken *result = func->apply(static_cast<NumberToken *>(value.get()));
  if (result->type == TokenType::Wrong) {
    err_status = true;
  }
  stack.emplace(result);

  return err_status;
}

bool Rpn::CalculateHandleRpnFunc(AToken *token,
                                 std::stack<std::unique_ptr<AToken>> &stack) {
  bool err_status = false;
  RpnFuncToken *func = static_cast<RpnFuncToken *>(token);

  if (stack.empty()) {
    stack.emplace(
        new WrongToken{"Error: incorrect sequence of reverse polish notation"});
    return true;
  }
  std::unique_ptr<AToken> value = std::move(stack.top());
  stack.pop();

  AToken *result = func->apply(static_cast<NumberToken *>(value.get()));
  if (result->type == TokenType::Wrong) {
    err_status = true;
  }
  stack.emplace(result);

  return err_status;
}

/*
 *  RPN FUNCTION TOKEN
 */

RpnFuncToken::RpnFuncToken(const Rpn &copy)
    : AToken{TokenType::RpnFunction}, rpn_{copy} {}

RpnFuncToken::~RpnFuncToken(void) {}

RpnFuncToken *RpnFuncToken::clone(void) const { return new RpnFuncToken{rpn_}; }

std::string RpnFuncToken::dump(void) const {
  std::string str{};

  str += "|";
  Rpn::ConstIterator it = rpn_.begin();
  Rpn::ConstIterator last = rpn_.end();
  while (it != last) {
    str += (*it)->dump();
    ++it;
    if (it != last) {
      str += " ";
    }
  }
  str += "|";

  return str;
}

AToken *RpnFuncToken::apply(const NumberToken *token) {
  rpn_.Calculate(token->value);
  if (rpn_.Error()) {
    std::cout << rpn_.ErrorMessage() << std::endl;
    return new WrongToken{rpn_.ErrorMessage()};
  }
  return new NumberToken{rpn_.Result()};
}

}  // namespace smartcalc

}  // namespace s21
