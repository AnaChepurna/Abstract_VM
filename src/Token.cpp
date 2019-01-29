//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#include "Token.h"

std::vector<std::string> const Token::pattern = {"push", "pop", "dump", "assert", "add",
                                                 "sub", "mul", "div", "mod", "print", "exit", "dump_type",
                                                 "color"};

Token::Token(Token::eTokenType type): _tokenType(type) {}

Token::~Token() {
    if (_value != nullptr)
        delete(_value);
}

Token::Token(Token const &src) {
    *this = src;
}

Token &Token::operator=(Token const &src) {
    this->_tokenType = src._tokenType;
    this->_value = src._value;
    return *this;
}

Token::eTokenType Token::getType() const{
    return _tokenType;
}

IOperand const *Token::getValue() const{
    return _value;
}

void Token::setOperand(IOperand const *o) {
    _value = o;
}

std::string Token::getTypeString() const {
    return pattern.at(_tokenType);
}
