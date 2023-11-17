#ifndef LIBSMARTCALC_TOKEN_H_
#define LIBSMARTCALC_TOKEN_H_

namespace s21 {

class AToken
{
 public:
	virtual TokenType type(void) const noexcept = 0;
	virtual ~AToken(void) = 0;
};

}  // namespace s21

#endif  // LIBSMARTCALC_TOKEN_H_
