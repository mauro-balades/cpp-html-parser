
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

class TokenizerTest : public ::testing::Test {
};

TEST_F(TokenizerTest, TestBackwardsCompat) {
    std::string code = "<h1>hello</h1>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    EXPECT_TRUE(1);
}

