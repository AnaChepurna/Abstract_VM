//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#include "Lexem.h"

Lexem::Lexem(Lexem::eLexemType type, const IOperand *value): _lexemType(type), _value(value) {}

Lexem::Lexem() {}

Lexem::Lexem(Lexem::eLexemType type): _lexemType(type) {}

Lexem::~Lexem() {}

Lexem::Lexem(Lexem const &src) {
    *this = src;
}

Lexem &Lexem::operator=(Lexem const &src) {
    this->_lexemType = src._lexemType;
    this->_value = src._value;
    return *this;
}

Lexem::eLexemType Lexem::getType() {
    return _lexemType;
}

IOperand const *Lexem::getValue() {
    return _value;
}
