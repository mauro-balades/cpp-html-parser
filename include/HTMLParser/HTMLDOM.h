
#include <string>
#include <vector>

#include "HTMLElement.h"

#ifndef _HTMLPARSER_DOM_H_
#define _HTMLPARSER_DOM_H_

namespace HTMLParser {

    class DOM {
        public:
            DOM() {}

            void set_html(std::string p_html) { _html = p_html; }
            std::string get_html() { return _html; }

            void add_element(HTMLElement* p_element) { _elements.push_back(p_element); }
            std::vector<HTMLElement*> get_elements() { return _elements; }

        private:
            std::string _html;
            std::vector<HTMLElement*> _elements;
    };
}

#endif /* _HTMLPARSER_DOM_H_ */
