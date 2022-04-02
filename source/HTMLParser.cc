
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDocument.h"
#include "HTMLParser/HTMLTokenizer.h"

#define GET_NEXT_TOKEN()             \
    i++;                             \
    Token current_token = tokens[i]; \


namespace HTMLParser {
    class Tokenizer;

    Parser::Parser(std::string p_html) {
        _document = new Document();

        _document->set_html(p_html);
        _tokenizer = new Tokenizer(_document);

    }

    void Parser::parse() {
        tokenize();

        std::vector<Token> tokens = _tokenizer->get_tokens();
        for(std::vector<T>::size_type i = 0; i != tokens.size(); i++) {
            Token current_token = tokens[i];

            switch (token.type) {

                case TokenType::OTAG: {

                    GET_NEXT_TOKEN();
                    if (current_token.type == TokenType::IDNT) { // <idnt>

                    } else if (current_token.type == TokenType::CTAG) { // <>

                    } else { // ??
                        // TODO: throw any error?
                    }
                };
            }
        }
    }
}
