#include <stack>

#include "rpn.h"

namespace s21 {

namespace smartcalc {

void Rpn::Push(AToken *token) {
	rpn_.emplace_back(token);
}

void Rpn::Calculate(void) {
	std::stack<std::unique_ptr<AToken>> stack;

	while (!rpn_.empty()) {
		std::unique_ptr<AToken> &token = rpn_.front();
		if (token->Type() == TokenType::Number) {
			stack.push(std::move(token));
			rpn_.pop_front();
		} else if (token->Type() == TokenType::UnaryOp) {
			std::unique_ptr<AToken> &value = stack.top();
			stack.pop();
			AToken *result = static_cast<UnaryOpToken*>(token.get())->Apply(value.get());
			stack.emplace(result);
			rpn_.pop_front();
		} else if (token->Type() == TokenType::BinaryOp) {
			std::unique_ptr<AToken> rhs = std::move(stack.top());
			stack.pop();
			std::unique_ptr<AToken> lhs = std::move(stack.top());
			stack.pop();
			AToken *result =
				static_cast<BinaryOpToken*>(token.get())->Apply(lhs.get(), rhs.get());
			stack.emplace(result);
			rpn_.pop_front();
		} else if (token->Type() == TokenType::Function) {
			std::unique_ptr<AToken> &value = stack.top();
			stack.pop();
			AToken *result = static_cast<FuncToken*>(token.get())->Apply(value.get());
			stack.emplace(result);
			rpn_.pop_front();
		}
	}
	result_ = static_cast<NumberToken*>(stack.top().get())->Value();
	stack.pop();
}

double Rpn::Result(void) const noexcept {
	return result_;
}

}  // namespace smartcalc

}  // namespace s21
