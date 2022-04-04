
#include <string>

#ifndef _HTMLPARSER_DOM_H_
#define _HTMLPARSER_DOM_H_

namespace HTMLParser {
    class DOM {
        public:
            DOM() {}

            void set_html(std::string p_html) { _html = p_html; }
            std::string get_html() { return _html; }

        private:
            std::string _html;
    };
}

#endif /* _HTMLPARSER_DOM_H_ */
