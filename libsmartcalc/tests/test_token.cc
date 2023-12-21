#include <gtest/gtest.h>

#include <iostream>

#include "operations.h"
#include "token.h"

using EmptyToken = s21::smartcalc::EmptyToken;
using WrongToken = s21::smartcalc::WrongToken;
using NumberToken = s21::smartcalc::NumberToken;
using UnaryOpToken = s21::smartcalc::UnaryOpToken;
using BinaryOpToken = s21::smartcalc::BinaryOpToken;
using FuncToken = s21::smartcalc::FuncToken;
using LeftBracketToken = s21::smartcalc::LeftBracketToken;
using RightBracketToken = s21::smartcalc::RightBracketToken;
using NameToken = s21::smartcalc::NameToken;

class TokenTest : public testing::Test {};

TEST_F(TokenTest, EmptyToken) {
  EmptyToken t{};
  EmptyToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "");
  delete ct;
}

TEST_F(TokenTest, WrongToken) {
  WrongToken t{"error"};
  WrongToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "error");
  delete ct;
}

TEST_F(TokenTest, NumberToken) {
  NumberToken t{12.4};
  NumberToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), std::to_string(12.4));
  delete ct;
}

TEST_F(TokenTest, UnaryOpToken) {
  UnaryOpToken t{&s21::smartcalc::unary_ops::plus};
  UnaryOpToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "+");
  delete ct;
}

TEST_F(TokenTest, BinaryOpToken) {
  BinaryOpToken t{&s21::smartcalc::binary_ops::power};
  BinaryOpToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "^");
  delete ct;
}

TEST_F(TokenTest, FuncToken) {
  FuncToken fsin{&s21::smartcalc::funcs::sin};
  EXPECT_EQ(fsin.dump(), "sin");

  FuncToken fcos{&s21::smartcalc::funcs::cos};
  EXPECT_EQ(fcos.dump(), "cos");

  FuncToken ftan{&s21::smartcalc::funcs::tan};
  EXPECT_EQ(ftan.dump(), "tan");

  FuncToken fasin{&s21::smartcalc::funcs::asin};
  EXPECT_EQ(fasin.dump(), "asin");

  FuncToken facos{&s21::smartcalc::funcs::acos};
  EXPECT_EQ(facos.dump(), "acos");

  FuncToken fatan{&s21::smartcalc::funcs::atan};
  EXPECT_EQ(fatan.dump(), "atan");

  FuncToken fln{&s21::smartcalc::funcs::ln};
  EXPECT_EQ(fln.dump(), "ln");

  FuncToken flog{&s21::smartcalc::funcs::log};
  EXPECT_EQ(flog.dump(), "log");

  FuncToken fsqrt{&s21::smartcalc::funcs::sqrt};
  EXPECT_EQ(fsqrt.dump(), "sqrt");
}

TEST_F(TokenTest, LeftBracketOpToken) {
  LeftBracketToken t{};
  LeftBracketToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "(");
  delete ct;
}

TEST_F(TokenTest, RightBracketOpToken) {
  RightBracketToken t{};
  RightBracketToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), ")");
  delete ct;
}

TEST_F(TokenTest, NameOpToken) {
  NameToken t{std::string{"tmp"}};
  NameToken *ct = t.clone();
  EXPECT_EQ(ct->dump(), "tmp");
  delete ct;
}

TEST_F(TokenTest, OutputTest) {
  std::cerr << s21::smartcalc::TokenType::Empty
            << s21::smartcalc::TokenType::Wrong
            << s21::smartcalc::TokenType::Number
            << s21::smartcalc::TokenType::UnaryOp
            << s21::smartcalc::TokenType::BinaryOp
            << s21::smartcalc::TokenType::Function
            << s21::smartcalc::TokenType::LeftBracket
            << s21::smartcalc::TokenType::RightBracket
            << s21::smartcalc::TokenType::Name << std::endl;
}
