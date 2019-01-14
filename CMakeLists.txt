cmake_minimum_required(VERSION 3.12)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Abstract_VM
        IOperand.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Parser.cpp
        Parser.h
        VirtualMachine.cpp
        VirtualMachine.h
        Operand.h
        Lexem.h
        Lexem.cpp)
