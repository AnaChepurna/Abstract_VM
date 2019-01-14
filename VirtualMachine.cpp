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

void VirtualMachine::push(IOperand const* value) {
    values.push_front(value);
}

void VirtualMachine::pop() {
//    IOperand const *own = values.front();
    values.pop_front();
//    delete own;
}

void VirtualMachine::dump() {
    std::cout << "dump >>>>>" << std::endl;
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        std::cout << o->toString() << std::endl;
    });
    std::cout << "<<<<<<<<<<" << std::endl;
}

void VirtualMachine::assert(IOperand const *value) {
    IOperand const*own = values.front();
    std::cout << "WHAT???\n";
}

void VirtualMachine::add() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*first + *second);
}

void VirtualMachine::sub() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*second - *first);
}

void VirtualMachine::mul() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*first * *second);
}

void VirtualMachine::div() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*second / *first);
}

void VirtualMachine::mod() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*second % *first);
}

void VirtualMachine::print() {
    std::cout << "Print\n";
}

void VirtualMachine::exit() {
    std::cout << "exit\n";
}


VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run() {
    code = parser.getCode();
}






