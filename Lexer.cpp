//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Lexer.h"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

Lexer::Lexer(Lexer const &src) {

}

Lexer &Lexer::operator=(Lexer const &src) = default;

bool Lexer::isEnd(std::string str) {
    return  (str == ";;");
}

Token *Lexer::getToken(std::string str) {
    if (isComment(str))
        return nullptr;
    for (int i = 0; i < pattern.size(); i++)
    {
        if (str == pattern[i])
//        if (str.compare(0, pattern[i].size(), pattern[i]) == 0)
        {
//            str = str.substr(pattern[i].size());
//            if (str != "")
//                throw MissedWhitespaceException();
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
    throw UnexpectedLexemException();
}

bool Lexer::isComment(std::string str) {
    return  (str.compare(0, 1, ";") == 0);
}

eOperandType Lexer::getOperandType(std::string &str) {
    for(int i = 0; i < pattern_operands.size(); i++) {
        if (str.compare(0, pattern_operands[i].size(), pattern_operands[i]) == 0)
        {
            str = str.substr(pattern_operands[i].size());
            return static_cast<eOperandType>(i);
        }
    }
    throw Lexer::UnknownOperandTypeException();
}

bool Lexer::isInt(std::string &str) {
    if (std::regex_match(str, std::regex(R"(^(\([-]?[0-9]+\))$)"))) {
        str = str.substr(1, str.size() - 2);
        return true;
    }
    return false;
}

bool Lexer::isFloat(std::string &str) {
    if (std::regex_match(str, std::regex(R"(^(\([-]?[0-9]+\.?[0-9]+\))$)"))) {
        str = str.substr(1, str.size() - 2);
        return true;
    } else return false;
}

