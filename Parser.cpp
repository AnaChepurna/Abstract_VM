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

std::vector<std::pair<int, Token const *>> Parser::getCode() {
    std::string str;
    int num = 0;
    if (_filename.empty()) {
        while (std::cin.good()) {
            num++;
            std::getline(std::cin, str);
            if (parseCode(str, num))
                break;
        }
    }
    else {
        std::fstream i;
        i.open(_filename);
        if (!i.good())
            throw Parser::BrokenFileException();
        while (std::getline(i, str)) {
            num++;
            if (parseCode(str, num))
                break;
        }
        i.close();
    }
    if (_code.empty() || !hasCode())
        throw NoRecognizedCodeException();
    if (!_errors.empty()) {
        std::for_each(_errors.begin(), _errors.end(), [](std::pair<int, std::string> pair) {
            std::cout << "Error : line " << pair.first << " : " << pair.second << std::endl;
        });
        exit(0);
    }
    return (_code);
}

bool Parser::parseCode(std::string str, int i) {
    formatWhitespaces(str);
    Token *token = nullptr;
    try {
        if (_lexer->isEnd(str)) {
            if (!hasExit())
                throw Parser::NoExitException();
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
    catch (Parser::NoExitException& e) {
        _errors.insert(_errors.end(), std::make_pair(i, e.what()));
        if (token != nullptr)
            delete(token);
        return true;
    }
    catch (std::exception& e) {
        _errors.insert(_errors.end(), std::make_pair(i, "\"" + str + "\" : " + e.what()));
        if (token != nullptr)
            delete(token);
    }
    return false;
}

bool Parser::createToken(std::string substr, Token **const token) {
    if (substr.empty())
        return false;
    if (hasExit())
        throw Parser::TokenAfterExitException();
    unsigned long com = substr.find(';');
    if (com < UINT64_MAX)
        substr = substr.substr(0, com);
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
        throw Parser::UnexpectedTokenException();
    return com < UINT64_MAX;
}

void Parser::checkToken(Token const *token) {
    if (token->getType() == Token::PUSH || token->getType() == Token::ASSERT) {
        if (token->getValue() == nullptr) {
            throw Parser::ExpectedValueAfterException();
        }
    }
    else
        if (token->getValue() != nullptr) {
            throw Parser::UnexpectedTokenException();
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
        throw Lexer::UnexpectedNumericalValueSybolException();
}

bool Parser::hasExit() {
    for (int i = 0; i < static_cast<int>(_code.size()); i++) {
        if (_code.at(i).second != nullptr && _code.at(i).second->getType() == Token::EXIT)
            return true;
    }
    return false;
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

const char *Parser::NoExitException::what() const noexcept {
    return "No exit instruction in the end of program";
}

const char *Parser::TokenAfterExitException::what() const noexcept {
    return "Token after exit instruction";
}

const char *Parser::ExpectedValueAfterException::what() const noexcept {
    return "Expecting operand after instruction";
}

const char *Parser::UnexpectedTokenException::what() const noexcept {
    return "Unexpected token after instruction";
}

const char *Parser::BrokenFileException::what() const noexcept {
    return "Cannot open input file : Check the filename or access rights";
}

const char *Parser::NoRecognizedCodeException::what() const noexcept {
    return "Cannot recognize any token : Check input data format";
}

