//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_PARSER_H
#define ABSTRACT_VM_PARSER_H

#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Lexer.h"
#include "OperandFactory.h"


class Parser {
private:
    Lexer  _lexer;
    OperandFactory _factory;
    std::string  _filename;
    std::vector<Token const *>_code = {};
    std::vector<std::string>_errors = {};

    bool parseCode(std::string code, int i);
    bool createToken(std::string, Token **);
    void checkToken(Token const *);
    void addErrorMessage(int i, std::string message);
    void formatWhitespaces(std::string &);
    IOperand const * createOperand(std::string string);

public:
    Parser();
    ~Parser();
    Parser(Parser const& src);
    Parser &operator=(Parser const &src);

    std::vector<Token const *> getCode();

class NoExitException : public std::exception {
public:
    const char *what() const throw();
};
class TokenAfterExitException : public std::exception {
public:
    const char *what() const throw();
};
class ExpectedValueAfterException : public std::exception {
public:
    const char *what() const throw();
};
class UnexpectedTokenException : public std::exception {
public:
    const char *what() const throw();
};
};


#endif //ABSTRACT_VM_PARSER_H
