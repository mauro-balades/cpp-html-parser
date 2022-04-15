
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
#define ADD_ATTR(x, y)  element_attrs[x] = y;

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

            // Check if the character is an opening tag
            IF_TOKEN(TokenType::OTAG)

                // Create a new instance of the element and go to the next token
                GET_NEXT_TOKEN()
                NEW_ELEMENT()

                // We check if the current token is of type TokenType::_EOF.
                // If it is, we just break the loop since it means that we
                // go to the end of the document.
                END_IF_EOF()

                IF_TOKEN(TokenType::IDNT)
                    element->set_tagname(token->content);
                END_BLOCK()

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

                                    GET_NEXT_TOKEN()
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

                element->set_attrs(element_attrs);

                // ~Parse HTML element's attributes
                IF_TOKEN(TokenType::CTAG)
                    GET_NEXT_TOKEN()
                END_BLOCK()

                p_parent->add_element(element);

            END_BLOCK()
            IF_TOKEN(TokenType::IDNT)
                NEW_ELEMENT()
                element->set_type("text");

                std::string element_text = "";

                while (true) {
                    END_IF_EOF()

                    IF_TOKEN(TokenType::OTAG)
                        break;
                    END_BLOCK()

                    element_text += token->content;
                    GET_NEXT_TOKEN()
                }

                element->set_raw_text(element_text);
                p_parent->add_element(element);

            END_BLOCK()
        END_BLOCK()
    }
}
