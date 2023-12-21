#include <gtest/gtest.h>

#include <iostream>

#include "operations.h"
#include "token.h"

using EmptyToken = s21::smartcalc::EmptyToken;
using WrongToken = s21::smartcalc::WrongToken;
using NumberToken = s21::smartcalc::NumberToken;
using UnaryOpToken = s21::smartcalc::UnaryOpToken;
using BinaryOpToken = s21::smartcalc::BinaryOpToken;

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
