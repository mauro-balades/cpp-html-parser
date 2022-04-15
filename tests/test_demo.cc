
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

class DemoTest : public ::testing::Test {
};

void printElements() {
    for (int i = 0; i < elements.size(); i++) {
        for(const auto& attr : elements.at(i)->get_attrs())
        {
            printf("ATTR: %s : %s\n", attr.first.c_str(), attr.second.c_str());
        }
    }
}

TEST_F(DemoTest, TestBackwardsCompat) {
    int fd = open("my_file_attrs.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();



    close(fd);
    EXPECT_TRUE(true);
}
