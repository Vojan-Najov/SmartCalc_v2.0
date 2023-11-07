#include "lexer.h"

#include <gtest/gtest.h>

class LexerTest : public testing::Test {

};

TEST_F(LexerTest, EmptyString) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected;
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, SpacesString) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("   \t   \n   \v    ");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected;
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String1) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("   11  ");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"11"};
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String2) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("1 2");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"12"};
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String3) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("1 + 2");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"1+2"};
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String4) {
	std::list<std::string> lexems = s21::lexer::str_to_lexems("-1 + 2mod3");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"-1+2%3"};
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String5) {
	std::list<std::string> lexems = 
		s21::lexer::str_to_lexems("-1+2*4/(17+sin(10))/14mod3");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"-1+2*4/(17+sin(10))/14%3"};
	EXPECT_EQ(dump, expected);
}

TEST_F(LexerTest, String6) {
	std::list<std::string> lexems = 
		s21::lexer::str_to_lexems("-1 + +2 * - 4 /ln(17+sin(10))/14mod3");
	std::string dump = s21::lexer::lexems_to_string(lexems);
	std::string expected{"-1++2*-4/ln(17+sin(10))/14%3"};
	EXPECT_EQ(dump, expected);
}

