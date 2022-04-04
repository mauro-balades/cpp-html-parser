
#include <string>

#ifndef _HTMLPARSER_ELEMENT_H_
#define _HTMLPARSER_ELEMENT_H_

namespace HTMLParser {
    class HTMLElement {
        public:
            HTMLElement() {}

            void set_tagname(std::string p_html) { _tag_name = _tag_name; }
            std::string get_tagname() { return _tag_name; }

        private:
            std::string _tag_name;
    };
}

#endif /* _HTMLPARSER_ELEMENT_H_ */
