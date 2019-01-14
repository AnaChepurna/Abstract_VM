//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_PARSER_H
#define ABSTRACT_VM_PARSER_H

#include <string>
#include <list>
#include <fstream>
#include <vector>
#include "Lexer.h"

class Parser {
private:
    Lexer _lexer;
    std::string _filename;
    std::vector<Token const *>_code = {};
    bool error = false;

    bool parseCode(std::string code);

public:
    Parser();
    ~Parser();
    Parser(Parser const& src);
    Parser &operator=(Parser const &src);

    std::vector<Token const *> getCode();
};


#endif //ABSTRACT_VM_PARSER_H
