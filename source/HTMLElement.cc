
#include "HTMLParser/HTMLElement.h"
#include <string>

#define __RETURN_HTML_ELEMENT_IF_TAGNAME_IS(x, y) if (tagname == std::string(x)) { return new y(); }
#define __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS(x) if (tagname == std::string(x)) { return 1; }

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

    int detect_if_empty_element_by_tagname(std::string tagname) {
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("br"     )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("wb"     )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("hr"     )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("col"    )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("img"    )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("link"   )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("meta"   )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("area"   )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("base"   )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("embed"  )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("input"  )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("param"  )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("track"  )
        __RETURN_IS_EMPTY_HTML_ELEMENT_IF_TAGNAME_IS("source" )

        return 0;
    }
}