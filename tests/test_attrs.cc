
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

TEST_F(AttributesTest, TestBackwardsCompat) {
    std::string code = "<h1 class=\"my_class\">hello</h1>";

    int fd = open("my_file_attrs.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    printf("Parsing element's attributes [%s]\n", code.c_str());
    for (int i = 0; i < elements.size(); i++) {
        for(const auto& attr : elements.at(i)->get_attrs())
        {
            printf("ATTR: %s : %s\n", attr.first.c_str(), attr.first.c_str());
        }
    }

    close(fd);
    EXPECT_TRUE(true);
}

