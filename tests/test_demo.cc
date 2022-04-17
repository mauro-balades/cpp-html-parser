
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

void printElements(std::vector<HTMLParser::HTMLElement*> elements, int index = 0) {
    if (elements.size() == 0) return;

    for (int i = 0; i < elements.size(); i++) {
        HTMLParser::HTMLElement* element = elements.at(i);

        std::string tab_repeat("");
        tab_repeat.insert(0, index, '\t');

        printf("%s%s (%i) [", tab_repeat.c_str(), element->get_tagname().c_str(), index);

        for(const auto& attr : element->get_attrs())
        {
            printf("%s: \"%s\", ", attr.first.c_str(), attr.second.c_str());
        }

        printf("]");

        if (element->type() == std::string("text") || element->type() == std::string("comment")) {
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
                "<!-- hello -->"
                "<link rel=\"stylesheet\" href=\"style.css\" />"
            "</head>"
            "<body>"
                "<h1>This is a great header</h1>"
                "<p style=\"color: red;\">Lorem ipsum...</p>"
            "</body>"
        "</html>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    printElements(elements);

    EXPECT_TRUE(true);
}
