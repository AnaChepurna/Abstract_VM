//
// Created by Anastasia CHEPURNA on 12/11/18.
//

#ifndef ABSTRACT_VM_IOPERAND_H
#define ABSTRACT_VM_IOPERAND_H

#include <iostream>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    int getPrecision(void) const;
    eOperandType getType(void) const;
    IOperand const * operator+( IOperand const &rhs ) const;
    IOperand const * operator-( IOperand const &rhs ) const;
    IOperand const * operator*( IOperand const &rhs ) const;
    IOperand const * operator/( IOperand const &rhs ) const;
    IOperand const * operator%( IOperand const &rhs ) const;
    std::string const & toString( void ) const;
};

#endif //ABSTRACT_VM_IOPERAND_H
