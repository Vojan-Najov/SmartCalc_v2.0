#include <gtest/gtest.h>
#include <cmath>

#include "smartcalc.h"

using Smartcalc = s21::Smartcalc;

class SmartcalcTest : public testing::Test {
 public:
  Smartcalc sc{};

  void SetUp(void) override {

  }
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
  EXPECT_EQ(sc.ErrorMessage(),
            std::string{"parser: unpaired brackets"});
}

TEST_F(SmartcalcTest, Expression25) {
  const char *expr = " 2 + 3 - 4) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_FALSE(ret);
  EXPECT_EQ(sc.ErrorMessage(),
            std::string{"parser: unpaired brackets"});
}

TEST_F(SmartcalcTest, Expression26) {
  double result = 2. + 3. - 4. * 5. - ((3. + 2.) / 10. -6.);
  const char *expr = " 2 + 3 - 4 * 5 - ((3 + 2) / 10 -6) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression27) {
  double result = 2. + 3. - 4. * 5. - ((3. + 2.) / 10. -6.);
  const char *expr = " 2 + 3 - 4 * 5 - ((3 + 2) / 10 -6) ";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

TEST_F(SmartcalcTest, Expression28) {
  double result = 2. - (std::log10(100. * (std::pow(std::sin(13. - 2.),2.) +
                                           std::pow(std::cos(9. + 2.), 2.))) * 3.0);
  const char *expr = "2 - (log(100 * (sin(13 - 2)^2 + cos(9 + 2)^2)) * 3)";

  bool ret = sc.CalculateExpression(expr);
  EXPECT_TRUE(ret);
  EXPECT_DOUBLE_EQ(sc.Result(), result);
}

