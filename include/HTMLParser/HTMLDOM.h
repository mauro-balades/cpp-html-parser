
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
            void add_child(HTMLElement* p_element) { add_element(p_element); } // For better readability for the user (used for children elements in parents)

            std::vector<HTMLElement*> get_elements() { return _elements; }
            std::vector<HTMLElement*> get_children() { return get_elements(); } // For better readability for the user (used for children elements in parents)

        private:
            std::string _html;
            std::vector<HTMLElement*> _elements;
    };
}

#endif /* _HTMLPARSER_DOM_H_ */
