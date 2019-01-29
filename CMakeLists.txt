cmake_minimum_required(VERSION 3.12)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
        incl)

add_executable(Abstract_VM
        incl/IOperand.h
        src/Lexer.cpp
        incl/Lexer.h
        src/main.cpp
        src/Parser.cpp
        incl/Parser.h
        src/VirtualMachine.cpp
        incl/VirtualMachine.h
        incl/Operand.h
        incl/Token.h
        src/Token.cpp
        src/OperandFactory.cpp
        incl/OperandFactory.h
        src/Error.cpp
        incl/Error.h)
