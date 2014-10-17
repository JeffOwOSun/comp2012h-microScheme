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
  /**
   * \brief Constructor
   * \param msg The message thst's going to be supplied to runtime_error constructor. Default is "divide by zero"
   */
  DivideByZeroError(std::string msg = "divide by zero");
};

/**
 * \class OperandInvalidError
 */
class OperandInvalidError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param msg The message that's going to be supplied to runtime_error constructor. Default is "operand invalid"
   */
  OperandInvalidError(std::string msg = "operand invalid");
};

/**
 * \class OperandNumberMismatchError
 */
class OperandNumberMismatchError : public runtime_error
{
public:
  /**
   * \brief Constructor
   * \param n Number of expected operand number
   */
  OperandNumberMismatchError(int n);
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
  UnimplementedError(std::string method_name);
};
