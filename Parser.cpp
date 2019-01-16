//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "Parser.h"

Parser::Parser() {
    _lexer = Lexer();
}


Parser::~Parser() {
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser &Parser::operator=(Parser const &src) {
    this->_filename = src._filename;
    this->_lexer = src._lexer;
    return *this;
}

std::vector<Token const *> Parser::getCode() {
    std::string str;
    int num = 0;
    if (_filename == "") {
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
    std::for_each(_errors.begin(), _errors.end(), [] (std::string str) {
        std::cout << str << "\n";
    });
    return (_code);
}

bool Parser::parseCode(std::string str, int i) {
    if (_lexer.isEnd(str))
        return true;
    std::stringstream stream(str);
    std::string substr;
    Token *token = nullptr;

    try {
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
    return false;
}

bool Parser::createToken(std::string substr, Token **token) {
    if (*token == nullptr) {
        *token = _lexer.getToken(substr);
        if (*token == nullptr)
            return true;
    }
    else if ((*token)->getValue() == nullptr) {
//            token->setOperand(new Operand<double>(Double, 22));
        std::cout << "needs operand!\n";
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
    if (!_code.empty() && _code.back()->getType() == Token::EXIT)
        throw Parser::TokenAfterExitException();
    if (token->getType() == Token::PUSH || token->getType() == Token::ASSERT) {
        if (token->getValue() == nullptr)
            throw Parser::ExpectedValueAfterException();
    }
    else
        if (token->getValue() != nullptr)
            throw Parser::UnexpectedTokenException();
}

