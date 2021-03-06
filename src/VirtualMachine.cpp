//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    parser = new Parser();
}

VirtualMachine::VirtualMachine(VirtualMachine const &src) {
    *this = src;
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &src) {
    this->values.clear();
    std::for_each(src.values.begin(), src.values.end(), [this] (IOperand const *o) {
        this->values.push_back(OperandFactory::getFactory()->createOperand(o->getType(), o->toString()));
    });
    this->code.clear();
    std::for_each(src.code.begin(), src.code.end(), [this] (std::pair<int, Token *> p) {
        int i = p.first;
        Token *token = new Token(p.second->getType());
        if (p.second->getValue() != nullptr)
            token->setOperand(OperandFactory::getFactory()->createOperand(
                    p.second->getValue()->getType(), p.second->getValue()->toString()));
        this->code.insert(code.end(), std::make_pair(i, token));
    });
    return *this;
}

void VirtualMachine::push(Token *token) {
    values.push_front(token->getValue());
}

void VirtualMachine::pop(Token *) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    values.pop_front();
}

void VirtualMachine::dump(Token *) {
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        std::cout << o->toString() << std::endl;
    });
}

void VirtualMachine::assert(Token *token)  {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    IOperand const*own = values.front();
    if (token->getValue()->getType() != own->getType())
        throw Error::NotAssertTypeException();
    else if (stod(token->getValue()->toString()) != stod(own->toString()))
        throw Error::NotAssertValueException();
}

void VirtualMachine::add(Token *token){
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw Error::LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    IOperand const*res = *second + *first;
    token->setOperand(res);
    values.push_front(res);
}

void VirtualMachine::sub(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw Error::LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    IOperand const*res = *second - *first;
    token->setOperand(res);
    values.push_front(res);
}

void VirtualMachine::mul(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw Error::LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    IOperand const*res = *second * *first;
    token->setOperand(res);
    values.push_front(res);
}

void VirtualMachine::div(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw Error::LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    if (stod(first->toString()) == 0)
        throw Error::DevisionByZeroException();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    IOperand const*res = *second / *first;
    token->setOperand(res);
    values.push_front(res);
}

void VirtualMachine::mod(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw Error::LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    if (stod(first->toString()) == 0)
        throw Error::DevisionByZeroException();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    IOperand const*res = *second % *first;
    token->setOperand(res);
    values.push_front(res);
}

void VirtualMachine::print(Token *) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    IOperand const *operand = values.front();
    if (operand->getType() != Int8)
        throw Error::NotAssertTypeException();
    auto c = static_cast<char>(std::stoi(operand->toString()));
    std::cout << c << std::endl;
}

void VirtualMachine::exit(Token *) {
}

VirtualMachine::~VirtualMachine() {
    values.clear();
    std::for_each(code.begin(), code.end(), [] (std::pair<int, Token *> p) {
        if (p.second != nullptr)
            delete(p.second);
    });
    code.clear();
    _functions.clear();
    delete(parser);
}

void VirtualMachine::run() {
        try {
            code = parser->getCode(errorIgnore);
        }
        catch (std::exception &e) {
            std::cout << "Error : " << e.what() << std::endl;
        }
        bool *error = new bool(false);
        std::for_each(code.begin(), code.end(), [this, error](std::pair<int , Token *> pair) {
            try {
                if (!*error && pair.second != nullptr)
                    (this->*_functions.at(pair.second->getType()))(pair.second);
            } catch (std::exception &e) {
                std::cout << "\x1B[0mError : line " << pair.first << " : \"" << pair.second->getTypeString() << "\" : " << e.what() << std::endl;
                if (!errorIgnore)
                    *error = true;
            }
        });
        delete(error);
}

void VirtualMachine::dump_type(Token *) {
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        switch (o->getType()) {
            case eOperandType::Int8 :
                std::cout << "int8(";
                break;
            case eOperandType::Int16 :
                std::cout << "int16(";
                break;
            case eOperandType::Int32 :
                std::cout << "int32(";
                break;
            case eOperandType::Float :
                std::cout << "float(";
                break;
            case eOperandType::Double :
                std::cout << "double(";
                break;
        }
        std::cout << o->toString() << ")" << std::endl;
    });
}

void VirtualMachine::setFlag(std::string const &flag) {
    if (flag == "-errorIgnore")
        errorIgnore = true;
    else if (parser->getFilename().empty())
        parser->setFilename(flag);
    else
        throw std::exception();
}

void VirtualMachine::color(Token *) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    IOperand const *operand = values.front();
    if (operand->getType() != Int8)
        throw Error::NotAssertTypeException();
    int c = std::stoi(operand->toString());
    if (c == 0 || (c > 30 && c < 38))
        std::cout << "\x1B[" <<  c << "m";
}

void VirtualMachine::abs(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    IOperand const *operand = values.front();
    auto value = static_cast<long double>(stod(operand->toString()));
    if (value < 0)
    {
        values.pop_front();
        value = -value;
        std::stringstream str;
        str << value;
        IOperand const *res = OperandFactory::getFactory()->createOperand(operand->getType(), str.str());
        token->setOperand(res);
        values.push_front(res);
    }
}

void VirtualMachine::up(Token *token) {
    if (values.empty())
        throw Error::OperationOnEmptyStackException();
    IOperand const *operand = values.front();
    if (operand->getType() == Double)
        throw Error::LimitOverflowException();
    values.pop_front();
    IOperand const *res = OperandFactory::getFactory()->createOperand(static_cast<eOperandType>(operand->getType() + 1), operand->toString());
    token->setOperand(res);
    values.push_front(res);
}

