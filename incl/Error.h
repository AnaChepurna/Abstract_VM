//
// Created by Anastasia CHEPURNA on 2019-01-29.
//

#ifndef ABSTRACT_VM_ERROR_H
#define ABSTRACT_VM_ERROR_H


#include <exception>

class Error {

public:
    class NoExitException : public std::exception {
    public:
        const char *what() const throw();
    };
    class TokenAfterExitException : public std::exception {
    public:
        const char *what() const throw();
    };
    class ExpectedValueAfterException : public  std::exception {
    public:
        const char *what() const throw();
    };
    class UnexpectedTokenException : public  std::exception {
    public:
        const char *what() const throw();
    };
    class BrokenFileException : public std::exception {
    public:
        const char *what() const throw();
    };
    class NoRecognizedCodeException : public std::exception {
    public:
        const char *what() const throw();
    };
    class LimitOverflowException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class LimitUnderflowException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class UnexpectedLexemException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class MissedWhitespaceException : public std::exception {
    public:
        const char *what() const noexcept;
    };
    class UnknownOperandTypeException : public std::exception {
    public:
        const char *what() const noexcept;
    };
    class UnexpectedNumericalValueSybolException : public std::exception {
    public:
        const char *what() const noexcept;
    };
    class MissedBracketsException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class MissedOperandValueException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class NotAssertTypeException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class NotAssertValueException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class DevisionByZeroException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class OperationOnEmptyStackException: public std::exception {
    public:
        const char *what() const noexcept;
    };
    class LessThanTwoValuesInStackException: public std::exception {
    public:
        const char *what() const noexcept;
    };
};


#endif //ABSTRACT_VM_ERROR_H
