//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    values.push_front(new Operand<double>(Double, "1.1"));
    values.push_front(new Operand<double>(Double, "2.2"));
    values.push_front(new Operand<double>(Double, "3.3"));
    values.push_front(new Operand<double>(Double, "4.4"));
    values.push_front(new Operand<double>(Double, "5.5"));
    add();
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
    values.pop_front();
}

void VirtualMachine::dump() {
    std::for_each(values.begin(), values.end(), [](IOperand const* o){
        std::cout << o->toString() << std::endl;
    });
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
    values.push_front(*first - *second);
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
    values.push_front(*first / *second);
}

void VirtualMachine::mod() {
    IOperand const *first = values.front();
    pop();
    IOperand const *second = values.front();
    pop();
    values.push_front(*first % *second);
}

void VirtualMachine::print() {
    std::cout << "Print\n";
}

void VirtualMachine::exit() {
    std::cout << "exit\n";
}


VirtualMachine::~VirtualMachine() = default;






