//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H

#include <string>
#include <regex>
#include "Token.h"


class Lexer {
public:
    Lexer();
    ~Lexer();
    Lexer(Lexer const& src);
    Lexer &operator=(Lexer const &src);

    bool isEnd(std::string str);
    Token * getToken(std::string str);
    bool isComment(std::string basic_string);
    eOperandType getOperandType(std::string &str);
    bool isInt(std::string& str);
    bool isFloat(std::string& str);

class UnexpectedLexemException: public std::exception {};
class MissedWhitespaceException : public std::exception {};
class UnknownOperandTypeException : public std::exception {};
class UnexpectedNumericalValueSybolException : public  std::exception {};

private:
    std::vector<std::string> pattern = {"push", "pop", "dump", "assert", "add",
                                                 "sub", "mul", "div", "mod", "print", "exit", "dump_type"};
    std::vector<std::string> pattern_operands = {"int8", "int16", "int32", "float", "double"};
};


#endif //ABSTRACT_VM_LEXER_H
