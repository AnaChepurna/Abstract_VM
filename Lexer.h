//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H

#include <string>
#include "Lexem.h"

class Lexer {
public:
    Lexer();
    ~Lexer();
    Lexer(Lexer const& src);
    Lexer &operator=(Lexer const &src);

    bool isEnd(std::string str) const;
    Lexem * getLexem(std::string str) const;
};


#endif //ABSTRACT_VM_LEXER_H
