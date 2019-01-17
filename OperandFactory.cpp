//
// Created by Anastasia CHEPURNA on 2019-01-16.
//

#include "OperandFactory.h"
#include "Operand.h"

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*_functions.at(type))(value);
}

OperandFactory::OperandFactory() {
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
    int64_t val = std::stoll(value);
    if (val > INT8_MAX)
        throw OperandFactory::LimitOverflowException();
    else if (val < INT8_MIN)
        throw  OperandFactory::LimitUnderflowException();
    return new Operand<int8_t>(Int8, static_cast<int8_t >(val));
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
    int64_t val = std::stoll(value);;
    if (val > INT16_MAX)
        throw OperandFactory::LimitOverflowException();
    else if (val < INT16_MIN)
        throw  OperandFactory::LimitUnderflowException();
    return new Operand<int16_t>(Int16, static_cast<int16_t >(val));
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
    int64_t val = std::stoll(value);
    if (val > INT32_MAX)
        throw OperandFactory::LimitOverflowException();
    else if (val < INT32_MIN)
        throw  OperandFactory::LimitUnderflowException();
    return new Operand<int32_t>(Int32, static_cast<int32_t >(val));
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
    long double val = std::stod(value);
    if (val > FLT_MAX)
        throw OperandFactory::LimitOverflowException();
    else if (val < -FLT_MAX)
        throw  OperandFactory::LimitUnderflowException();
    return new Operand<float>(Float, static_cast<float >(val));
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
    long double val = std::stod(value);
    if (val > DBL_MAX)
        throw OperandFactory::LimitOverflowException();
    else if (val < -DBL_MAX)
        throw  OperandFactory::LimitUnderflowException();
    return new Operand<double>(Double, static_cast<double >(val));
}

OperandFactory::~OperandFactory() {
}

OperandFactory::OperandFactory(OperandFactory const &rhs) {
}

OperandFactory &OperandFactory::operator=(OperandFactory const &rhs) {
    return *this;
}

const char *OperandFactory::LimitOverflowException::what() const noexcept {
    return "Limit overflow";
}

const char *OperandFactory::LimitUnderflowException::what() const noexcept {
    return "Limit underflow";
}
