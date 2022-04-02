
#include <string>

#include "HTMLTokenizer.h"
#include "HTMLDocument.h"

#ifndef _HTMLPARSER_H_
#define _HTMLPARSER_H_

namespace HTMLParser {

    class Parser {

        public:
            // TODO: add suport for "const char*" and add destructor
            Parser(std::string p_html);

            Document* get_document() { return _document; }
            void parse();
            void tokenize() { _tokenizer->tokenize(); }

            Tokenizer* get_tokenizer() { return _tokenizer; }
            
        private:
            Document* _document;
            Tokenizer* _tokenizer;

    };
}

#endif /* _HTMLPARSER_H_ */
