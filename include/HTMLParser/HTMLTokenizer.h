
#include <vector>

#include "HTMLTokens.h"
#include "HTMLDocument.h"

#ifndef _HTMLPARSER_TOKENIZER_H_
#define _HTMLPARSER_TOKENIZER_H_

namespace HTMLParser {
    class Tokenizer {

        public:
            Tokenizer(Document* p_document);
            void tokenize();
            std::string _parse_word();


        private:
            Document* _document;
            std::vector<Token> _tokens;

            TokenPosition pos;
    };
}

#endif /* _HTMLPARSER_TOKENIZER_H_ */
