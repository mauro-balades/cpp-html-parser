
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#include "HTMLParser/HTMLElement.h"

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

        printf("TOK LEN: %li\n", _tokens.size());
        while(pos != _tokens.size()) {
            Token current_token = _tokens[pos];

            switch (current_token.type) {

                case TokenType::OTAG: {

                    HTMLElement* element = new HTMLElement();

                    GET_NEXT_TOKEN();
                    if (current_token.type == TokenType::IDNT) {
                        element->set_tagname(current_token.content);
                    }

                    element->set_attrs(_parse_attrs());

                    for (int )

                    _dom->add_element(element);
                    delete element;
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
            printf("CUR: %s\n", current_token.content.c_str());

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
