
#include "HTMLParser/HTMLTokens.h"
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLTokenizer.h"

#include <iostream>
#include <string.h>
#include <regex>

#define IS_WORD(x) (std::regex_match(x, std::regex("^[A-Za-z0-9_.]+$")))

namespace HTMLParser {

    Tokenizer::Tokenizer(DOM* p_dom) {
        _dom = p_dom;
    }

    void Tokenizer::tokenize() {
        std::string html = _dom->get_html();

        for(std::string::size_type i = 0; i < html.size() + 1; ++i) {

            if ((pos.real_pos + 1) >= (html.size() + 1)) break;

            std::string character(1, html.at(pos.real_pos));

            if (character == "\n") {
                pos.y++;
                pos.x = 0;
                pos.real_pos++;

                continue;
            }

            TokenType type = get_token_type(character);

            if (type == TokenType::OTHER) {
                if (IS_WORD(character.c_str())) {
                    std::string word = _parse_word();

                    type = TokenType::IDNT;
                    character = word;
                }
            }

            if (character != " ") { // ignore white spaces
                // printf("HTML LEN: %s\n", character.c_str());
                Token token = {
                    .content = character,

                    .type = type,
                    .pos = &pos,
                };

                _tokens.push_back(token);
            }

            pos.x++;
            pos.real_pos++;
        }

        Token token = {
            .content = "",

            .type = TokenType::_EOF,
            .pos = &pos,
        };

        _tokens.push_back(token);
    }

    std::string Tokenizer::_parse_word() {
        std::string html = _dom->get_html().substr(pos.real_pos);
        std::string word = "";

        int i = 0;
        std::string character(1, html.at(i));

        while (IS_WORD(character.c_str())) {

            word.append(character);

            if ((i + 1) < html.length()) {

                i++;
                pos.x++;
                pos.real_pos++;

                character = html.at(i);
                continue;
            }

            break;
        }

        pos.x--; // We increment it at the end of Tokenizer::tokenize()
        pos.real_pos--;

        return word;
    }
}

