//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_VIRTUALMACHINE_H
#define ABSTRACT_VM_VIRTUALMACHINE_H

#include <iostream>
#include <fstream>

class VirtualMachine {
private:
    std::ifstream _ifstream;
    void read();

public :
    VirtualMachine();
    explicit VirtualMachine(std::string filename);
    VirtualMachine(VirtualMachine const& src);
    VirtualMachine &operator=(VirtualMachine const &src);
    ~VirtualMachine();
    void run();
};


#endif //ABSTRACT_VM_VIRTUALMACHINE_H
