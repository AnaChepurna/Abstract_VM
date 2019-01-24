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
    std::vector<std::pair<int, Token const*>>code;
    Parser parser;

public :
    VirtualMachine();
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();
    void run();

class NotAssertTypeException: public std::exception {
public:
    const char *what() const noexcept;
};
class NotAssertValueException: public std::exception {
public:
    const char *what() const noexcept;
};
class DevisionByZeroException: public std::exception {
public:
    const char *what() const noexcept;
};
class OperationOnEmptyStackException: public std::exception {
public:
    const char *what() const noexcept;
};
class LessThanTwoValuesInStackException: public std::exception {
public:
    const char *what() const noexcept;
};

private:
    void push(Token const *);
    void pop(Token const *);
    void dump(Token const *);
    void assert(Token const *);
    void add(Token const *);
    void sub(Token const *);
    void mul(Token const *);
    void div(Token const *);
    void mod(Token const *);
    void print(Token const *);
    void exit(Token const *);
    void dump_type(Token const *);

    std::vector<void (VirtualMachine::*)(Token const *)> _functions = {
            &VirtualMachine::push,
            &VirtualMachine::pop,
            &VirtualMachine::dump,
            &VirtualMachine::assert,
            &VirtualMachine::add,
            &VirtualMachine::sub,
            &VirtualMachine::mul,
            &VirtualMachine::div,
            &VirtualMachine::mod,
            &VirtualMachine::print,
            &VirtualMachine::exit,
            &VirtualMachine::dump_type
    };
};


#endif //ABSTRACT_VM_VIRTUALMACHINE_H
