
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

class TokenizerTest : public ::testing::Test {
};

TEST_F(TokenizerTest, TestBackwardsCompat) {
    std::string code = "<h1>hello</h1>\n<p>paragraph</p>";
    
    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    EXPECT_TRUE(1);
}

