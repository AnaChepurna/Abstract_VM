//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    _ifstream.copyfmt(std::cin);
}

VirtualMachine::VirtualMachine(std::string filename) {
    _ifstream.open(filename);
}

VirtualMachine::VirtualMachine(VirtualMachine const &src) {
    *this = src;
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &src) {
    _ifstream.copyfmt(src._ifstream);
    return *this;
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run() {
    read();
}

void VirtualMachine::read() {
    std::string str;
    if (_ifstream.is_open())
    {
        while(42)
        {
            getline(_ifstream, str);
            if (str == "" || )
        }
        _ifstream.close();
    }
}




