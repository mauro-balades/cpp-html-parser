
#include <string>

#include "HTMLTokenizer.h"
#include "HTMLDOM.h"

#ifndef _HTMLPARSER_H_
#define _HTMLPARSER_H_

namespace HTMLParser {

    class Parser {

        public:
            // TODO: add suport for "const char*" and add destructor
            Parser(std::string p_html);

            DOM* get_dom() { return _dom; }
            void parse();

            void tokenize() { _tokenizer->tokenize(); }

            Tokenizer* get_tokenizer() { return _tokenizer; }

        private:
            DOM* _dom;
            Tokenizer* _tokenizer;
            std::vector<Token>::size_type pos = 0;
            std::vector<Token> _tokens;

            std::map<std::string, std::string> _parse_attrs();
            Token peek();
    };
}

#endif /* _HTMLPARSER_H_ */
