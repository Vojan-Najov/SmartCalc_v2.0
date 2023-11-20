#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"

class LexerTest : public testing::Test {

};

TEST_F(LexerTest, EmptyString) {
	s21::Lexer lexer{""};
	EXPECT_TRUE(lexer.Empty());

	s21::AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), s21::TokenType::Empty);
	delete token;
}

TEST_F(LexerTest, SpaceString) {
	s21::Lexer lexer{"    \t   \v    \n    \t\t    \n"};
	EXPECT_TRUE(lexer.Empty());

	s21::AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), s21::TokenType::Empty);
	delete token;
}

TEST_F(LexerTest, NumberTest) {
	s21::Lexer lexer{"        123         \n"};
	EXPECT_FALSE(lexer.Empty());

	s21::AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), s21::TokenType::Number);

	s21::NumberToken *num = static_cast<s21::NumberToken *>(token);
	EXPECT_EQ(num->Value(), 123.0);

	EXPECT_TRUE(lexer.Empty());

	delete token;
}

TEST_F(LexerTest, HugeValueTest) {
	s21::Lexer lexer{"    1.18973e+4932    "};
	EXPECT_FALSE(lexer.Empty());

	s21::AToken *token = lexer.NextToken();
	EXPECT_EQ(token->Type(), s21::TokenType::Wrong);

	std::cout << static_cast<s21::WrongToken*>(token)->errmsg << std::endl;

	EXPECT_TRUE(lexer.Empty());

	delete token;
}
