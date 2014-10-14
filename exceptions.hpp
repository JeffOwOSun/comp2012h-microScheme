/**
 * \file exceptions.hpp
 * \brief Custom exception classes
 */

#include<stdexcept>
#include<string>
using namespace std;

/**
 * \class DivideByZeroError
 */
class DivideByZeroError : public runtime_error
{
public:
  DivideByZeroError(std::string msg = "divide by zero");
};

/**
 * \class OperandInvalidError
 */
class OperandInvalidError : public runtime_error
{
public:
  OperandInvalidError(std::string msg = "operand invalid");
};

/**
 * \class OperandNumberMismatchError
 */
class OperandNumberMismatchError : public runtime_error
{
public:
  OperandNumberMismatchError(int n);
};
