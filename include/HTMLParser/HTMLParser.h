
#ifndef _HTMLPARSER_H_
#define _HTMLPARSER_H_

namespace HTMLParser {

    class Parser {

        public:
            // TODO: add suport for "const char*"
            Parser(std::string p_html);

            // ~Parser();

        private:
            std::string _html;
    }
}

#endif /* _HTMLPARSER_H_ */
