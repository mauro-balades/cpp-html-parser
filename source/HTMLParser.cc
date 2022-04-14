
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#include "HTMLParser/HTMLElement.h"

#include <string>

#define GET_NEXT_TOKEN() token++;

#define IF_TOKEN(tk) if (token->type == tk) {
#define END_BLOCK() }

#define END_IF_EOF()            \
    IF_TOKEN(TokenType::_EOF)   \
        break;                  \
    END_BLOCK()                 \

#define LOOP_TOKENS() for(std::vector<Token>::iterator token = tokens.begin(); token != tokens.end(); ++token) {
#define NEW_ELEMENT() HTMLElement* element = new HTMLElement();

#define NEW_ATTRS() std::map<std::string, std::string> element_attrs;
#define ADD_ATTR(x, y)  element_attrs.insert(std::pair<std::string, std::string>(x, y));

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

        std::vector<Token> tokens = _tokenizer->get_tokens();
        LOOP_TOKENS()
            printf("TOK: %s\n", token->content.c_str());
            IF_TOKEN(TokenType::OTAG)
                GET_NEXT_TOKEN()
                NEW_ELEMENT()

                IF_TOKEN(TokenType::IDNT)
                    element->set_tagname(token->content);
                END_BLOCK()
                END_IF_EOF()

                // Parse HTML element's attributes

                NEW_ATTRS()
                while (true) {
                    END_IF_EOF()

                    GET_NEXT_TOKEN()
                    IF_TOKEN(TokenType::CTAG)
                        break;
                    END_BLOCK()
                    IF_TOKEN(TokenType::IDNT)
                        std::string attr_name = token->content;
                        std::string attr_val  = "";

                        GET_NEXT_TOKEN()
                        IF_TOKEN(TokenType::EQU)

                            GET_NEXT_TOKEN()
                            IF_TOKEN(TokenType::QUOT)
                                while (true) {
                                    END_IF_EOF()

                                    IF_TOKEN(TokenType::QUOT)
                                        break;
                                    END_BLOCK()

                                    attr_val += token->content;
                                }
                            END_BLOCK()
                        END_BLOCK()

                        ADD_ATTR(attr_name, attr_val)
                    END_BLOCK()
                }

                // ~Parse HTML element's attributes
                IF_TOKEN(TokenType::CTAG)
                    GET_NEXT_TOKEN()
                END_BLOCK()

                p_parent->add_element(element);
                delete element;

            END_BLOCK()
        END_BLOCK()
    }
}
