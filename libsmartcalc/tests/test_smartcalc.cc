#include <gtest/gtest.h>

#include <cmath>

#include "smartcalc.h"

using Smartcalc = s21::Smartcalc;

class SmartcalcTest : public testing::Test {
 public:
  Smartcalc sc{};

  void SetUp(void) override {}
};

TEST_F(SmartcalcTest, Expression01) {
  const char *expr = "";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_TRUE(sc.Error());
  EXPECT_EQ(sc.ErrorMessage(), "parser: empty input");
}

TEST_F(SmartcalcTest, Expression02) {
  const char *expr = "    \t   \v    \n    \t  \n";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_TRUE(sc.Error());
  EXPECT_EQ(sc.ErrorMessage(), "parser: empty input");
}

TEST_F(SmartcalcTest, Expression03) {
  double result = 2.0;
  const char *expr = "   2   ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression04) {
  double result = 2.0 + 3.0;
  const char *expr = "   2 + 3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression05) {
  double result = 2.0 + -3.0;
  const char *expr = "   2 + -3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression06) {
  double result = -2.0 + -3.0;
  const char *expr = "   -2 + -3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression07) {
  double result = -2.0 - -3.0;
  const char *expr = "   -2 - -3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression08) {
  double result = -2.0 / -3.0;
  const char *expr = "   -2 / -3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression09) {
  double result = -2.0 * +3.0;
  const char *expr = "   -2 * +3  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression10) {
  double result = std::pow(2.0, 10.0);
  const char *expr = "   2.0 ^ 10.0  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression11) {
  double result = std::fmod(278.3, 10.0);
  const char *expr = "   278.3 mod 10.0  ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression12) {
  double result = std::sin(278.3);
  const char *expr = "   sin(278.3) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression13) {
  double result = std::cos(278.3);
  const char *expr = "   cos(278.3) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression14) {
  double result = std::tan(278.3);
  const char *expr = "   tan(278.3) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression15) {
  double result = std::asin(0.51234);
  const char *expr = "   asin(0.51234) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression16) {
  double result = std::acos(0.51234);
  const char *expr = "   acos(0.51234) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression17) {
  double result = std::atan(0.51234);
  const char *expr = "   atan(0.51234) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression18) {
  double result = std::log(1024.8);
  const char *expr = "   ln(1024.8) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression19) {
  double result = std::log10(1024.8);
  const char *expr = "   log(1024.8) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression20) {
  double result = std::pow(2.0, std::pow(2.0, 3.0));
  const char *expr = "   2 ^ 2 ^ 3 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression21) {
  double result = 2.0 * std::pow(2.0, 3.0);
  const char *expr = "   2 * 2 ^ 3 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression22) {
  double result = std::pow(2.0, 3.0) / 5;
  const char *expr = "  2 ^ 3 / 5 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression23) {
  const char *expr = " 2 + 3 + ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(),
            std::string{"parser: error near the end of the line"});
}

TEST_F(SmartcalcTest, Expression24) {
  const char *expr = " (2 + 3 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), std::string{"parser: unpaired brackets"});
}

TEST_F(SmartcalcTest, Expression25) {
  const char *expr = " 2 + 3 - 4) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), std::string{"parser: unpaired brackets"});
}

TEST_F(SmartcalcTest, Expression26) {
  double result = 2. + 3. - 4. * 5. - ((3. + 2.) / 10. - 6.);
  const char *expr = " 2 + 3 - 4 * 5 - ((3 + 2) / 10 -6) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression27) {
  double result = 2. + 3. - 4. * 5. - ((3. + 2.) / 10. - 6.);
  const char *expr = " 2 + 3 - 4 * 5 - ((3 + 2) / 10 -6) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression28) {
  double result = 2. - (std::log10(100. * (std::pow(std::sin(13. - 2.), 2.) +
                                           std::pow(std::cos(9. + 2.), 2.))) *
                        3.0);
  const char *expr = "2 - (log(100 * (sin(13 - 2)^2 + cos(9 + 2)^2)) * 3)";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression29) {
  const char *expr = " 2 + x - 43";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: unknown token x");
}

TEST_F(SmartcalcTest, Expression30) {
  double result = std::sqrt(1024.5) - 0.5;
  const char *expr = " sqrt(1024.5) - 0.5";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression31) {
  const char *expr = " 2 4 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token 4.000000");
}

TEST_F(SmartcalcTest, Expression32) {
  const char *expr = " ) 4 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token )");
}

TEST_F(SmartcalcTest, Expression33) {
  const char *expr = " sin 4 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token 4.000000");
}

TEST_F(SmartcalcTest, Expression34) {
  const char *expr = " 2 x ";

  bool ret = sc.SetFunction("y", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token x");
}

TEST_F(SmartcalcTest, Expression35) {
  const char *expr = " -+1 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token +");
}

TEST_F(SmartcalcTest, Expression36) {
  const char *expr = " 1 sin(3) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token sin");
}

TEST_F(SmartcalcTest, Expression37) {
  const char *expr = " 1 (1 -4) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token (");
}

TEST_F(SmartcalcTest, Expression38) {
  double result = std::fmod(2. * 4, 3.);
  const char *expr = " 2 * 4 mod 3 ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression39) {
  double result = 1 + std::pow(2., std::pow(3., 4.));
  const char *expr = " 1 + 2 ^ 3 ^ 4";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}


TEST_F(SmartcalcTest, Variable01) {
  double result = 2. - 3. + 4. * 8.;
  const char *expr = "2 - 3 + 4 * 8";

  bool ret = sc.SetVariable("x", expr);
  EXPECT_TRUE(ret);
  ret = sc.CalculateExpression("x");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
  result = std::pow(result, 3.0);
  ret = sc.CalculateExpression("x ^ 3");
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Variable02) {
  double result = 2. - 3. + 4. * 8.;
  const char *expr = "2 - 3 + 4 * 8";

  bool ret = sc.SetVariable("x", expr);
  EXPECT_TRUE(ret);
  ret = sc.CalculateExpression("x");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
  result = std::pow(result, 3.0);
  ret = sc.CalculateExpression("x ^ 3");
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Variable03) {
  const char *expr = "2 - 3 + 4 * 8";

  bool ret = sc.SetVariable("", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "'' is invalid name for a variable");

  ret = sc.SetVariable("123", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "'123' is invalid name for a variable");

  ret = sc.SetVariable(" x", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "' x' is invalid name for a variable");
}

TEST_F(SmartcalcTest, Variable04) {
  const char *expr = "2 - 3 + 4 * 8";

  bool ret = sc.SetVariable("asin", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "The name 'asin' is defined as the function");
}

TEST_F(SmartcalcTest, Variable05) {
  const char *expr = "2 - 3 + 4 * / 8";

  bool ret = sc.SetVariable("x", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(), "parser: error near token /");
}

TEST_F(SmartcalcTest, Function01) {
  const char *expr = "-sin(x)";

  bool ret = sc.SetFunction("func", expr);
  EXPECT_TRUE(ret);

  ret = sc.CalculateExpression("func(3)");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), -std::sin(3.0));

  ret = sc.CalculateExpression("func(19)");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), -std::sin(19.0));

  ret = sc.CalculateExpression("func(19) + 1");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), -std::sin(19.0) + 1.0);

  ret = sc.CalculateExpression("func(19) + 1 - 4 * func(16 - 3)");
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(),
                   -std::sin(19.0) + 1.0 - 4 * -std::sin(16.0 - 3.0));
}

TEST_F(SmartcalcTest, Function02) {
  const char *expr = "-sin(x)";

  bool ret = sc.SetFunction("12func", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ("'12func' is invalid name for a function", sc.ErrorMessage());
}

TEST_F(SmartcalcTest, Function03) {
  const char *expr = "-sin(x)";

  bool ret = sc.SetFunction("PI", expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ("The name 'PI' is defined as the variable", sc.ErrorMessage());
}

TEST_F(SmartcalcTest, GetFuncNames) {
  auto lst = sc.GetFuncNames();
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_FALSE(it->empty());
  }
}

TEST_F(SmartcalcTest, GetVarNames) {
  auto lst = sc.GetVarNames();
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_FALSE(it->empty());
  }
}

TEST_F(SmartcalcTest, GetPlot) {
  auto vec = sc.GetPlot("sin", {-10.0, 10.0}, {-10.0, 10.0});
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    // std::cout << it->first << "  " << it->second << "\n";
    double a = it->first + it->second;
    (void)a;
  }
}
