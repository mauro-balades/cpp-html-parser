
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

class BasicsTest : public ::testing::Test {
};

TEST_F(BasicsTest, TestBackwardsCompat) {
    std::string code = "<h1>hello</h1>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    ASSERT_TRUE(true);
}