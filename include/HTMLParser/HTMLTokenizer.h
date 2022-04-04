
#include <vector>

#include "HTMLTokens.h"
#include "HTMLDOM.h"

#ifndef _HTMLPARSER_TOKENIZER_H_
#define _HTMLPARSER_TOKENIZER_H_

namespace HTMLParser {
    class Tokenizer {

        public:
            Tokenizer(DOM* p_dom);
            void tokenize();
            std::string _parse_word();

            std::vector<Token> get_tokens() { return _tokens; }

        private:
            DOM* _dom;
            std::vector<Token> _tokens;

            TokenPosition pos;
    };
}

#endif /* _HTMLPARSER_TOKENIZER_H_ */
