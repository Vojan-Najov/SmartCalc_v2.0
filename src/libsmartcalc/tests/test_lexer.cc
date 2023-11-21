#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"

using Lexer = s21::smartcalc::Lexer;
using AToken = s21::smartcalc::AToken;
using NumberToken = s21::smartcalc::NumberToken;
using WrongToken = s21::smartcalc::WrongToken;
using TokenType = s21::smartcalc::TokenType;

class LexerTest : public testing::Test {

};

TEST_F(LexerTest, EmptyString) {
	Lexer lexer{""};
	EXPECT_TRUE(lexer.Empty());

	AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), TokenType::Empty);
	delete token;
}

TEST_F(LexerTest, SpaceString) {
	Lexer lexer{"    \t   \v    \n    \t\t    \n"};
	EXPECT_TRUE(lexer.Empty());

	AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), TokenType::Empty);
	delete token;
}

TEST_F(LexerTest, NumberTest) {
	Lexer lexer{"        123         \n"};
	EXPECT_FALSE(lexer.Empty());

	AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), TokenType::Number);

	NumberToken *num = static_cast<NumberToken *>(token);
	EXPECT_EQ(num->Value(), 123.0);

	EXPECT_TRUE(lexer.Empty());

	delete token;
}

TEST_F(LexerTest, HugeValueTest) {
	Lexer lexer{"    1.18973e+4932    "};
	EXPECT_FALSE(lexer.Empty());

	AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), TokenType::Wrong);

	std::cout << static_cast<WrongToken*>(token)->errmsg << std::endl;

	EXPECT_TRUE(lexer.Empty());

	delete token;
}
