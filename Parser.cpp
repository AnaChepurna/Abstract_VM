//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include <sstream>
#include "Parser.h"

Parser::Parser() {
    _lexer = Lexer();
}


Parser::~Parser() {
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    this->_lexer = src._lexer;
    return *this;
}

std::vector<Token const *> Parser::getCode() {
    std::string str;
    if (_filename == "") {
        while (std::cin.good()) {
            std::getline(std::cin, str);
            if (!parseCode(str))
                break;
        }
    }
    else {
        std::fstream i;
        i.open(_filename);
        while (std::getline(i, str)) {
            if (!parseCode(str))
                break;
        }
        i.close();
    }
    return (_code);
}

bool Parser::parseCode(std::string str) {
    if (_lexer.isEnd(str))
        return false;
    std::stringstream stream(str);
    std::string substr;
    Token *token = nullptr;

    while (stream.good()) {
        std::getline(stream, substr, ' ');
        if (token == nullptr) {
            token = _lexer.getLexem(substr);
            if (token == nullptr)
                break;
        }
        else if (token->getValue() == nullptr) {
//            token->setOperand(new Operand<double>(Double, 22));
            std::cout << "needs operand!\n";
            if (token->getValue() == nullptr)
                break;
        }
        else {
//            if (!_lexer.isComment(substr))
//                error = true;
            break;
        }
    }
    if (token != nullptr)
        _code.insert(_code.end(), token);
    else
        delete(token);
    return true;
}


