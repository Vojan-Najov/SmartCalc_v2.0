#ifndef MODEL_TOKEN_H_
#define MODEL_TOKEN_H_

namespace s21 {

enum class TokenType
{
	UNARY_OP,
};

class AToken {
 public:
	virtual TokenType type(void) const noexcept = 0;
	virtual ~AToken(void) = 0;
};

class UnaryOperator : AToken
{
 public:
	
};

class AValuableToken {
 public:
	virtual double value(void) = 0;
	virtual ~AValuable(void) = 0;
};

class AFunctional
{
 public:
	TokenType type(void) const noexcept = 0;
	virtual NumberToken *call(const AValueble *token) = 0;
	virtual ~AFunctional(void) = 0;
};

class Function : AToken, AFunctional
{
 public:
	Function(double (*func)(double));
	TokenType type(void) const noexcept override;
	Number *call(const AValueable *token) override;

 private:
	double (*func_)(double);
};

class UserFunction : AToken, AFunctional
{
 public:
	UserFunction(const std::deque<std::shared_ptr> func);
	TokenType type(void) const noexcept override;
	Number *call(const AValueable *token) override;
	
 private:
	std::deque<std::shared_ptr<AToken*>> func_;
};

}  // namespace s21


#endif MODEL_TOKEN_H_
