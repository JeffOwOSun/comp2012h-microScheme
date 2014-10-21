/**
 * \file exceptions.cpp
 * \brief Custom exception classes
 */

#include"exceptions.hpp"
using namespace std;

DivideByZeroError::DivideByZeroError(string msg): runtime_error(msg){}

OperandInvalidError::OperandInvalidError(string operation): runtime_error(operation + " operand invalid"){}

OperandNumberMismatchError::OperandNumberMismatchError(string operation, string n): runtime_error(operation + " must have " + n +" operand(s)"){}

UnimplementedError::UnimplementedError(string method_name): runtime_error(method_name + " method not implemented"){}
