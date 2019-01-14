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
#include "Token.h"
#include "Parser.h"


class VirtualMachine {
private:
    std::list<IOperand const *>values;
    std::vector<Token const*>code;
    Parser parser;

public :
    VirtualMachine();
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();
    void run();

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
