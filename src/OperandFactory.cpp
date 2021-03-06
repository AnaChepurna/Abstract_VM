//
// Created by Anastasia CHEPURNA on 2019-01-16.
//

#include "OperandFactory.h"
#include "Operand.h"

std::vector<std::string> const OperandFactory::pattern = {"int8", "int16", "int32", "float", "double"};


OperandFactory * OperandFactory::_factory = nullptr;

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*_functions.at(type))(value);
}

OperandFactory::OperandFactory() {
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
    int64_t val;
    try {
        val = static_cast<int64_t >(std::stod(value));
    } catch (std::exception &e) {
        if (value[0] == '-')
            throw Error::LimitUnderflowException();
        else
            throw Error::LimitOverflowException();
    }
    if (val > INT8_MAX)
        throw Error::LimitOverflowException();
    else if (val < INT8_MIN)
        throw  Error::LimitUnderflowException();
    return new Operand<int8_t>(Int8, static_cast<int8_t >(val));
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
    int64_t val;
    try {
        val = static_cast<int64_t >(std::stod(value));
    } catch (std::exception &e) {
        if (value[0] == '-')
            throw Error::LimitUnderflowException();
        else
            throw Error::LimitOverflowException();
    }
    if (val > INT16_MAX)
        throw Error::LimitOverflowException();
    else if (val < INT16_MIN)
        throw  Error::LimitUnderflowException();
    return new Operand<int16_t>(Int16, static_cast<int16_t >(val));
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
    int64_t val;
    try {
        val = static_cast<int64_t >(std::stod(value));
    } catch (std::exception &e) {
        if (value[0] == '-')
            throw Error::LimitUnderflowException();
        else
            throw Error::LimitOverflowException();
    }
    if (val > INT32_MAX)
        throw Error::LimitOverflowException();
    else if (val < INT32_MIN)
        throw  Error::LimitUnderflowException();
    return new Operand<int32_t>(Int32, static_cast<int32_t >(val));
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
    long double val;
    try {
        val = std::stod(value);
    } catch (std::exception &e) {
        if (value[0] == '-')
            throw Error::LimitUnderflowException();
        else
            throw Error::LimitOverflowException();
    }
    if (val > FLT_MAX)
        throw Error::LimitOverflowException();
    else if (val < -FLT_MAX)
        throw  Error::LimitUnderflowException();
    return new Operand<float>(Float, static_cast<float >(val));
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
    long double val;
    try {
        val = std::stod(value);
    } catch (std::exception &e) {
        if (value[0] == '-')
            throw Error::LimitUnderflowException();
        else
            throw Error::LimitOverflowException();
    }
    if (val > DBL_MAX)
        throw Error::LimitOverflowException();
    else if (val < -DBL_MAX)
        throw  Error::LimitUnderflowException();
    return new Operand<double>(Double, static_cast<double >(val));
}

OperandFactory::~OperandFactory() {
}

OperandFactory *OperandFactory::getFactory() {
    if (_factory == nullptr)
        _factory = new OperandFactory();
    return _factory;
}
