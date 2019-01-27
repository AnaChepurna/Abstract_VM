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
#include <map>


class VirtualMachine {
private:
    std::list<IOperand const *>values;
    std::vector<std::pair<int, Token *>>code;
    Parser *parser;
    bool errorIgnore = false;

public :
    VirtualMachine();
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();
    void run();
    void setFlag(std::string const& flag);

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
    void push(Token *);
    void pop(Token *);
    void dump(Token *);
    void assert(Token *);
    void add(Token  *);
    void sub(Token *);
    void mul(Token *);
    void div(Token *);
    void mod(Token *);
    void print(Token *);
    void exit(Token *);
    void dump_type(Token *);

    std::vector<void (VirtualMachine::*)(Token *)> _functions = {
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
