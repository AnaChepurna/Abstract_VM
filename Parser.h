//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_PARSER_H
#define ABSTRACT_VM_PARSER_H


#include "VirtualMachine.h"
#include "Lexer.h"

class Parser {
private:
    VirtualMachine const*_vm;
    Lexer const* _lexer;
    std::string _filename;


    Parser();

public:
    explicit Parser(VirtualMachine const *vm);
    ~Parser();
    Parser(Parser const& src);
    Parser &operator=(Parser const &src);

};


#endif //ABSTRACT_VM_PARSER_H
