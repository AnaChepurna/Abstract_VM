//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H


class Lexer {
public:
    Lexer();
    ~Lexer();
    Lexer(Lexer const& src);
    Lexer &operator=(Lexer const &src);
};


#endif //ABSTRACT_VM_LEXER_H
