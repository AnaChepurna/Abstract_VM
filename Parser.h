//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_PARSER_H
#define ABSTRACT_VM_PARSER_H


#include "VirtualMachine.h"
#include "Lexer.h"

class Parser {
private:
    Lexer const* _lexer;
    std::string _filename;
    std::list<Lexem const *>_code;


    void readSrc();

public:
    Parser();
    ~Parser();
    Parser(Parser const& src);
    Parser &operator=(Parser const &src);

    std::list<Lexem const *> getCode();
};


#endif //ABSTRACT_VM_PARSER_H
