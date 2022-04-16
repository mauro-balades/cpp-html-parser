
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <vector>

class DemoTest : public ::testing::Test {
};

        // for(const auto& attr : element->get_attrs())
        // {
        //     printf("\tATTR: %s : %s\n", attr.first.c_str(), attr.second.c_str());
        // }

void printElements(std::vector<HTMLParser::HTMLElement*> elements, int index = 0) {
    if (elements.size() == 0) return;

    for (int i = 0; i < elements.size(); i++) {
        HTMLParser::HTMLElement* element = elements.at(i);

        std::string tab_repeat("");
        tab_repeat.insert(0, index, '\t');

        printf("%s%s (%i)", tab_repeat.c_str(), element->get_tagname().c_str(), index);

        if (element->type() == std::string("text")) {
            printf(" - %s\n", element->raw_text().c_str());
        } else {
            printf("\n");
        }

        printElements(element->get_elements(), index + 1);
    }
}

TEST_F(DemoTest, TestBackwardsCompat) {
    std::string code =
        "<html>"
            "<head>"
                "<link />"
            "</head>"
            "<body>"
                "<p></p>"
                "<d></d>"
                "<d><awd></awd></d>"
            "</body>"
        "</html>";
    // int fd = open("my_file_demo.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    // assert(fd >= 0);
    // int ret = dup2(fd, 1);
    // assert(ret >= 0);

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    printElements(elements);

    // close(fd);
    EXPECT_TRUE(true);
}
