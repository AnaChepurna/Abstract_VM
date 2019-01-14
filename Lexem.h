//
// Created by Anastasia CHEPURNA on 2019-01-14.
//

#ifndef ABSTRACT_VM_LEXEMAV_H
#define ABSTRACT_VM_LEXEMAV_H

#include "IOperand.h"

class Lexem {
public:
    enum eLexemType {
        PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT
    };

private:
    eLexemType _lexemType;
    IOperand const* _value;
    Lexem();

public:
    explicit Lexem(eLexemType type);
    Lexem(eLexemType type, IOperand const* value);
    ~Lexem();
    Lexem(Lexem const &src);
    Lexem &operator=(Lexem const &src);
    eLexemType getType();
    IOperand const* getValue();
};


#endif //ABSTRACT_VM_LEXEMAV_H
