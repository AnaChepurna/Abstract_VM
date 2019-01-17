//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
    _lexer = Lexer();
    _factory = OperandFactory();
}


Parser::~Parser() {
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    this->_lexer = src._lexer;
    this->_factory = src._factory;
    return *this;
}

std::vector<Token const *> Parser::getCode() {
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
        while (std::getline(i, str)) {
            num++;
            if (parseCode(str, num))
                break;
        }
        i.close();
    }
    if (!_errors.empty()) {
        std::for_each(_errors.begin(), _errors.end(), [](std::string str) {
            std::cout << str << "\n";
        });
        exit(0);
    }
    return (_code);
}

bool Parser::parseCode(std::string str, int i) {
    formatWhitespaces(str);
    try {
        if (_lexer.isEnd(str)) {
            if (!_code.empty() && _code.back()->getType() != Token::EXIT)
                throw Parser::NoExitException();
            return true;
        }
        std::stringstream stream(str);
        std::string substr;
        Token *token = nullptr;
        while (stream.good()) {
            std::getline(stream, substr, ' ');
            if (createToken(substr, &token))
                break;
        }
        if (token != nullptr) {
            checkToken(token);
            _code.insert(_code.end(), token);
        }
    }
    catch (Lexer::MissedWhitespaceException& e) {
        addErrorMessage(i, e.what());
    }
    catch (Lexer::UnexpectedLexemException& e) {
        addErrorMessage(i, e.what());
    }
    catch (Parser::UnexpectedTokenException& e){
        addErrorMessage(i, e.what());
    }
    catch (Parser::TokenAfterExitException& e) {
        addErrorMessage(i, e.what());
    }
    catch (Parser::ExpectedValueAfterException& e) {
        addErrorMessage(i, e.what());
    }
    catch (Parser::NoExitException& e) {
        addErrorMessage(i, e.what());
        return true;
    }
    catch (Lexer::UnknownOperandTypeException& e) {
        addErrorMessage(i, e.what());
    }
    catch  (Lexer::UnexpectedNumericalValueSybolException& e) {
        addErrorMessage(i, e.what());
    }
    catch (OperandFactory::LimitOverflowException& e) {
        addErrorMessage(i, e.what());
    }
    catch (OperandFactory::LimitUnderflowException& e) {
        addErrorMessage(i, e.what());
    }
    return false;
}

bool Parser::createToken(std::string const substr, Token **const token) {
    if (substr.empty())
        return false;
    if (!_code.empty() && _code.back()->getType() == Token::EXIT)
        throw Parser::TokenAfterExitException();
    if (*token == nullptr) {
        *token = _lexer.getToken(substr);
        if (*token == nullptr)
            return true;
    }
    else if ((*token)->getValue() == nullptr) {
        (*token)->setOperand(createOperand(substr));
        if ((*token)->getValue() == nullptr)
            return true;
    }
    else
        throw Parser::UnexpectedTokenException();
    return false;
}

void Parser::addErrorMessage(int i, std::string message) {
    std::stringstream stream;
    stream << "In line " << i << ": " << message;
    _errors.insert(_errors.end(), stream.str());
}

void Parser::checkToken(Token const *token) {
    if (token->getType() == Token::PUSH || token->getType() == Token::ASSERT) {
        if (token->getValue() == nullptr)
            throw Parser::ExpectedValueAfterException();
    }
    else
        if (token->getValue() != nullptr)
            throw Parser::UnexpectedTokenException();
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
    if (_lexer.isComment(str))
        return nullptr;
    eOperandType type = _lexer.getOperandType(str);
    if ((type >= Float && _lexer.isFloat(str)) ||
            (type < Float && _lexer.isInt(str)))
        return _factory.createOperand(type, str);
    else
        throw Lexer::UnexpectedNumericalValueSybolException();
}

