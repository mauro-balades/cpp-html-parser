
#include "HTMLParser/HTMLDOM.h"
#include "HTMLParser/HTMLParser.h"

#include "HTMLParser/HTMLElement.h"
#include "HTMLParser/HTMLTokenizer.h"


#include <string>
#include <typeinfo>

#define GET_NEXT_TOKEN() END_IF_EOF() ; _current_token = std::next(_current_token, 1);
#define GET_PREV_TOKEN() END_IF_EOF() ; _current_token = std::prev(_current_token, 1);
#define IGNORE_WHITE_SPACES()       \
    while (true) {                  \
        END_IF_EOF()                \
                                    \
        IFN_TOKEN(TokenType::SPAC)  \
            break;                  \
        END_BLOCK()                 \
                                    \
        GET_NEXT_TOKEN()            \
    }


#define IF_TOKEN(tk)  if (_current_token->type == tk) {
#define IFN_TOKEN(tk) if (_current_token->type != tk) {
#define END_BLOCK() }

#define PEEK() std::vector<Token>::iterator peek = _current_token + 1;
#define PEEK_BACKWARDS() std::vector<Token>::iterator peek = _current_token - 1;
#define END_IF_EOF()            \
    IF_TOKEN(TokenType::_EOF)   \
        return;                 \
    END_BLOCK()                 \

#define LOOP_TOKENS() for(std::vector<Token>::iterator token = tokens.begin(); token != tokens.end();) {
#define NEW_ELEMENT(name)                                     \
    HTMLElement* element = get_html_element_by_tagname(name); \
    element->set_tagname(name);

#define NEW_ATTRS() std::map<std::string, std::string> element_attrs;
#define ADD_ATTR(x, y)  element_attrs[x] = y;
#define COMMENT_END() std::string("--")

namespace HTMLParser {
    class Tokenizer;

    Parser::Parser(std::string p_html) {
        _dom = new DOM();

        _dom->set_html(p_html);
        _tokenizer = new Tokenizer(_dom);

    }

    void Parser::parse() {
        tokenize();

        std::vector<Token> tokens = _tokenizer->get_tokens();
        LOOP_TOKENS()
            if (token - tokens.begin() == 0)
                _current_token = token;

            token = _current_token;
            parse_elements(_dom, tokens);
            GET_NEXT_TOKEN()
        END_BLOCK()
    }

    template <typename T>
    void Parser::parse_elements(T* p_parent, std::vector<Token> tokens) {
        // Check if the character is an opening tag
        IF_TOKEN(TokenType::OTAG)

            // Consume the opening tag for the current token (<)
            IGNORE_WHITE_SPACES()
            GET_NEXT_TOKEN()

            // We check if the current token is a dash.
            // If it is a dash, we will just return, because
            // it means there is an error with the HTML document.
            // e.g. An empty element has a closing tag.
            // TODO: finish parsing the ending tag?
            IF_TOKEN(TokenType::DASH)
                return;
            END_BLOCK()

            // We migh have encountered a comment.
            IF_TOKEN(TokenType::EXCL)

                GET_NEXT_TOKEN()
                IGNORE_WHITE_SPACES()

                // See if the current token starts with "--". We do this because
                // "--" is considered as an identifier. This means that if we have
                // a comment like this: "<!--hello->" we will have the identifier
                // "--hello" and that is why we don't check for the token type.
                if (_current_token->content.rfind("--", 0) == 0) {

                    // Make a copy of the token's content to not change the current
                    // token's content.
                    std::string token_copy = _current_token->content;

                    // Remove the first 2 caracters of the comment ("--")
                    token_copy.erase(0, 2);

                    // Start an empty comment with the current token's content with the
                    // first 2 characters removed.
                    std::string comment_content = token_copy;

                    PEEK()
                    int end_comment = 0;

                    // We check if the next character is a closing symbol (>) and that the
                    // current token is exactly "--" or "---". This is because according to the HTML5
                    // specs, we can have comments such as: "<!-->" and "<!--->".
                    // https://html.spec.whatwg.org/multipage/parsing.html#parse-error-abrupt-closing-of-empty-comment
                    if (peek->type == TokenType::CTAG && (_current_token->content == "--" || _current_token->content == "---")) {
                        GET_NEXT_TOKEN() // Consume "--" or "---"
                        GET_NEXT_TOKEN() // Consume ">"

                        // Set the comment as closed.
                        end_comment = 1;
                    }

                    while (!end_comment) {
                        GET_NEXT_TOKEN()

                        // The next 2 if statements are used to check if the current token ends
                        // with "--"
                        if (_current_token->content.length() >= COMMENT_END().length()) {
                            if (0 == _current_token->content.compare (_current_token->content.length() - COMMENT_END().length(), COMMENT_END().length(), COMMENT_END()  )) {

                                PEEK()

                                // If the next token is a closing symbol (>) we just consume
                                // this 2 tokens and consither the comment as closed.
                                // TODO: add the current token's content to the comment
                                //       but remove the last 2 characters
                                if (peek->type == CTAG) {
                                    GET_NEXT_TOKEN()
                                    GET_NEXT_TOKEN()
                                    break;
                                }
                            }
                        }

                        comment_content += _current_token->content;
                    }

                    // Create a new element with the "#comment" tagname
                    NEW_ELEMENT("#comment")

                    // Set type and raw text to the comment.
                    element->set_raw_text(comment_content);
                    element->set_type("comment");

                    // Add it to the parent element.
                    p_parent->add_element(element);
                }

                return;
            END_BLOCK()

            // We check if the current token is of type TokenType::_EOF.
            // If it is, we just break the loop since it means that we
            // go to the end of the document.
            END_IF_EOF()

            // By default, the tag name  will be empty.
            // this is not allowed in HTML5 as said in the specs.
            // otherwise, if the current token is an identifier,
            // we will put this token's content as the tagname.
            // <tagname ...
            //  ^~~~~~^
            std::string tagname = "";
            IF_TOKEN(TokenType::IDNT)
                tagname = _current_token->content;
            END_BLOCK()

            // Create a new instance of an element.
            // This macro also has another functionality.
            // It gets an appropiate class for the element
            // depending on the tagname (wich it is why tagname
            // is a parameter). It also sets the tagname to that
            // element.
            NEW_ELEMENT(tagname)

            /// Parse HTML element's attributes

            // We create a new map of 2 strings that will be used
            // as a key-value list for the attributes. The first
            // item(key) will be considered as the attribute's
            // name. And the second one(value) is the attribute's
            // value.
            NEW_ATTRS()

            // We parse the attributes and insert the into the map
            // declared before.
            parse_attributes(element_attrs);

            // Set the attributes to the current element.
            element->set_attrs(element_attrs);

            // Detect if an element is an empty element.
            // If the element is an empty element, we do not
            // need to continue parsing because it is not "allowed"
            // to have elements inside it.
            // --------------------------------------------------------
            // If the element is empty AND it does have an empty tag,
            // this will be parsed at the top of the function because
            // we do not expect a closing tag.
            int element_is_autoclosed = detect_if_empty_element_by_tagname(tagname);

            // If there is a dash (/) we asume we encountered an empty class.
            if (_current_token->type == TokenType::DASH) { // e.g. <input />
                element_is_autoclosed = 1;
                GET_NEXT_TOKEN()
            }

            // If we found a closing tag symbol (>), we just consume
            // it. we expect a closing tag symbol anyways because we
            // just finished parsing the opening tag.
            // TODO: Throw an error if there is no closing symbol (>)?
            IF_TOKEN(TokenType::CTAG)
                GET_NEXT_TOKEN()
            END_BLOCK()

            // Check if we have an empty element. If we have an empty tag,
            // just ignore this steps and don't parse any child elements.
            if (!element_is_autoclosed) {

                while (true) {

                    // Parse inner elements of the current element.
                    // <div><p></p></div>
                    //      ^~~~~~^       - inner
                    // ^~~~^       ^~~~~^ - current
                    parse_elements(element, tokens);

                    IGNORE_WHITE_SPACES()
                    PEEK_BACKWARDS()

                    // Check if we found the closing tag (as expected).
                    // TODO: what happens if no ending tag?
                    if (peek->type == TokenType::OTAG) {

                        // We iterate infinitally untill we find a closing symbol (>).
                        // This is because ending tag might have attributes and this
                        // attributes MUST not be included into the final DOM.
                        // https://html.spec.whatwg.org/multipage/parsing.html#parse-error-end-tag-with-attributes
                        while (true) {
                            END_IF_EOF()

                            IF_TOKEN(TokenType::CTAG)

                                // Add the parent to the DOM.
                                // We only add it IF we do not
                                // encounter an EOF or a ">"
                                p_parent->add_element(element);

                                // Consume ">"
                                GET_NEXT_TOKEN()

                                // Return because if the element is an
                                // empty element, we would add it to the
                                // end of the function. This is to prevent
                                // duplication.
                                return;
                            END_BLOCK()

                            // Keep getting the next token until
                            // we find EOF or ">". To prevent infinite
                            // loops.
                            GET_NEXT_TOKEN()
                        }
                    }
                }
                // ~Consume the closing tag
            }

            p_parent->add_element(element);
            END_IF_EOF()

        END_BLOCK()
        IF_TOKEN(TokenType::IDNT)
            parse_text(p_parent);
        END_BLOCK()
    }

    template <typename T>
    void Parser::parse_text(T* p_parent) {
        NEW_ELEMENT("#text")
        element->set_type("text");

        std::string element_text = "";

        while (true) {
            END_IF_EOF()

            element_text += _current_token->content;
            GET_NEXT_TOKEN()

            IF_TOKEN(TokenType::OTAG)

                PEEK()
                if (peek->type != TokenType::DASH || peek->type != TokenType::IDNT) {
                    break;
                }
                break;
            END_BLOCK()
        }

        element->set_raw_text(element_text);
        p_parent->add_element(element);
    }

    void Parser::parse_attributes(std::map<std::string, std::string> &element_attrs) {
        while (true) {

            // Always get the next token to
            // prevent an infinite loop.
            GET_NEXT_TOKEN()

            // If we find any of this characters,
            // we encountered the end of the tag.
            // we shall stop this loop end finish
            // parsing the element.
            IF_TOKEN(TokenType::CTAG)
                break;
            END_BLOCK()
            IF_TOKEN(TokenType::DASH)
                break;
            END_BLOCK()

            // Otherwise, if we have an identifier,
            // we got an attribute name.
            IF_TOKEN(TokenType::IDNT)

                std::string attr_name = _current_token->content;
                std::string attr_val  = "";

                // get the next character that is
                // not a white space.
                IGNORE_WHITE_SPACES()
                GET_NEXT_TOKEN()

                // IF we encounter an equal sign,
                // we will parse attribute's content.
                // if not, we will just set it to default
                // value ("")
                // https://html.spec.whatwg.org/multipage/parsing.html#parse-error-missing-attribute-value
                IF_TOKEN(TokenType::EQU)


                    IGNORE_WHITE_SPACES()
                    GET_NEXT_TOKEN()

                    // Check if the current (non white space) token
                    // is a quote.
                    // TODO: handle un-quoted attribute value
                    IF_TOKEN(TokenType::QUOT)
                        while (true) {

                            // Keep adding the current token's
                            // to the attribute's value.
                            // TODO: check if quotes are the same
                            // TODO: checked if quote is scaped
                            GET_NEXT_TOKEN()
                            IF_TOKEN(TokenType::QUOT)
                                break;
                            END_BLOCK()

                            // Add content to the attribute's value.
                            attr_val += _current_token->content;
                        }
                    END_BLOCK()
                END_BLOCK()

                // Add a new attribute to the list.
                // note: we use operator[] because,
                // if the attribute already exists, we can
                // just replace it's value with a new one.
                // https://html.spec.whatwg.org/multipage/parsing.html#parse-error-duplicate-attribute
                ADD_ATTR(attr_name, attr_val)
            END_BLOCK()

        }
    }
}
