//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_VIRTUALMACHINE_H
#define ABSTRACT_VM_VIRTUALMACHINE_H

#include <iostream>
#include <fstream>
#include <list>
#include "IOperand.h"
#include "Operand.h"
#include "Lexem.h"

class VirtualMachine {
private:
    std::list<IOperand const *>values;
    std::list<Lexem const*>code;


public :
    VirtualMachine();
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();

private:
    void push(IOperand const *value);
    void pop();
    void dump();
    void assert(IOperand const *value);
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
    void exit();
};


#endif //ABSTRACT_VM_VIRTUALMACHINE_H
