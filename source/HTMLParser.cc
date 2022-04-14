
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

                while (true) {
                    END_IF_EOF()

                    GET_NEXT_TOKEN()
                    IF_TOKEN(TokenType::CTAG)
                        break;
                    END_BLOCK()

                    
                }

                // ~Parse HTML element's attributes

                p_parent->add_element(element);
                delete element;

            END_BLOCK()
        END_BLOCK()
    }
}
