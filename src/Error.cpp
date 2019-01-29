//
// Created by Anastasia CHEPURNA on 2019-01-29.
//

#include <incl/Error.h>

#include "Error.h"

const char *Error::UnexpectedLexemException::what() const throw() {
    return "Unknown instruction";
}

const char *Error::MissedWhitespaceException::what() const throw() {
    return "Missed whitespace after instruction";
}

const char *Error::UnknownOperandTypeException::what() const throw() {
    return "Unknown operand type";
}

const char *Error::UnexpectedNumericalValueSybolException::what() const throw() {
    return "Unexpected symbol in numerical value";
}

const char *Error::MissedBracketsException::what() const noexcept {
    return "Missed brackets in operand declaration";
}

const char *Error::MissedOperandValueException::what() const noexcept {
    return "Missed value in operand declaration";
}

const char *Error::LimitOverflowException::what() const noexcept {
    return "Limit overflow";
}

const char *Error::LimitUnderflowException::what() const noexcept {
    return "Limit underflow";
}

const char *Error::NoExitException::what() const noexcept {
    return "No exit instruction in the end of program";
}

const char *Error::TokenAfterExitException::what() const noexcept {
    return "Token after exit instruction";
}

const char *Error::ExpectedValueAfterException::what() const noexcept {
    return "Expecting operand after instruction";
}

const char *Error::UnexpectedTokenException::what() const noexcept {
    return "Unexpected token after instruction";
}

const char *Error::BrokenFileException::what() const noexcept {
    return "Cannot open input file : Check the filename or access rights";
}

const char *Error::NoRecognizedCodeException::what() const noexcept {
    return "Cannot recognize any token : Check input data format";
}

