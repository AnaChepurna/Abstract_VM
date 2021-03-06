//
// Created by Anastasia CHEPURNA on 2019-01-16.
//

#ifndef ABSTRACT_VM_OPERANDFACTORY_H
#define ABSTRACT_VM_OPERANDFACTORY_H

#include "IOperand.h"
#include <vector>
#include <limits>
#include "float.h"
#include "Error.h"

class OperandFactory {
public:
    static OperandFactory *getFactory();
    ~OperandFactory();
    IOperand const *createOperand(eOperandType type, std::string const &value) const;
private:
    OperandFactory();
    IOperand const *createInt8(std::string const &value) const;
    IOperand const *createInt16(std::string const &value) const;
    IOperand const *createInt32(std::string const &value) const;
    IOperand const *createFloat(std::string const &value) const;
    IOperand const *createDouble(std::string const &value) const;

    std::vector<IOperand const *(OperandFactory::*)(std::string const &value) const> _functions = {
            &OperandFactory::createInt8,
            &OperandFactory::createInt16,
            &OperandFactory::createInt32,
            &OperandFactory::createFloat,
            &OperandFactory::createDouble
    };

    static OperandFactory *_factory;
public:
    static std::vector<std::string> const pattern;
};


#endif //ABSTRACT_VM_OPERANDFACTORY_H
