//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_LEXER_H
#define ABSTRACT_VM_LEXER_H

#include <string>
#include <regex>
#include "Token.h"
#include "OperandFactory.h"


class Lexer {
public:
    Lexer();
    ~Lexer();

    bool isEnd(std::string str) const;
    Token * getToken(std::string str) const;
    bool isComment(std::string basic_string) const;
    eOperandType getOperandType(std::string &str) const;
    bool hasBrackets(std::string &str) const;
    bool isInt(std::string& str) const;
    bool isFloat(std::string& str) const;

class UnexpectedLexemException: public std::exception {
public:
    const char *what() const noexcept;
};
class MissedWhitespaceException : public std::exception {
public:
    const char *what() const noexcept;
};
class UnknownOperandTypeException : public std::exception {
public:
    const char *what() const noexcept;
};
class UnexpectedNumericalValueSybolException : public  std::exception {
public:
    const char *what() const noexcept;
};

class MissedBracketsException: public std::exception {
public:
    const char *what() const noexcept;
};
class MissedOperandValueException: public std::exception {
public:
    const char *what() const noexcept;
};
};


#endif //ABSTRACT_VM_LEXER_H
