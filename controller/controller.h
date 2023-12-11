#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <string>

namespace s21 {

class Controller {
	std::string RunExpression(const std::string &);
 private:
	Model model_;
};

}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
