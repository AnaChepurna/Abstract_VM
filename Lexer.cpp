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

Lexer &Lexer::operator=(Lexer const &src) {
    return *this;
}

bool Lexer::isEnd(std::string str) const{
    if (str.compare(0, 2, ";;") == 0)
        return true;
    return false;
}
