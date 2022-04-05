
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

            void tokenize() {
                _tokenizer->tokenize();
                _tokens = _tokenizer->get_tokens();
            }

            Tokenizer* get_tokenizer() { return _tokenizer; }
            DOM* dom() { return _dom; }

        private:
            DOM* _dom;
            Tokenizer* _tokenizer;

            int pos = 0;
            std::vector<Token> _tokens;

            std::map<std::string, std::string> _parse_attrs();
            Token peek();
    };
}

#endif /* _HTMLPARSER_H_ */
