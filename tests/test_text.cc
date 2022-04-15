
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <vector>

class TextTest : public ::testing::Test {
};

TEST_F(TextTest, TestBackwardsCompat) {
    std::string code = "<h1>my text</h1>";

    int fd = open("my_file_text.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    printf("Parsing element's text [%s]\n", code.c_str());
    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i)->type() == "text")
            printf("TEXT: %s\n", elements.at(i)->raw_text().c_str());
    }

    close(fd);
    EXPECT_TRUE(true);
}

