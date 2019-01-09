//
// Created by Anastasia CHEPURNA on 2019-01-09.
//

#ifndef ABSTRACT_VM_OPERAND_H
#define ABSTRACT_VM_OPERAND_H

#include "VirtualMachine.h"
#include "IOperand.h"

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
        _value = 10; //static_cast<T>(value);
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
        return new Operand();
    }

    IOperand const * operator-( IOperand const &rhs ) const {
        return new Operand();
    }

    IOperand const * operator*( IOperand const &rhs ) const {
        return new Operand();
    }

    IOperand const * operator/( IOperand const &rhs ) const {
        return new Operand();
    }

    IOperand const * operator%( IOperand const &rhs ) const {
        return new Operand();
    }

    std::string const & toString( void ) const {
        return _string;
    }
};


#endif //ABSTRACT_VM_OPERAND_H
