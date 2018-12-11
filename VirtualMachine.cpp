//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(): _filename("") {
}

VirtualMachine::VirtualMachine(std::string filename) {
    _filename = filename;
}

VirtualMachine::VirtualMachine(VirtualMachine const &src) {
    *this = src;
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &src) {
    _filename = src._filename;
    return *this;
}

VirtualMachine::~VirtualMachine() = default;

void VirtualMachine::run() {
    _read();
}

void VirtualMachine::_readFromFile() {
    std::string str;
    std::ifstream ifs(_filename);

    if (!ifs.is_open())
        return ;
    while (42)
    {
        getline(ifs, str);
        std::cout << str << std::endl;
        if (ifs.eof())
            return;
    }
}

void VirtualMachine::_readFromConsole() {
    std::string str;

    while (42)
    {
        getline(std::cin, str);
        std::cout << str << std::endl;
    }
}

void VirtualMachine::_read() {

    if (_filename.empty())
        _readFromConsole();
    else
        _readFromFile();
}




