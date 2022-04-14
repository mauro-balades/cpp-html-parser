
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
    std::string code = "<h1>hello</h1><p>paragraph</p>";

    int fd = open("my_file.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    close(fd);
    EXPECT_TRUE(true);
}

