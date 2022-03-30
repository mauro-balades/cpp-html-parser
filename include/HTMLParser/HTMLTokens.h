
#include <vector>

#ifndef _HTMLPARSER_TOKENS_H_
#define _HTMLPARSER_TOKENS_H_

namespace HTMLParser {
    struct TokenPosition {
        int y;
        int x;
    }

    struct Token {
        std::string content;

        
        std::vector<TokenPosition> pos;
    }
}

#endif /* _HTMLPARSER_TOKENS_H_ */
