
#include "HTMLParser/HTMLElement.h"
#include <string>

#define __RETURN_HTML_ELEMENT_IF_TAGNAME_IS(x, y) if (tagname == std::string(x)) { return new y(); }

namespace HTMLParser {

    HTMLElement* get_html_element_by_tagname(std::string tagname) {
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("a",        AnchorElement   )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("img",      ImageElement    )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("div",      DivElement      )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("form",     FormElement     )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("span",     SpanElement     )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("label",    LabelElement    )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("table",    TableElement    )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("input",    InputElement    )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("select",   SelectElement   )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("option",   OptionElement   )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("button",   ButtonElement   )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("textarea", TextAreaElement )
        __RETURN_HTML_ELEMENT_IF_TAGNAME_IS("fieldset", FieldSetElement )

        return new HTMLElement();
    }
}