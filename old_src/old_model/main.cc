#include <iostream>
#include "calculator.h"

int main() {
	s21::Calculator calc;

	std::cout << calc.calculate_expr("1 + 2") << std::endl;
	
}
