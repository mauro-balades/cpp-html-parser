
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#include "HTMLParser/HTMLElement.h"

#include <string>

#define GET_NEXT_TOKEN()                \
    pos++;                              \
    current_token = _tokens[pos]; \

namespace HTMLParser {
    class Tokenizer;

    Parser::Parser(std::string p_html) {
        _dom = new DOM();

        _dom->set_html(p_html);
        _tokenizer = new Tokenizer(_dom);

    }

    void Parser::parse() {
        tokenize();
        parse_elements(_dom);
    }

    template <typename T>
    void Parser::parse_elements(T* p_parent) {
        while (pos != _tokens.size()) {
            Token current_token = _tokens[pos];

            switch (current_token.type) {

                case TokenType::OTAG: {

                    HTMLElement* element = new HTMLElement();

                    GET_NEXT_TOKEN();
                    if (current_token.type == TokenType::IDNT) {
                        element->set_tagname(current_token.content);
                    } else if (current_token.type == TokenType::CTAG) {
                        delete element;
                        return;
                    }

                    element->set_attrs(_parse_attrs());
                    element->set_type("element");
                    GET_NEXT_TOKEN(); // TODO: check if next token is a <


                    parse_elements(element);

                    p_parent->add_element(element);
                    delete element;
                };

                case TokenType::_EOF:
                    break;

                default: {
                    if (current_token.type == TokenType::_EOF) {
                        return; // TODO: do something
                    }

                    Token current_token;
                    std::string text = "";


                    while (peek().type != TokenType::CTAG) {
                        GET_NEXT_TOKEN();

                        if (current_token.type == TokenType::_EOF) break;

                        text += current_token.content;

                    }


                    if (text != "") {

                        HTMLElement* element = new HTMLElement();
                        element->set_type("text");

                        element->set_raw_text(text);

                        p_parent->add_element(element);
                        delete element;
                    }

                };
            }

            pos++;
        }
    }

    Token Parser::peek() {
        // TODO: check if EOF
        return _tokens[pos + 1];
    }

    std::map<std::string, std::string> Parser::_parse_attrs() {
        std::map<std::string, std::string> attrs;
        Token current_token;

        while (peek().content != ">") {
            GET_NEXT_TOKEN();

            if (current_token.type == TokenType::IDNT) {
                std::string current_attr = current_token.content;
                std::string attr_content = "";

                if (peek().content == "=") {
                    GET_NEXT_TOKEN();

                    do {
                        GET_NEXT_TOKEN();
                        attr_content += current_token.content;
                    } while (peek().content != "\"");

                    GET_NEXT_TOKEN();
                    attr_content = current_token.content;
                }

                attrs[current_attr] = attr_content;
            }
        }

        return attrs;
    }
}
