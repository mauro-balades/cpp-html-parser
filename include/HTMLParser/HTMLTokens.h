
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
    };

    struct TokenPosition {
        int y = 0;
        int x = 0;

        int real_pos = 0;
    };

    struct Token {
        std::string content;

        TokenType type;
        TokenPosition * pos;
    };

    // Methods
    TokenType get_token_type(std::string character);

}

#endif /* _HTMLPARSER_TOKENS_H_ */
