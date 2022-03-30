
#include <vector>

#include "HTMLTokens.h"

#ifndef _HTMLPARSER_TOKENIZER_H_
#define _HTMLPARSER_TOKENIZER_H_

namespace HTMLParser {
    class Tokenizer {

        public:
            Tokenizer(Document p_document);
            void tokenize();

        private:
            Document* _document;
            std::vector<Token> _tokens;
    }
}

#endif /* _HTMLPARSER_TOKENIZER_H_ */
