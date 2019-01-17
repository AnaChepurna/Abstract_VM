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
    IOperand const*own = values.front();
    if (token->getValue()->getType() != own->getType())
        std::cout << "not equal types\n";
    else if (stod(token->getValue()->toString()) != stod(own->toString()))
        std::cout << "not equal values\n";
}

void VirtualMachine::add(Token const *){
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*first + *second);
}

void VirtualMachine::sub(Token const *) {
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second - *first);
}

void VirtualMachine::mul(Token const *) {
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*first * *second);
}

void VirtualMachine::div(Token const *) {
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second / *first);
}

void VirtualMachine::mod(Token const *) {
    IOperand const *first = values.front();
    values.pop_front();
    IOperand const *second = values.front();
    values.pop_front();
    values.push_front(*second % *first);
}

void VirtualMachine::print(Token const *) {
    std::cout << "Print\n";
}

void VirtualMachine::exit(Token const *) {
    std::cout << "exit\n";
}


VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run() {
    code = parser.getCode();
    std::for_each(code.begin(), code.end(), [this](Token const *token) {
        (this->*_functions.at(token->getType()))(token);
    });
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






