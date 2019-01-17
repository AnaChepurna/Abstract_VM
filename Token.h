//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#ifndef ABSTRACT_VM_TOKEN_H
#define ABSTRACT_VM_TOKEN_H

#include "IOperand.h"

class Token {
public:
    enum eTokenType {
        PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, DUMP_TYPE
    };

private:
    eTokenType _tokenType;
    IOperand const* _value = nullptr;
    Token();

public:
    explicit Token(eTokenType type);
    ~Token();
    Token(Token const &src);
    Token &operator=(Token const &src);
    eTokenType getType() const;
    IOperand const* getValue() const;
    void setOperand(IOperand const *o);
};


#endif //ABSTRACT_VM_TOKEN_H
