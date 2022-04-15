
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

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    printf("Parsing element's text [%s]\n", code.c_str());
    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i)->get_elements().at(0)->type() == "text")
            EXPECT_TRUE(elements.at(i)->get_elements().at(0)->raw_text() == std::string("my text"));
    }
}

