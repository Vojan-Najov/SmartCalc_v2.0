#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "operations.h"
#include "rpn.h"
#include "token.h"

using Rpn = s21::smartcalc::Rpn;
using AToken = s21::smartcalc::AToken;
using NumberToken = s21::smartcalc::NumberToken;
using UnaryOpToken = s21::smartcalc::UnaryOpToken;
using BinaryOpToken = s21::smartcalc::BinaryOpToken;
using FuncToken = s21::smartcalc::FuncToken;
using RpnFuncToken = s21::smartcalc::RpnFuncToken;
using WrongToken = s21::smartcalc::WrongToken;
using VarToken = s21::smartcalc::VarToken;
using TokenType = s21::smartcalc::TokenType;

class RpnTest : public testing::Test {};

TEST_F(RpnTest, MoveConstructor) {
  Rpn rpn1;
  rpn1.Push(new VarToken{});
  rpn1.Push(new FuncToken{&s21::smartcalc::funcs::sin});

  Rpn rpn2 = std::move(rpn1);

  rpn2.Calculate(1);
  double res = rpn2.Result();

  EXPECT_EQ(res, std::sin(1.0));
}

TEST_F(RpnTest, CopyConstructor) {
  Rpn rpn1;
  rpn1.Push(new VarToken{});
  rpn1.Push(new FuncToken{&s21::smartcalc::funcs::sin});

  Rpn rpn2 = rpn1;

  rpn1.Calculate(1);
  double res1 = rpn1.Result();

  rpn2.Calculate(1);
  double res2 = rpn2.Result();

  EXPECT_EQ(res1, res2);
}

TEST_F(RpnTest, OperatorAssign) {
  Rpn rpn1;
  rpn1.Push(new VarToken{});
  rpn1.Push(new FuncToken{&s21::smartcalc::funcs::sin});

  Rpn rpn2 = rpn1;
  rpn2 = rpn1;

  rpn1.Calculate(1);
  double res1 = rpn1.Result();

  rpn2.Calculate(1);
  double res2 = rpn2.Result();

  EXPECT_EQ(res1, res2);
}

TEST_F(RpnTest, Dump) {
  Rpn rpn;
  rpn.Push(new VarToken{});
  rpn.Push(new FuncToken{&s21::smartcalc::funcs::sin});

  std::string dump = rpn.Dump();
  EXPECT_EQ(dump, "x sin");

  s21::smartcalc::RpnFuncToken tok{rpn};
  dump = tok.dump();
  EXPECT_EQ(dump, "|x sin|");

  s21::smartcalc::RpnFuncToken *clone = tok.clone();
  dump = clone->dump();
  delete clone;
  EXPECT_EQ(dump, "|x sin|");
}

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

TEST_F(RpnTest, Error01) {
  Rpn rpn;

  rpn.Push(new UnaryOpToken{&s21::smartcalc::unary_ops::minus});

  bool ret = rpn.Calculate();
  EXPECT_FALSE(ret);
  EXPECT_EQ(rpn.ErrorMessage(),
            "Error: incorrect sequence of reverse polish notation");
}

TEST_F(RpnTest, Error02) {
  Rpn rpn;

  rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::sub});

  bool ret = rpn.Calculate();
  EXPECT_FALSE(ret);
  EXPECT_EQ(rpn.ErrorMessage(),
            "Error: incorrect sequence of reverse polish notation");
}

TEST_F(RpnTest, Error03) {
  Rpn rpn;

  rpn.Push(new NumberToken{3.0});
  rpn.Push(new BinaryOpToken{&s21::smartcalc::binary_ops::sub});

  bool ret = rpn.Calculate();
  EXPECT_FALSE(ret);
  EXPECT_EQ(rpn.ErrorMessage(),
            "Error: incorrect sequence of reverse polish notation");
}

TEST_F(RpnTest, Error04) {
  Rpn rpn;

  rpn.Push(new FuncToken{&s21::smartcalc::funcs::sin});

  bool ret = rpn.Calculate();
  EXPECT_FALSE(ret);
  EXPECT_EQ(rpn.ErrorMessage(),
            "Error: incorrect sequence of reverse polish notation");
}

TEST_F(RpnTest, Error05) {
  Rpn rpn_for_token;
  rpn_for_token.Push(new NumberToken{3.0});

  Rpn rpn;
  rpn.Push(new RpnFuncToken{std::move(rpn_for_token)});

  bool ret = rpn.Calculate();
  EXPECT_FALSE(ret);
  EXPECT_EQ(rpn.ErrorMessage(),
            "Error: incorrect sequence of reverse polish notation");
}
