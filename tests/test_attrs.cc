
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <vector>

class AttributesTest : public ::testing::Test {
};

class AttributesWithDashTest : public ::testing::Test {
};

TEST_F(AttributesTest, TestBackwardsCompat) {
    std::string code = "<h1 class=\"my_class\"></h1>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    for (int i = 0; i < elements.size(); i++) {
        for(const auto& attr : elements.at(i)->get_attrs())
        {
            EXPECT_TRUE(attr.first == std::string("class"));
            EXPECT_TRUE(attr.second == std::string("my_class"));
        }
    }
}

TEST_F(AttributesWithDashTest, TestBackwardsCompat) {
    std::string code = "<h1 my-attribute=\"hello\"></h1>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    for (int i = 0; i < elements.size(); i++) {
        for(const auto& attr : elements.at(i)->get_attrs())
        {
            EXPECT_TRUE(attr.first == std::string("my-attribute"));
            EXPECT_TRUE(attr.second == std::string("hello"));
        }
    }
}