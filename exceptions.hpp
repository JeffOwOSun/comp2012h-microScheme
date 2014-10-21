/**
 * \file exceptions.hpp
 * \brief Custom exception classes
 */
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include<stdexcept>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

/**
 * \class DivideByZeroError
 */
class DivideByZeroError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param msg The message thst's going to be supplied to runtime_error constructor. Default is "divide by zero"
   */
  DivideByZeroError(string msg = "divide by zero");
};

/**
 * \class OperandInvalidError
 */
class OperandInvalidError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param operation The name for the operation that is supplied with mismatched number of operands
   */
  OperandInvalidError(string operation);
};

/**
 * \class OperandNumberMismatchError
 */
class OperandNumberMismatchError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param operation The name for the operation that is supplied with mismatched number of operands
   * \param n Number of expected operand number
   */
  OperandNumberMismatchError(string operation, string n);
};

/**
 * \class UnimplementedError
 */
class UnimplementedError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param method_name The method name that is considered unimplemented
   */
  UnimplementedError(string method_name);
};

#endif // EXCEPTIONS_HPP
