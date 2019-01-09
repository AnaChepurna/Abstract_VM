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

class VirtualMachine {
private:
    std::list<IOperand const *>values;
    std::list<std::string>code;


public :
    VirtualMachine();
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();
};


#endif //ABSTRACT_VM_VIRTUALMACHINE_H
