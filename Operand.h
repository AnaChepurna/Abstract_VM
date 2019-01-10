//
// Created by Anastasia CHEPURNA on 2019-01-09.
//

#ifndef ABSTRACT_VM_OPERAND_H
#define ABSTRACT_VM_OPERAND_H

#include "VirtualMachine.h"
#include "IOperand.h"
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class Operand: public IOperand {
private:
    eOperandType    _operandType;
    T               _value;
    std::string     _string;
    int             _precision;

    Operand<T>() {}

public:

    Operand<T>(eOperandType type, std::string const & value) {
        _operandType = type;
        _value = static_cast<T>(stod(value, 0));
        _string = value;
        _precision = type;
    }

    ~Operand<T>() {}

    Operand<T>	&operator=(Operand const & rhs) {
        this->_value = rhs._value;
        this->_operandType = rhs._operandType;
    }

    Operand<T>( Operand const & copy ) {
        *this = copy;
    }

    eOperandType getType(void) const {
        return _operandType;
    }

    T getValue(void) const {
        return _value;
    }

    int getPrecision(void) const {
        return _precision;
    }

    IOperand const * operator+( IOperand const &rhs ) const {
        double rhsValue = static_cast<double>(stod(rhs.toString(), 0));
        std::stringstream stringStream;
        stringStream << this->_value + rhsValue;
        int resPrecision = this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision();
        eOperandType resType = static_cast<eOperandType>(resPrecision);
        return new Operand(resType, stringStream.str());
    }

    IOperand const * operator-( IOperand const &rhs ) const {
        double rhsValue = static_cast<double>(stod(rhs.toString(), 0));
        std::stringstream stringStream;
        stringStream << this->_value - rhsValue;
        int resPrecision = this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision();
        eOperandType resType = static_cast<eOperandType>(resPrecision);
        return new Operand(resType, stringStream.str());
    }

    IOperand const * operator*( IOperand const &rhs ) const {
        double rhsValue = static_cast<double>(stod(rhs.toString(), 0));
        std::stringstream stringStream;
        stringStream << this->_value * rhsValue;
        int resPrecision = this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision();
        eOperandType resType = static_cast<eOperandType>(resPrecision);
        return new Operand(resType, stringStream.str());
    }

    IOperand const * operator/( IOperand const &rhs ) const {
        std::stringstream stringStream;
        if (rhs.getType() == eOperandType::Double || rhs.getType() == eOperandType::Float) {
            double rhsValue = static_cast<double>(stod(rhs.toString(), 0));
            stringStream << this->_value / rhsValue;
        }
        else {
            int32_t rhsValue = static_cast<int32_t >(stod(rhs.toString(), 0));
            stringStream << this->_value / rhsValue;
        }
        int resPrecision = this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision();
        eOperandType resType = static_cast<eOperandType>(resPrecision);
        return new Operand(resType, stringStream.str());
    }

    IOperand const * operator%( IOperand const &rhs ) const {
        double rhsValue = static_cast<double>(stod(rhs.toString(), 0));
        std::stringstream stringStream;
        stringStream << std::fmod(this->_value, rhsValue);
        int resPrecision = this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision();
        eOperandType resType = static_cast<eOperandType>(resPrecision);
        return new Operand(resType, stringStream.str());
    }

    std::string const & toString( void ) const {
        return _string;
    }
};


#endif //ABSTRACT_VM_OPERAND_H
