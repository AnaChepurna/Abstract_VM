//
// Created by Anastasia CHEPURNA on 2019-01-09.
//

#ifndef ABSTRACT_VM_OPERAND_H
#define ABSTRACT_VM_OPERAND_H

#include "OperandFactory.h"
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class Operand: public IOperand {
private:
    eOperandType    _operandType;
    T               _value;
    std::string     _string;
    OperandFactory const _factory = OperandFactory();

    Operand<T>() {}

public:

    Operand<T>(eOperandType type, T value) {
        _operandType = type;
        _value = value;
        std::stringstream str;
        str << value;
        _string = str.str();
    }

    ~Operand<T>() {}

    Operand<T>	&operator=(Operand const & rhs) {
        this->_value = rhs._value;
        this->_operandType = rhs._operandType;
        this->_string = rhs._string;
    }

    Operand<T>( Operand const & copy ) {
        *this = copy;
    }

    eOperandType getType() const override {
        return _operandType;
    }

    T getValue() const {
        return _value;
    }

    int getPrecision() const override {
        return (int)_operandType;
    }

    IOperand const * operator+( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString(), nullptr));
        std::stringstream stringStream;
        stringStream << this->_value + rhsValue;
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);
        return _factory.createOperand(resType, stringStream.str());
    }

    IOperand const * operator-( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString(), nullptr));
        std::stringstream stringStream;
        stringStream << this->_value - rhsValue;
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);
        return _factory.createOperand(resType, stringStream.str());
    }

    IOperand const * operator*( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString(), nullptr));
        std::stringstream stringStream;
        stringStream << this->_value * rhsValue;
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);
        return _factory.createOperand(resType, stringStream.str());
    }

    IOperand const * operator/( IOperand const &rhs ) const override {
        std::stringstream stringStream;
        if (rhs.getType() >= Float) {
            auto rhsValue = static_cast<long double>(stod(rhs.toString(), nullptr));
            stringStream << this->_value / rhsValue;
        }
        else {
            auto rhsValue = static_cast<int64_t >(stod(rhs.toString(), nullptr));
            stringStream << this->_value / rhsValue;
        }
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);
        return _factory.createOperand(resType, stringStream.str());
    }

    IOperand const * operator%( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString(), nullptr));
        std::stringstream stringStream;
        stringStream << std::fmod(this->_value, rhsValue);
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);
        return _factory.createOperand(resType, stringStream.str());
    }

    std::string const & toString() const override {
        return _string;
    }
};


#endif //ABSTRACT_VM_OPERAND_H
