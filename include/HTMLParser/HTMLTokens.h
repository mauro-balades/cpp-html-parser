
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
        int y;
        int x;
    };

    struct Token {
        std::string content;

        TokenType type;
        std::vector<TokenPosition> pos;
    };
}

#endif /* _HTMLPARSER_TOKENS_H_ */
