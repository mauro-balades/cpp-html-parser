
#include <gtest/gtest.h>
#include <HTMLParser/HTMLParser.h>

class AutoclosingElementsTest : public ::testing::Test {
};

TEST_F(AutoclosingElementsTest, TestBackwardsCompat) {
    std::string code = "<input /><button type='submit'>submit</button>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();

    std::vector<HTMLParser::HTMLElement*> elements = parser->dom()->get_elements();
    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i)->get_tagname() == "input") {
            for(const auto& attr : elements.at(i)->get_attrs()) {
                EXPECT_TRUE(attr.first == std::string("placeholder"));
                EXPECT_TRUE(attr.second == std::string("please, enter a password"));
            }
        }
        if (elements.at(i)->get_tagname() == "button") {
            EXPECT_TRUE(elements.at(i)->get_elements().at(0)->raw_text() == std::string("submit"));

            for(const auto& attr : elements.at(i)->get_attrs()) {
                EXPECT_TRUE(attr.first == std::string("type"));
                EXPECT_TRUE(attr.second == std::string("submit"));
            }
        }
    }
}

