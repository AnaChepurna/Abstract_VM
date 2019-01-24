//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    parser = Parser();
}

VirtualMachine::VirtualMachine(VirtualMachine const &src) {
    *this = src;
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &src) {
    return *this;
}

void VirtualMachine::push(Token const *token) {
    values.push_front(token->getValue());
}

void VirtualMachine::pop(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    values.pop_front();
}

void VirtualMachine::dump(Token const *) {
    std::cout << "dump >>>>>" << std::endl;
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        std::cout << o->toString() << std::endl;
    });
    std::cout << "<<<<<<<<<<" << std::endl;
}

void VirtualMachine::assert(Token const *token)  {
    if (values.empty())
        throw OperationOnEmptyStackException();
    IOperand const*own = values.front();
    if (token->getValue()->getType() != own->getType())
        throw NotAssertTypeException();
    else if (stod(token->getValue()->toString()) != stod(own->toString()))
        throw NotAssertValueException();
}

void VirtualMachine::add(Token const *){
    if (values.empty())
        throw OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*first + *second);
}

void VirtualMachine::sub(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second - *first);
}

void VirtualMachine::mul(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*first * *second);
}

void VirtualMachine::div(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    if (stod(first->toString()) == 0)
        throw DevisionByZeroException();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second / *first);
}

void VirtualMachine::mod(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    else if (values.size() < 2)
        throw LessThanTwoValuesInStackException();
    IOperand const *first = values.front();
    if (stod(first->toString()) == 0)
        throw DevisionByZeroException();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second % *first);
}

void VirtualMachine::print(Token const *) {
    if (values.empty())
        throw OperationOnEmptyStackException();
    IOperand const *operand = values.front();
    if (operand->getType() != Int8)
        throw NotAssertTypeException();
    auto c = static_cast<char>(std::stoi(operand->toString()));
    std::cout << c << std::endl;
}

void VirtualMachine::exit(Token const *) {
}


VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run() {
        code = parser.getCode();
        bool *error = new bool(false);
        std::for_each(code.begin(), code.end(), [this, error](std::pair<int , Token const *> pair) {
            try {
                if (!*error && pair.second != nullptr)
                    (this->*_functions.at(pair.second->getType()))(pair.second);
            } catch (std::exception &e) {
                std::cout << "Error : line " << pair.first << " : \"" << pair.second->getTypeString() << "\" : " << e.what() << std::endl;
                *error = true;
            }
        });
        while(42) {}
}

void VirtualMachine::dump_type(Token const *) {
    std::cout << "dump type >" << std::endl;
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        switch (o->getType()) {
            case eOperandType::Int8 :
                std::cout << "int8 ";
                break;
            case eOperandType::Int16 :
                std::cout << "int16 ";
                break;
            case eOperandType::Int32 :
                std::cout << "int32 ";
                break;
            case eOperandType::Float :
                std::cout << "float ";
                break;
            case eOperandType::Double :
                std::cout << "double ";
                break;
        }
        std::cout << o->toString() << std::endl;
    });
    std::cout << "<<<<<<<<<<" << std::endl;
}


const char *VirtualMachine::NotAssertTypeException::what() const noexcept {
    return "Operand in stack has wrong type";
}

const char *VirtualMachine::NotAssertValueException::what() const noexcept {
    return "Operand in stack has different value";
}

const char *VirtualMachine::DevisionByZeroException::what() const noexcept {
    return "Division/modulo by zero";
}

const char *VirtualMachine::OperationOnEmptyStackException::what() const noexcept {
    return "Operation on empty stack";
}

const char *VirtualMachine::LessThanTwoValuesInStackException::what() const noexcept {
    return "Arithmetic instruction needs at least two operands in stack";
}
