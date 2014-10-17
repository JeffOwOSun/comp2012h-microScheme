/**
 * \file exceptions.cpp
 * \brief Custom exception classes
 */

#include"exceptions.hpp"
using namespace std;

DivideByZeroError::DivideByZeroError(string msg): runtime_error(msg){}

OperandInvalidError::OperandInvalidError(string operation): runtime_error(operation + " operand invalid"){}

OperandNumberMismatchError::OperandNumberMismatchError(string operation, int n): runtime_error(operation + " must have "+n+" operand(s)"){}

OperandNumberMismatchError::OperandNumberMismatchError(string operation, int n, int m): runtime_error(operation + " must have "+n+" OR "+m+" operand(s)"){}

OperandNumberMismatchError::OperandNumberMismatchError(string operation, int n, int m, int k): runtime_error(operation + " must have "+n+" OR "+m+" OR "+k+" operand(s)"){}

UnimplementedError::UnimplementedError(string method_name): runtime_error(method_name + " method not implemented");
