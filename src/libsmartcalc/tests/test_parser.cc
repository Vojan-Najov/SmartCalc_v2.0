#include <gtest/gtest.h>

#include "parser.h"

using Parser = s21::smartcalc::Parser;
using AToken = s21::smartcalc::AToken;
using TokenType = s21::smartcalc::TokenType;

class ParserTest : public testing::Test {};

/*
TEST_F(ParserTest, Expression01) {
	const char *str = "1 + 2";
	std::queue<std::unique_ptr<AToken>> rpn;
	std::string arr[] = {std::to_string(1.0), std::to_string(2.0), "+"};

	Parser parser(str);
	bool result = parser.ToRpn(rpn);
	EXPECT_FALSE(result);

	for (size_t i = 0; i < sizeof(arr) / sizeof(std::string); ++i) {
		EXPECT_FALSE(rpn.empty());
		if (rpn.empty()) {
			break;
		}
		EXPECT_EQ(rpn.front()->Dump(), arr[i]);
		rpn.pop();
	}
	EXPECT_TRUE(rpn.empty());
}

TEST_F(ParserTest, Expression02) {
	const char *str = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
	// 3 4 2 * 1 5 − 2 3 ^ ^ / +
	std::queue<std::unique_ptr<AToken>> rpn;
	std::string arr[] = {std::to_string(3.0), std::to_string(4.0),
											 std::to_string(2.0), "*",
											 std::to_string(1.0), std::to_string(5.0),
                       "-", std::to_string(2.0), std::to_string(3.0),
                       "^", "^", "/", "+"};

	Parser parser(str);
	bool result = parser.ToRpn(rpn);
	EXPECT_FALSE(result);

	for (size_t i = 0; i < sizeof(arr) / sizeof(std::string); ++i) {
		EXPECT_FALSE(rpn.empty());
		if (rpn.empty()) {
			break;
		}
		EXPECT_EQ(rpn.front()->Dump(), arr[i]);
		rpn.pop();
	}
	EXPECT_TRUE(rpn.empty());
}
*/
TEST_F(ParserTest, Expression03) {
	const char *str = "sin(cos(4) / 3 * 2)";
	// 4 cos 3 / 2 * sin
	std::queue<std::unique_ptr<AToken>> rpn;
	std::string arr[] = {std::to_string(4.0), "cos",
											 std::to_string(3.0), "/",
											 std::to_string(2.0), "*", "sin"};

	Parser parser(str);
	bool result = parser.ToRpn(rpn);
	EXPECT_FALSE(result);

	for (size_t i = 0; i < sizeof(arr) / sizeof(std::string); ++i) {
		EXPECT_FALSE(rpn.empty());
		if (rpn.empty()) {
			break;
		}
		EXPECT_EQ(rpn.front()->Dump(), arr[i]);
		rpn.pop();
	}
	EXPECT_TRUE(rpn.empty());
}
