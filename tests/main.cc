
#include <gtest/gtest.h>

class BasicsTest : public ::testing::Test {
};

TEST_F(BasicsTest, TestBackwardsCompat) {

    ASSERT_TRUE(true);
}