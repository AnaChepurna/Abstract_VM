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
    Token * getToken(std::string str);
    bool isComment(std::string basic_string);
    eOperandType getOperandType(std::string &str);

class UnexpectedLexemException: public std::exception {};
class MissedWhitespaceException : public std::exception {};
class UnknownOperandTypeException : public std::exception {};

private:
    static std::string const patterns[11];
    static std::string const patterns_operands[5];
};


#endif //ABSTRACT_VM_LEXER_H
