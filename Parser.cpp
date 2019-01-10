//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(VirtualMachine const *vm): _vm(vm), _lexer(new Lexer()), _filename(nullptr) {}

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

