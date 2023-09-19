#include <gtest/gtest.h>
#include <utils/NumberUtils.h>

using namespace cpptest::utils;

TEST(NumberUtilsTestIsZero, isZeroInt) { ASSERT_TRUE(isZero(0)); }
TEST(NumberUtilsTestIsZero, isZeroFloat) { ASSERT_TRUE(isZero(0.0)); }

TEST(NumberUtilsTestIsZero, isNotZeroPositiveInt) { ASSERT_FALSE(isZero(5)); }
TEST(NumberUtilsTestIsZero, isNotZeroPositiveFloat) {
  ASSERT_FALSE(isZero(2.1));
}

TEST(NumberUtilsTestIsZero, isNotZeroNegativeInt) { ASSERT_FALSE(isZero(-1)); }
TEST(NumberUtilsTestIsZero, isNotZeroNegativeFloat) {
  ASSERT_FALSE(isZero(-0.1));
}

TEST(NumberUtilsTestIsPositive, IsPositiveInt) { ASSERT_TRUE(isPositive(1)); }
TEST(NumberUtilsTestIsPositive, IsPositiveFloat) {
  ASSERT_TRUE(isPositive(1.3));
}

TEST(NumberUtilsTestIsPositive, isNotPositiveInt) {
  ASSERT_FALSE(isPositive(0));
}
TEST(NumberUtilsTestIsPositive, isNotPositiveFloat) {
  ASSERT_FALSE(isPositive(-1.1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}