
#include <string>

#include "HTMLDocument.h"

#ifndef _HTMLPARSER_H_
#define _HTMLPARSER_H_

namespace HTMLParser {

    class Parser {

        public:
            // TODO: add suport for "const char*" and add destructor
            Parser(std::string p_html);

            Document* get_document() { return _document; }

        private:
            Document* _document;
    };
}

#endif /* _HTMLPARSER_H_ */
