//
// Created by Anastasia CHEPURNA on 2019-01-09.
//

#ifndef ABSTRACT_VM_OPERAND_H
#define ABSTRACT_VM_OPERAND_H

#include "OperandFactory.h"
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <iomanip>

#define ABS(x) (x > 0 ? x : -x)

template <typename T>
class Operand: public IOperand {
private:
    eOperandType    _operandType;
    std::string     _string;

    Operand<T>() {}

public:

    Operand<T>(eOperandType type, T value) {
        _operandType = type;
        if (type < Float)
            _string = std::to_string(value);
        else {
            std::stringstream str;
            if (type == Float)
                str << std::setprecision(7);
            else
                str << std::setprecision(14);
            str << value;
            _string = str.str();
        }
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

    int getPrecision() const override {
        return (int)_operandType;
    }

    IOperand const * operator+( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString()));
        auto value = static_cast<long double>(stod(toString()));
        value += rhsValue;

        std::stringstream stringStream;
        stringStream << value;

        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);

        return OperandFactory::getFactory()->createOperand(resType, stringStream.str());
    }

    IOperand const * operator-( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString()));
        auto value = static_cast<long double>(stod(toString()));
        value -= rhsValue;

        std::stringstream stringStream;
        stringStream << value;

        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);

        return OperandFactory::getFactory()->createOperand(resType, stringStream.str());
    }

    IOperand const * operator*( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString()));
        auto value = static_cast<long double>(stod(toString()));
        if (ABS(DBL_MAX / rhsValue) < ABS(value)) {
            if ((rhsValue > 0 && value > 0)||(rhsValue < 0 && value < 0))
                throw Error::LimitOverflowException();
            else
                throw Error::LimitUnderflowException();
        }
        value *= rhsValue;

        std::stringstream stringStream;
        stringStream << value;

        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);

        return OperandFactory::getFactory()->createOperand(resType, stringStream.str());
    }

    IOperand const * operator/( IOperand const &rhs ) const override {
        std::stringstream stringStream;

        if (rhs.getType() >= Float) {
            auto rhsValue = static_cast<long double>(stod(rhs.toString()));
            auto value = static_cast<long double>(stod(toString()));
            stringStream << value / rhsValue;
        }
        else {
            auto rhsValue = static_cast<int64_t >(stoll(rhs.toString()));
            auto value = static_cast<int64_t >(stod(toString()));
            stringStream << value / rhsValue;
        }
        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);

        return OperandFactory::getFactory()->createOperand(resType, stringStream.str());
    }

    IOperand const * operator%( IOperand const &rhs ) const override {
        auto rhsValue = static_cast<long double>(stod(rhs.toString()));
        auto value = static_cast<long double>(stod(toString()));

        std::stringstream stringStream;
        stringStream << std::fmod(value, rhsValue);

        int resPrecision = this->getPrecision() >= rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision();
        auto resType = static_cast<eOperandType>(resPrecision);

        return OperandFactory::getFactory()->createOperand(resType, stringStream.str());
    }

    std::string const & toString() const override {
        return _string;
    }
};


#endif //ABSTRACT_VM_OPERAND_H
