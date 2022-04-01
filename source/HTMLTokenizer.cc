
#include "HTMLParser/HTMLTokens.h"
#include "HTMLParser/HTMLDocument.h"
#include "HTMLParser/HTMLTokenizer.h"

#include <iostream>

namespace HTMLParser {

    Tokenizer::Tokenizer(Document* p_document) {
        _document = p_document;
    }

    void Tokenizer::tokenize() {
        std::string html = _document->get_html();

        TokenPosition pos;

        pos.x = 0;
        pos.y = 0;

        for(std::string::size_type i = 0; i < html.size(); ++i) {

            std::string character = std::string(html[i], 1);

            if (character == "\n") {
                pos.y++;
                pos.x = 0;
            }

        }

    }
}

