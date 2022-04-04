
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#define GET_NEXT_TOKEN()             \
    i++;                             \
    Token current_token = tokens[i]; \


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
        for(std::vector<Token>::size_type i = 0; i != tokens.size(); i++) {
            Token current_token = tokens[i];

            switch (current_token.type) {

                case TokenType::OTAG: {

                    GET_NEXT_TOKEN();
                    if (current_token.type == TokenType::IDNT) {
                        
                    }
                };
            }
        }
    }
}
