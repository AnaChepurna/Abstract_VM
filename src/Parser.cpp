//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
    _lexer = new Lexer();
}


Parser::~Parser() {
    _code.clear();
    _errors.clear();
    delete(_lexer);
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    return *this;
}

std::map<int, Token *> Parser::getCode(bool errorIgnore) {
    std::string str;
    int num = 0;
    if (_filename.empty()) {
        while (std::cin.good()) {
            num++;
            std::getline(std::cin, str);
            if (parseCode(str, num, errorIgnore))
                break;
        }
    }
    else {
        std::fstream i;
        i.open(_filename);
        if (!i.good())
            throw Error::BrokenFileException();
        while (std::getline(i, str)) {
            num++;
            if (parseCode(str, num, errorIgnore))
                break;
        }
        i.close();
    }
    try {
        if (!hasExit())
            throw Error::NoExitException();
    } catch (std::exception &e) {
        _errors.insert(_errors.end(), std::make_pair(static_cast<int>(_code.size()) + 1, e.what()));
    }
    if (_code.empty() || !hasCode())
        throw Error::NoRecognizedCodeException();
    if (!_errors.empty()) {
        std::for_each(_errors.begin(), _errors.end(), [](std::pair<int, std::string> pair) {
            std::cout << "Error : line " << pair.first << " : " << pair.second << std::endl;
        });
        exit(0);
    }
    return (_code);
}

bool Parser::parseCode(std::string str, int i, bool errorIgnore) {
    formatWhitespaces(str);
    Token *token = nullptr;
    try {
        if (_lexer->isEnd(str)) {
            if (!hasExit())
                throw Error::NoExitException();
            return true;
        }
        std::stringstream stream(str);
        std::string substr;
        while (stream.good()) {
            std::getline(stream, substr, ' ');
            if (createToken(substr, &token))
                break;
        }
        if (token != nullptr)
            checkToken(token);
        _code.insert(_code.end(), std::make_pair(i, token));
    }
    catch (Error::NoExitException& e) {
            _errors.insert(_errors.end(), std::make_pair(i, e.what()));
        if (token != nullptr)
            delete(token);
        return true;
    }
    catch (std::exception& e) {
        if (!errorIgnore)
            _errors.insert(_errors.end(), std::make_pair(i, "\"" + str + "\" : " + e.what()));
        else
            std::cout << "Error : line " << i << " : \"" << str << "\" : " << e.what() << std::endl;
        if (token != nullptr)
            delete(token);
    }
    return false;
}

bool Parser::createToken(std::string substr, Token **const token) {
    unsigned long com = substr.find(';');
    if (com < UINT64_MAX)
        substr = substr.substr(0, com);
    if (substr.empty())
        return true;
    if (hasExit())
        throw Error::TokenAfterExitException();
    if (*token == nullptr) {
        *token = _lexer->getToken(substr);
        if (*token == nullptr)
            return true;
    }
    else if ((*token)->getValue() == nullptr) {
        (*token)->setOperand(createOperand(substr));
        if ((*token)->getValue() == nullptr)
            return true;
    }
    else if (!_lexer->isComment(substr))
        throw Error::UnexpectedTokenException();
    return com < UINT64_MAX;
}

void Parser::checkToken(Token const *token) {
    if (token->getType() == Token::PUSH || token->getType() == Token::ASSERT) {
        if (token->getValue() == nullptr) {
            throw Error::ExpectedValueAfterException();
        }
    }
    else
        if (token->getValue() != nullptr) {
            throw Error::UnexpectedTokenException();
        }
}

void Parser::formatWhitespaces(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    std::replace(str.begin(), str.end(), '\t', ' ');
    std::replace(str.begin(), str.end(), '\v', ' ');
    std::replace(str.begin(), str.end(), '\r', ' ');
}

IOperand const* Parser::createOperand(std::string str) {
    if (_lexer->isComment(str))
        return nullptr;
    eOperandType type = _lexer->getOperandType(str);
    _lexer->hasBrackets(str);
    if ((type >= Float && _lexer->isFloat(str)) ||
            (type < Float && _lexer->isInt(str)))
        return OperandFactory::getFactory()->createOperand(type, str);
    else
        throw Error::UnexpectedNumericalValueSybolException();
}

bool Parser::hasExit() {
    bool *ret = new bool(false);
    std::for_each(_code.begin(), _code.end(), [ret] (std::pair<int, Token const *> p){
        if (p.second != nullptr && p.second->getType() == Token::EXIT)
            *ret = true;
    });
    bool r = *ret;
    delete(ret);
    return r;
}

void Parser::setFilename(std::string const &str) {
    _filename = str;
}

bool Parser::hasCode() {
    bool *ret = new bool(false);
    std::for_each(_code.begin(), _code.end(), [ret] (std::pair<int, Token const *> p){
        if (p.second != nullptr)
            *ret = true;
    });
    bool r = *ret;
    delete(ret);
    return r;
}

std::string const &Parser::getFilename() const {
    return _filename;
}

