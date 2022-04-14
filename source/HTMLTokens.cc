
#include "HTMLParser/HTMLTokens.h"

#include <string>
#include <cstring>

namespace HTMLParser {

    TokenType get_token_type(std::string character) {

        if (character == "<") {
            return TokenType::OTAG;
        } else if (character == ">") {
            return TokenType::CTAG;
        } else if (character == "/") {
            return TokenType::DASH;
        } else if (character == "\"" || character == "'") {
            return TokenType::QUOT;
        } else if (character == "=") {
            return TokenType::EQU;
        }

        // Default should be other such as a character (A-Za-z1-0) wich it should be an identifier.
        return TokenType::IDNT;
    }

}