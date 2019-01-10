//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    std::cout << "create\n";
    values.push_front(new Operand<double>(Double, "1.1"));
    values.push_front(new Operand<int8_t>(Int8, "2"));
    values.push_front(new Operand<double>(Double, "3.3"));
    values.push_front(new Operand<double>(Double, "4.4"));
    values.push_front(new Operand<double>(Double, "5.5"));
    values.push_front(new Operand<int8_t>(Int8, "3"));
    values.push_front(new Operand<int8_t>(Int8, "2"));
    dump();
    div();
    dump();
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


VirtualMachine::~VirtualMachine() = default;






