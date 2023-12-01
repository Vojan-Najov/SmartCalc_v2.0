#include "rpn.h"

#include <stack>

namespace s21 {

namespace smartcalc {

Rpn::Rpn(void) : result_{0.0}, rpn_{} {}

Rpn::Rpn(const Rpn &copy) : result_{copy.result_}, rpn_{} {
  ConstIterator it = copy.begin();
  ConstIterator last = copy.end();
  for (; it != last; ++it) {
    rpn_.emplace_back((*it)->clone());
  }
}

Rpn::Rpn(Rpn &&other) : result_{other.result_}, rpn_{std::move(other.rpn_)} {
  other.result_ = 0.0;
}

Rpn &Rpn::operator=(const Rpn &other) {
  if (this != &other) {
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
    rpn_ = std::move(other.rpn_);
    result_ = other.result_;
    other.result_ = 0.0;
  }

  return *this;
}

Rpn::~Rpn(void) {}

Rpn::ConstIterator Rpn::begin(void) const noexcept { return rpn_.begin(); }

Rpn::ConstIterator Rpn::end(void) const noexcept { return rpn_.end(); }

void Rpn::Push(AToken *token) { rpn_.emplace_back(token); }

void Rpn::Push(std::unique_ptr<AToken> &token_ptr) {
  rpn_.emplace_back(std::move(token_ptr));
}

bool Rpn::Calculate(void) {
  std::stack<std::unique_ptr<AToken>> stack;

  while (!rpn_.empty()) {
    std::unique_ptr<AToken> &token = rpn_.front();
    if (token->type == TokenType::Number) {
      stack.push(std::move(token));
      rpn_.pop_front();
    } else if (token->type == TokenType::UnaryOp) {
      std::unique_ptr<AToken> &value = stack.top();
      AToken *result = static_cast<UnaryOpToken *>(token.get())
                           ->apply(static_cast<NumberToken *>(value.get()));
	  stack.pop();
      stack.emplace(result);
      rpn_.pop_front();
    } else if (token->type == TokenType::BinaryOp) {
      std::unique_ptr<AToken> rhs = std::move(stack.top());
      stack.pop();
      std::unique_ptr<AToken> lhs = std::move(stack.top());
      stack.pop();
      AToken *result = static_cast<BinaryOpToken *>(token.get())
                           ->apply(static_cast<NumberToken *>(lhs.get()),
                                   static_cast<NumberToken *>(rhs.get()));
      stack.emplace(result);
      rpn_.pop_front();
    } else if (token->type == TokenType::Function) {
      std::unique_ptr<AToken> &value = stack.top();
      AToken *result = static_cast<FuncToken *>(token.get())
                           ->apply(static_cast<NumberToken *>(value.get()));
      stack.pop();
      stack.emplace(result);
      rpn_.pop_front();
    }
  }
  result_ = static_cast<NumberToken *>(stack.top().get())->value;
  stack.pop();

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

/*
 *  RPN FUNCTION TOKEN
 */

RpnFuncToken::RpnFuncToken(const Rpn &copy)
    : AToken{TokenType::Function}, rpn_{copy} {}

RpnFuncToken::~RpnFuncToken(void) {}

RpnFuncToken *RpnFuncToken::clone(void) const { return new RpnFuncToken{rpn_}; }

std::string RpnFuncToken::dump(void) const {
  std::string str{};

  str += "|";
  Rpn::ConstIterator it = rpn_.begin();
  Rpn::ConstIterator last = rpn_.end();
  for (; it != last; ++it) {
    str += (*it)->dump();
  }
  str += "|";

  return str;
}

}  // namespace smartcalc

}  // namespace s21
