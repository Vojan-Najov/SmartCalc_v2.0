#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "rpn.h"
#include "operations.h"

using Rpn = s21::smartcalc::Rpn;
using AToken = s21::smartcalc::AToken;
using NumberToken = s21::smartcalc::NumberToken;
using UnaryOpToken = s21::smartcalc::UnaryOpToken;
using BinaryOpToken = s21::smartcalc::BinaryOpToken;
using FuncToken = s21::smartcalc::FuncToken;
using WrongToken = s21::smartcalc::WrongToken;
using TokenType = s21::smartcalc::TokenType;

class RpnTest : public testing::Test {

};

TEST_F(RpnTest, Expression00) {
	Rpn rpn;

	rpn.Push(new NumberToken{5.0});

	rpn.Calculate();
	EXPECT_EQ(rpn.Result(), 5.0);
}

TEST_F(RpnTest, Expression01) {
	Rpn rpn;

	rpn.Push(new NumberToken{15.0});
	rpn.Push(new NumberToken{10.0});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::sub});

	bool ret = rpn.Calculate();
	EXPECT_TRUE(ret);
	EXPECT_EQ(rpn.Result(), 5.0);
}

TEST_F(RpnTest, Expression02) {
	Rpn rpn;

	// 3 + 4 × 2 ÷ ( 1 − 5 ) ^ 2 ^ 3
	double result = 3.0 + 4.0 * 2.0 / std::pow((1.0 - 5.0), pow(2.0, 3.0));

	// 3 4 2 × 1 5 − 2 3 ^ ^ ÷ +
	rpn.Push(new NumberToken{3.0});
	rpn.Push(new NumberToken{4.0});
	rpn.Push(new NumberToken{2.0});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::multiply});
	rpn.Push(new NumberToken{1.0});
	rpn.Push(new NumberToken{5.0});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::sub});
	rpn.Push(new NumberToken{2.0});
	rpn.Push(new NumberToken{3.0});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::power});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::power});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::devide});
	rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::sum});

	bool ret = rpn.Calculate();
	EXPECT_TRUE(ret);
	EXPECT_EQ(rpn.Result(), result);
}

