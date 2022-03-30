
#include "HTMLParser.h"

namespace HTMLParser {
    Parser::Parser(std::string p_html) {
        _document = new Document();

        _document->set_html(p_html);
    }

}
