//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Lexer.h"

std::string const pattern[11] = {"push", "pop", "dump", "assert", "add",
                                "sub", "mul", "div", "mod", "print", "exit"};

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
    strStartTrim(str);
    if (str.compare(0, 2, ";;") == 0)
        return true;
    return false;
}

Token *Lexer::getLexem(std::string str) {
//    strStartTrim(str);
    for (int i = 0; i < 11; i++)
    {
        if (str.compare(0, pattern[i].size(), pattern[i]) == 0)
        {
            str = str.substr(pattern[i].size());
            if (str != "")
                std::cout << "no whitespace after " << pattern[i] << "\n";
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
        if (isComment(str))
            return nullptr;
    }
    return nullptr;
}

void Lexer::strStartTrim(std::string &str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
            return !std::isspace(ch);
        }));
}

bool Lexer::isComment(std::string str) {
    strStartTrim(str);
    if (str.compare(0, 1, ";") == 0)
        return true;
    return false;
}

