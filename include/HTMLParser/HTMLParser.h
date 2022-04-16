
#include <map>
#include <string>

#include "HTMLTokenizer.h"
#include "HTMLDOM.h"
#include "HTMLElement.h"

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
            }

            Tokenizer* get_tokenizer() { return _tokenizer; }

            template <typename T>
            void parse_elements(T* p_parent, std::vector<Token> tokens);

            DOM* dom() { return _dom; }

        private:
            DOM* _dom;
            Tokenizer* _tokenizer;

            int pos = 0;

            std::map<std::string, std::string> _parse_attrs();
            Token peek();

            std::vector<HTMLParser::Token>::iterator _current_token;
            void parse_attributes(std::map<std::string, std::string> &element_attrs);
    };
}

#endif /* _HTMLPARSER_H_ */
