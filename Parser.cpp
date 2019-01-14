//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
}


Parser::~Parser() {
    delete(_lexer);
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    this->_lexer = src._lexer;
    return *this;
}

std::list<Lexem const *> Parser::getCode() {
    readSrc();
    return (_code);
}

void Parser::readSrc() {
    std::string str;
    if (_filename == "") {
        while (std::getline(std::cin, str)) {
            if (_lexer->isEnd(str))
                break;
            Lexem *lexem = _lexer->getLexem(str);
            if (lexem != nullptr)
                _code.insert(_code.end(), lexem);
        }
    }
    else {
        std::fstream i;
        i.open(_filename);
        while (std::getline(i, str)) {
            if (_lexer->isEnd(str))
                break;
            Lexem *lexem = _lexer->getLexem(str);
            if (lexem != nullptr)
                _code.insert(_code.end(), lexem);
        }
        i.close();
    }
}

