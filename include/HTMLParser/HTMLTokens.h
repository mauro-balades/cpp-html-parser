
#include <vector>
#include <string>

#ifndef _HTMLPARSER_TOKENS_H_
#define _HTMLPARSER_TOKENS_H_

namespace HTMLParser {

    enum TokenType {
        _EOF = 0,

        OTAG, // Opening tag (<)
        CTAG, // Closing tag (>)

        DASH, // a.k.a dividing symbol (/)

        IDNT, // Identifier
        OTHER,
    };

    struct TokenPosition {
        int y;
        int x;
    };

    struct Token {
        std::string content;

        TokenType type;
        std::vector<TokenPosition> pos;
    };

    // Methods
    TokenType get_token_type(std::string character) {
        switch (character.c_str()) {
            case '<':
                return TokenType.OTAG;
            case '>':
                return TokenType.CTAG;

            case '/':
                return TokenType.DASH;

            default:
                return TokenType.OTHER;
        }
    }

}

#endif /* _HTMLPARSER_TOKENS_H_ */
