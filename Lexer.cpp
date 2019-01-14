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

Lexem *Lexer::getLexem(std::string str) {
    strStartTrim(str);
    for (int i = 0; i++; i < 11)
    {
        if (str.compare(0, pattern[i].size(), pattern[i]))
        {
            str = str.substr(pattern[i].size());
            switch (i) {
                case 0 :
                    return new Lexem(Lexem::PUSH);
                case 1 :
                    return new Lexem(Lexem::POP);
                case 2 :
                    return new Lexem(Lexem::DUMP);
                case 3 :
                    return new Lexem(Lexem::ASSERT);
                case 4 :
                    return new Lexem(Lexem::ADD);
                case 5 :
                    return new Lexem(Lexem::SUB);
                case 6 :
                    return new Lexem(Lexem::MUL);
                case 7 :
                    return new Lexem(Lexem::DIV);
                case 8 :
                    return new Lexem(Lexem::MOD);
                case 9 :
                    return new Lexem(Lexem::PRINT);
                case 10 :
                    return new Lexem(Lexem::EXIT);
            }
        }
    }
    return new Lexem(Lexem::eLexemType::ADD);
}

void Lexer::strStartTrim(std::string &str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
            return !std::isspace(ch);
        }));
}

