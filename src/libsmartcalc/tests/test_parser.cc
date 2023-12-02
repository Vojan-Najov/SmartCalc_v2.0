#include <gtest/gtest.h>

#include "parser.h"
#include "smartcalc.h"

using Parser = s21::smartcalc::Parser;
using AToken = s21::smartcalc::AToken;
using TokenType = s21::smartcalc::TokenType;
using Rpn = s21::smartcalc::Rpn;
using Smartcalc = s21::Smartcalc;

class ParserTest : public testing::Test {
 public:
  std::map<std::string, double> vars;
  std::map<std::string, Rpn> funcs;

  void SetUp(void) override {
    vars.emplace("E", Smartcalc::E);
    vars.emplace("PI", Smartcalc::PI);
  }

  template <size_t N>
  void check(const Rpn &rpn, const std::string (&arr)[N]) {
    size_t i = 0;
    auto it = rpn.begin();
    auto last = rpn.end();
    for (; i < N && it != last; ++i, ++it) {
      EXPECT_EQ((*it)->dump(), arr[i]);
    }
    EXPECT_EQ(it, last);
    EXPECT_EQ(i, N);
  }
};

TEST_F(ParserTest, Expression01) {
  const char *str = "1 + 2";
  std::string arr[] = {std::to_string(1.0), std::to_string(2.0), "+"};

  Parser parser(str);
  Rpn rpn = parser.ToRpn(vars, funcs);
  EXPECT_FALSE(parser.Error());

  check(rpn, arr);
}

TEST_F(ParserTest, Expression02) {
  const char *str = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
  // 3 4 2 * 1 5 − 2 3 ^ ^ / +
  std::string arr[] = {std::to_string(3.0),
                       std::to_string(4.0),
                       std::to_string(2.0),
                       "*",
                       std::to_string(1.0),
                       std::to_string(5.0),
                       "-",
                       std::to_string(2.0),
                       std::to_string(3.0),
                       "^",
                       "^",
                       "/",
                       "+"};

  Parser parser(str);
  Rpn rpn = parser.ToRpn(vars, funcs);
  EXPECT_FALSE(parser.Error());

  check(rpn, arr);
}

TEST_F(ParserTest, Expression03) {
  const char *str = "sin(cos(4) / 3 * 2)";
  // 4 cos 3 / 2 * sin
  std::string arr[] = {std::to_string(4.0),
                       "cos",
                       std::to_string(3.0),
                       "/",
                       std::to_string(2.0),
                       "*",
                       "sin"};

  Parser parser(str);
  Rpn rpn = parser.ToRpn(vars, funcs);
  EXPECT_FALSE(parser.Error());

  check(rpn, arr);
}

TEST_F(ParserTest, Expression04) {
  const char *str = "PI";
  std::string arr[] = {std::to_string(Smartcalc::PI)};

  Parser parser(str);
  Rpn rpn = parser.ToRpn(vars, funcs);
  EXPECT_FALSE(parser.Error());

  check(rpn, arr);
}

TEST_F(ParserTest, Expression05) {
  const char *str = "PI + 2 * E";
  std::string arr[] = {std::to_string(Smartcalc::PI), std::to_string(2.0),
                       std::to_string(Smartcalc::E), std::string{"*"},
                       std::string{"+"}};

  Parser parser(str);
  Rpn rpn = parser.ToRpn(vars, funcs);
  EXPECT_FALSE(parser.Error());

  check(rpn, arr);
}
