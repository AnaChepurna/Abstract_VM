//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#include "Token.h"

Token::Token() {}

Token::Token(Token::eTokenType type): _tokenType(type) {}

Token::~Token() {}

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
