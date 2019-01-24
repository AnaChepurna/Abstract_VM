//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Lexer.h"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

Lexer::Lexer(Lexer const &src) {
    *this = src;
}

Lexer &Lexer::operator=(Lexer const &src){
    return *this;
}

bool Lexer::isEnd(std::string str) const {
    return  (str == ";;");
}

Token *Lexer::getToken(std::string str) const {
    if (str.empty() || isComment(str))
        return nullptr;
    for (int i = 0; i < Token::pattern.size(); i++)
    {
        if (str == Token::pattern[i])
        {
            switch (i) {
                case Token::PUSH :
                    return new Token(Token::PUSH);
                case Token::POP :
                    return new Token(Token::POP);
                case Token::DUMP :
                    return new Token(Token::DUMP);
                case Token::ASSERT :
                    return new Token(Token::ASSERT);
                case Token::ADD :
                    return new Token(Token::ADD);
                case Token::SUB :
                    return new Token(Token::SUB);
                case Token::MUL :
                    return new Token(Token::MUL);
                case Token::DIV :
                    return new Token(Token::DIV);
                case Token::MOD :
                    return new Token(Token::MOD);
                case Token::PRINT :
                    return new Token(Token::PRINT);
                case Token::EXIT :
                    return new Token(Token::EXIT);
                case Token::DUMP_TYPE :
                    return new Token(Token::DUMP_TYPE);
            }
            break;
        }
    }
    for (int i = 0; i < Token::pattern.size(); i++)
        if (str.compare(0, Token::pattern[i].size(), Token::pattern[i]) == 0) {
            str = str.substr(Token::pattern[i].size());
            if (!str.empty())
                throw MissedWhitespaceException();
        }
    throw UnexpectedLexemException();
}

bool Lexer::isComment(std::string str) const {
    return  (str.compare(0, 1, ";") == 0);
}

eOperandType Lexer::getOperandType(std::string &str) const {
    for(int i = 0; i < OperandFactory::pattern.size(); i++) {
        if (str.compare(0, OperandFactory::pattern[i].size(), OperandFactory::pattern[i]) == 0)
        {
            str = str.substr(OperandFactory::pattern[i].size());
            return static_cast<eOperandType>(i);
        }
    }
    throw Lexer::UnknownOperandTypeException();
}

bool Lexer::isInt(std::string &str) const {
    return (std::regex_match(str, std::regex(R"(^[-]?[0-9]+$)")));
}

bool Lexer::isFloat(std::string &str) const {
    if (isInt(str))
        return true;
    return (std::regex_match(str, std::regex(R"(^[-]?[0-9]+\.[0-9]+$)")));
}

bool Lexer::hasBrackets(std::string &str) const {
    if (std::regex_match(str, std::regex(R"(^\(.+\)$)"))) {
        str = str.substr(1, str.size() - 2);
        return true;
    }
    throw Lexer::MissedBracketsException();
}

const char *Lexer::UnexpectedLexemException::what() const throw() {
    return "Unknown instruction";
}

const char *Lexer::MissedWhitespaceException::what() const throw() {
    return "Missed whitespace after instruction";
}

const char *Lexer::UnknownOperandTypeException::what() const throw() {
    return "Unknown operand type";
}

const char *Lexer::UnexpectedNumericalValueSybolException::what() const throw() {
    return "Unexpected symbol in numerical value";
}

const char *Lexer::MissedBracketsException::what() const noexcept {
    return "Missed brackets in operand declaration";
}
