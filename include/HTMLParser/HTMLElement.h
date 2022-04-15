
#include <map>
#include <string>
#include <vector>

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

            void set_raw_text(std::string p_raw) { _raw = p_raw; }
            std::string raw_text() { return _raw; }

            // Functions stolen from HTMLDOM to avoid #include infinite iteration
            void add_element(HTMLElement* p_element) { _elements.push_back(p_element); }
            std::vector<HTMLElement*> get_elements() { return _elements; }


        private:
            std::string _raw;
            std::string _type;
            std::string _tag_name;
            std::vector<HTMLElement*> _elements;
            std::map<std::string, std::string> _attrs;

    };

    // Special types of HTML elements
    class CommentElement : public HTMLElement {};
    class DocTypeElement : public HTMLElement {};

    // Normal HTML elements (supported with HTML 5)
    // note:
    //  If the HTML element is not supported in HTML 5,
    //  nor it does not exist in the list bellow,
    //  it will just be a HTMLElement class, with no special
    //  child class.
    class DivElement          : public HTMLElement {};
    class FormElement         : public HTMLElement {};
    class SpanElement         : public HTMLElement {};
    class LabelElement        : public HTMLElement {};
    class TableElement        : public HTMLElement {};
    class InputElement        : public HTMLElement {};
    class ImageElement        : public HTMLElement {};
    class SelectElement       : public HTMLElement {};
    class OptionElement       : public HTMLElement {};
    class AnchorElement       : public HTMLElement {};
    class ButtonElement       : public HTMLElement {};
    class TextAreaElement     : public HTMLElement {};
    class FieldSetElement     : public HTMLElement {};

    // Methods
    HTMLElement* get_html_element_by_tagname(std::string tagname);
}

#endif /* _HTMLPARSER_ELEMENT_H_ */
