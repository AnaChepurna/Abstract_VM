//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Lexer.h"

std::string const pattern[11] = {"push", "pop", "dump", "assert", "add",
                                "sub", "mul", "div", "mod", "print", "exit"};
std::string const pattern_operands[5] = {"int8", "int16", "int32", "float", "double"};

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

Lexer::Lexer(Lexer const &src) {

}

Lexer &Lexer::operator=(Lexer const &src) {
    return *this;
}

bool Lexer::isEnd(std::string str) {
    if (str == ";;")
        return true;
    return false;
}

Token *Lexer::getToken(std::string str) {
    if (isComment(str))
        return nullptr;
    for (int i = 0; i < 11; i++)
    {
        if (str.compare(0, pattern[i].size(), pattern[i]) == 0)
        {
            str = str.substr(pattern[i].size());
            if (str != "")
                throw MissedWhitespaceException();
            switch (i) {
                case 0 :
                    return new Token(Token::PUSH);
                case 1 :
                    return new Token(Token::POP);
                case 2 :
                    return new Token(Token::DUMP);
                case 3 :
                    return new Token(Token::ASSERT);
                case 4 :
                    return new Token(Token::ADD);
                case 5 :
                    return new Token(Token::SUB);
                case 6 :
                    return new Token(Token::MUL);
                case 7 :
                    return new Token(Token::DIV);
                case 8 :
                    return new Token(Token::MOD);
                case 9 :
                    return new Token(Token::PRINT);
                case 10 :
                    return new Token(Token::EXIT);
            }
            break;
        }
    }
    throw UnexpectedLexemException();
}

bool Lexer::isComment(std::string str) {
    if (str.compare(0, 1, ";") == 0)
        return true;
    return false;
}

eOperandType Lexer::getOperandType(std::string &str) {
    for(int i = 0; i < 5; i++) {
        if (str.compare(0, pattern_operands[i].size(), pattern_operands[i]) == 0)
        {
            str = str.substr(pattern_operands[i].size());
            return static_cast<eOperandType>(i);
        }
    }
    throw Lexer::UnexpectedLexemException();
}

