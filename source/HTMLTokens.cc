
#include "HTMLParser/HTMLTokens.h"

#include <string>
#include <cstring>

#define CASE(x, y) if (character == x) return y;

namespace HTMLParser {

    TokenType get_token_type(std::string character) {

        CASE("=", TokenType::EQU)
        CASE("<", TokenType::OTAG)
        CASE(">", TokenType::CTAG)
        CASE("/", TokenType::DASH)
        CASE("!", TokenType::EXCL)
        CASE("'", TokenType::QUOT)
        CASE(" ", TokenType::SPAC)
        CASE("\"", TokenType::QUOT)

        // Default should be other such as a character (A-Za-z1-0) wich it should be an identifier.
        return TokenType::IDNT;
    }

}