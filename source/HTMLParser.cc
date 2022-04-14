
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#include "HTMLParser/HTMLElement.h"

#include <string>

#define GET_NEXT_TOKEN()                             \
    if (!((pos + 1) >= _tokens.size())) {            \
        pos++;                                       \
        current_token = _tokens[pos];                \
    } else {                                         \
        current_token = _tokens[_tokens.size() - 1]; \
    }

#define IF_TOKEN(tk) if (token.type == tk) {

#define END_TOKEN() }

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

        for(std::vector<Token>::iterator token = tokens.begin(); token != tokens.end(); ++token) {
            printf("TOK: %s\n", token->content.c_str());
        }
    }
}
