//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_IOPERAND_H
#define ABSTRACT_VM_IOPERAND_H

#include <iostream>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    virtual int getPrecision(void) const = 0;
    virtual eOperandType getType(void) const = 0;
    virtual IOperand const * operator+( IOperand const &rhs ) const = 0;
    virtual IOperand const * operator-( IOperand const &rhs ) const = 0;
    virtual IOperand const * operator*( IOperand const &rhs ) const = 0;
    virtual IOperand const * operator/( IOperand const &rhs ) const = 0;
    virtual IOperand const * operator%( IOperand const &rhs ) const = 0;
    virtual std::string const & toString( void ) const = 0;
    virtual ~IOperand( void ) {}
//    virtual IOperand const * createOperand( eOperandType type, std::string const & value ) const = 0;
};

#endif //ABSTRACT_VM_IOPERAND_H
