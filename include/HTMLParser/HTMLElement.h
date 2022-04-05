
#include <map>
#include <string>

#ifndef _HTMLPARSER_ELEMENT_H_
#define _HTMLPARSER_ELEMENT_H_

namespace HTMLParser {
    class HTMLElement {
        public:
            HTMLElement() {}

            void set_tagname(std::string p_tagname) { _tag_name = p_tagname; }
            std::string get_tagname() { return _tag_name; }

            void set_attrs(std::map<std::string, std::string> p_attrs) { _attrs = p_attrs; }
            std::map<std::string, std::string> get_attrs() { return _attrs; }

            void set_type(std::string p_type) { _type = p_type; }
            std::string type() { return _type; }

        private:
            std::string _type;
            std::string _tag_name;
            std::map<std::string, std::string> _attrs;
    };
}

#endif /* _HTMLPARSER_ELEMENT_H_ */
