#include "lexer.h"

#include <gtest/gtest.h>

class LexerTest : public testing::Test {

};

TEST_F(LexerTest, EmptyString) {
	std::string errmsg;
	s21::Lexer lexer{"", errmsg};
	const char *expected[] = {};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, SpacesString) {
	std::string errmsg;
	s21::Lexer lexer{"    \t     \n   ", errmsg};
	const char *expected[] = {};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String1) {
	std::string errmsg;
	s21::Lexer lexer{"    11       ", errmsg};
	const char *expected[] = {"11"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String2) {
	std::string errmsg;
	s21::Lexer lexer{"   1   2   ", errmsg};
	const char *expected[] = {"1", "2"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String3) {
	std::string errmsg;
	s21::Lexer lexer{"1+2", errmsg};
	const char *expected[] = {"1", "+", "2"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String4) {
	std::string errmsg;
	s21::Lexer lexer{"-1 + 2mod3", errmsg};
	const char *expected[] = {"-", "1", "+", "2", "%", "3"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String5) {
	std::string errmsg;
	s21::Lexer lexer{"-1+2*4/(17+sin(10))/14mod3", errmsg};
	const char *expected[] = {"-", "1", "+", "2", "*", "4", "/",
                            "(", "17", "+", "sin", "(", "10", 
                            ")", ")", "/", "14", "%", "3"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

TEST_F(LexerTest, String6) {
	std::string errmsg;
	s21::Lexer lexer{"-1 + +2 * -4 / ln(17+sin(10))/14mod3", errmsg};
	const char *expected[] = {"-", "1", "+", "+", "2", "*", "-",
														"4", "/", "ln", "(", "17", "+", "sin", "(", "10", 
                            ")", ")", "/", "14", "%", "3"};

	for (size_t i = 0; i < sizeof(expected) / sizeof(const char *); ++i) {
		EXPECT_EQ(lexer.next(), std::string{expected[i]});
	}
	EXPECT_TRUE(lexer.empty());
}

