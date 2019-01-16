//
// Created by Anastasia CHEPURNA on 2019-01-16.
//

#include "OperandFactory.h"

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*_functions.at(type))(value);
}

OperandFactory::OperandFactory() {
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
    return new Operand<int8_t>(Int8, value);
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
    return new Operand<int16_t>(Int16, value);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
    return new Operand<int32_t>(Int32, value);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
    return new Operand<float>(Float, value);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
    return new Operand<double>(Double, value);
}

OperandFactory::~OperandFactory() {
}

OperandFactory::OperandFactory(OperandFactory const &rhs) {
}

OperandFactory &OperandFactory::operator=(OperandFactory const &rhs) {
    return *this;
}
