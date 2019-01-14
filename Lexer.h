//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H

#include <string>
#include "Token.h"

class Lexer {
public:
    Lexer();
    ~Lexer();
    Lexer(Lexer const& src);
    Lexer &operator=(Lexer const &src);

    bool isEnd(std::string str);
    Token * getLexem(std::string str);
    bool isComment(std::string basic_string);

private:
    static std::string const patterns[11];
    void strStartTrim(std::string &str);
};


#endif //ABSTRACT_VM_LEXER_H
