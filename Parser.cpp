//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(VirtualMachine const *vm) : _vm(vm), _lexer(new Lexer()), _filename(""), src(src) {}

Parser::~Parser() {
    delete(_lexer);
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    this->_lexer = src._lexer;
    this->_vm = src._vm;
    return *this;
}

void Parser::getCode() {
    readSrc();
}

void Parser::readSrc() {
    std::string str;
    if (_filename == "")
    {
        while (std::getline(std::cin, str))
        {
            std::
            if (_lexer->isEnd(str))
                break;
        }
    }
}

