#include <HTMLParser/HTMLParser.h>

#include <string>
#include <iostream>

int main() {
    std::cout << "hello";
    std::string code = "<h1>hello</h1>";

    HTMLParser::Parser* parser = new HTMLParser::Parser(code);
    parser->parse();
    
    return 0;
}
