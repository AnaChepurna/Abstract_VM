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
#include <utility>
#include "incl/Lexer.h"
#include "incl/OperandFactory.h"
#include <map>


class Parser {
private:
    Lexer *_lexer;
    std::string _filename;
    std::map<int, Token *>_code = {};
    std::map<int, std::string>_errors = {};

    bool parseCode(std::string code, int i, bool errorIgnore);
    bool createToken(std::string, Token **);
    void checkToken(Token const *);
    void formatWhitespaces(std::string &);
    IOperand const * createOperand(std::string string);
    bool hasExit();
    bool hasCode();

public:
    Parser();
    ~Parser();
    Parser(Parser const& src);
    Parser &operator=(Parser const &src);
    std::map<int, Token *> getCode(bool errorIgnore);
    void setFilename(std::string const &str);
    std::string const& getFilename() const;

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
class BrokenFileException : public std::exception {
public:
    const char *what() const throw();
};
class NoRecognizedCodeException : public std::exception {
public:
    const char *what() const throw();
};
};


#endif //ABSTRACT_VM_PARSER_H
