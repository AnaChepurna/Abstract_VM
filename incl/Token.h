//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#ifndef ABSTRACT_VM_TOKEN_H
#define ABSTRACT_VM_TOKEN_H

#include "IOperand.h"
#include <vector>

class Token {
public:
    enum eTokenType {
        PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, DUMP_TYPE, COLOR, ABS, UP
    };

private:
    eTokenType _tokenType;
    IOperand const* _value = nullptr;

public:
    explicit Token(eTokenType type);
    ~Token();
    Token(Token const &src);
    Token &operator=(Token const &src);
    eTokenType getType() const;
    IOperand const* getValue() const;
    void setOperand(IOperand const *o);
    std::string getTypeString() const;
    static std::vector<std::string> const pattern;
};


#endif //ABSTRACT_VM_TOKEN_H
