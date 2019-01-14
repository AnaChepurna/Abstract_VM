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
    Lexem *lexem = nullptr;
    for (int i = 0; i < 11; i++)
    {
        if (str.compare(0, pattern[i].size(), pattern[i]) == 0)
        {
            str = str.substr(pattern[i].size());
            switch (i) {
                case 0 :
                    lexem = new Lexem(Lexem::PUSH);
                    break;
                case 1 :
                    lexem = new Lexem(Lexem::POP);
                    break;
                case 2 :
                    lexem = new Lexem(Lexem::DUMP);
                    break;
                case 3 :
                    lexem = new Lexem(Lexem::ASSERT);
                    break;
                case 4 :
                    lexem = new Lexem(Lexem::ADD);
                    break;
                case 5 :
                    lexem = new Lexem(Lexem::SUB);
                    break;
                case 6 :
                    lexem = new Lexem(Lexem::MUL);
                    break;
                case 7 :
                    lexem = new Lexem(Lexem::DIV);
                    break;
                case 8 :
                    lexem = new Lexem(Lexem::MOD);
                    break;
                case 9 :
                    lexem = new Lexem(Lexem::PRINT);
                    break;
                case 10 :
                    lexem =  new Lexem(Lexem::EXIT);
                    break;
            }
            break;
        }
        if (isComment(str))
            std::cout << "find comment\n";
    }
    return lexem;
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

