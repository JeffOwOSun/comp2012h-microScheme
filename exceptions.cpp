/**
 * \file exceptions.cpp
 * \brief Custom exception classes
 */

#include<"exceptions.hpp">

DivideByZeroError::DivideByZeroError(std::string msg): runtime_error(msg){}

OperandInvalidError::OperandInvalidError(std::string msg): runtime_error(msg){}

OperandNumberMismatchError::OperandNumberMismatchError(int n): runtime_error("must have "+n+" operand(s)"){}
