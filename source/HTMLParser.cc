
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLParser.h"

#include "HTMLParser/HTMLElement.h"
#include "HTMLParser/HTMLTokenizer.h"


#include <string>
#include <typeinfo>

#define GET_NEXT_TOKEN() END_IF_EOF() ; _current_token = std::next(_current_token, 1);
#define GET_PREV_TOKEN() END_IF_EOF() ; _current_token = std::prev(_current_token, 1);
#define IGNORE_WHITE_SPACES()       \
    while (true) {                  \
        END_IF_EOF()                \
                                    \
        IFN_TOKEN(TokenType::SPAC)  \
            break;                  \
        END_BLOCK()                 \
                                    \
        GET_NEXT_TOKEN()            \
    }


#define IF_TOKEN(tk)  if (_current_token->type == tk) {
#define IFN_TOKEN(tk) if (_current_token->type != tk) {
#define END_BLOCK() }

#define PEEK() std::vector<Token>::iterator peek = _current_token + 1;
#define PEEK_BACKWARDS() std::vector<Token>::iterator peek = _current_token - 1;
#define END_IF_EOF()            \
    IF_TOKEN(TokenType::_EOF)   \
        return;                 \
    END_BLOCK()                 \

#define LOOP_TOKENS() for(std::vector<Token>::iterator token = tokens.begin(); token != tokens.end();) {
#define NEW_ELEMENT(name)                                     \
    HTMLElement* element = get_html_element_by_tagname(name); \
    element->set_tagname(name);

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

        std::vector<Token> tokens = _tokenizer->get_tokens();
        LOOP_TOKENS()
            if (token - tokens.begin() == 0)
                _current_token = token;

            token = _current_token;
            parse_elements(_dom, tokens);
            GET_NEXT_TOKEN()
        END_BLOCK()
    }

    template <typename T>
    void Parser::parse_elements(T* p_parent, std::vector<Token> tokens) {
        // Check if the character is an opening tag
        IF_TOKEN(TokenType::OTAG)

            // Create a new instance of the element and go to the next token (ignoring white spaces)
            IGNORE_WHITE_SPACES()
            GET_NEXT_TOKEN()

            IF_TOKEN(TokenType::DASH)
                return;
            END_BLOCK()

            // We check if the current token is of type TokenType::_EOF.
            // If it is, we just break the loop since it means that we
            // go to the end of the document.
            END_IF_EOF()

            std::string tagname = "";
            IF_TOKEN(TokenType::IDNT)
                tagname = _current_token->content;
            END_BLOCK()

            NEW_ELEMENT(tagname)

            // Parse HTML element's attributes

            NEW_ATTRS()
            parse_attributes(element_attrs);
            element->set_attrs(element_attrs);

            // ~Parse HTML element's attributes

            int element_is_autoclosed = 0;

            if (_current_token->type == TokenType::DASH) { // e.g. <input />
                element_is_autoclosed = 1;
                GET_NEXT_TOKEN()
            }

            IF_TOKEN(TokenType::CTAG)
                GET_NEXT_TOKEN()
            END_BLOCK()

            if (!element_is_autoclosed) {

                while (true) {
                    parse_elements(element, tokens);
                    PEEK_BACKWARDS()
                    IGNORE_WHITE_SPACES()

                    // Consume the closing tag
                    if (peek->type == TokenType::OTAG) {

                        while (true) {
                            END_IF_EOF()

                            IF_TOKEN(TokenType::CTAG)
                                p_parent->add_element(element);
                                GET_NEXT_TOKEN()

                                return;
                            END_BLOCK()

                            GET_NEXT_TOKEN()
                        }
                    }
                }
                // ~Consume the closing tag
            }

            p_parent->add_element(element);
            END_IF_EOF()

        END_BLOCK()
        // IF_TOKEN(TokenType::IDNT)

        //     NEW_ELEMENT("#text")
        //     element->set_type("text");

        //     std::string element_text = "";

        //     while (true) {
        //         END_IF_EOF()

        //         element_text += _current_token->content;
        //         GET_NEXT_TOKEN()

        //         IF_TOKEN(TokenType::OTAG)

        //             PEEK()
        //             if (peek->type != TokenType::DASH) {
        //                 parse_elements(p_parent, tokens);
        //             } else {
        //                 GET_NEXT_TOKEN()
        //                 GET_NEXT_TOKEN()
        //             }
        //             break;
        //         END_BLOCK()
        //     }

        //     element->set_raw_text(element_text);
        //     p_parent->add_element(element);

        // END_BLOCK()
    }

    void Parser::parse_attributes(std::map<std::string, std::string> &element_attrs) {
        while (true) {
            GET_NEXT_TOKEN()

            IF_TOKEN(TokenType::CTAG)
                break;
            END_BLOCK()
            IF_TOKEN(TokenType::DASH)
                break;
            END_BLOCK()

            IF_TOKEN(TokenType::IDNT)

                std::string attr_name = _current_token->content;
                std::string attr_val  = "";

                IGNORE_WHITE_SPACES()
                GET_NEXT_TOKEN()

                IF_TOKEN(TokenType::EQU)

                    IGNORE_WHITE_SPACES()
                    GET_NEXT_TOKEN()

                    IF_TOKEN(TokenType::QUOT)
                        while (true) {
                            GET_NEXT_TOKEN()
                            IF_TOKEN(TokenType::QUOT)
                                break;
                            END_BLOCK()

                            attr_val += _current_token->content;
                        }
                    END_BLOCK()
                END_BLOCK()

                ADD_ATTR(attr_name, attr_val)
            END_BLOCK()

        }
    }
}
