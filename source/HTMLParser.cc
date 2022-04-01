
#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/HTMLDocument.h"
#include "HTMLParser/HTMLTokenizer.h"

namespace HTMLParser {
    class Tokenizer;

    Parser::Parser(std::string p_html) {
        _document = new Document();

        _document->set_html(p_html);
        _tokenizer = new Tokenizer(_document);

    }

    void Parser::parse() {
        tokenize();
    }
}
