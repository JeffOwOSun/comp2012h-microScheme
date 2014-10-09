/**
 * \file Operation.hpp
 *
 * Encapsulates the abstract interface for self-defined operations
 */

#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <string>

#include "error.hpp"
#include "Cell.hpp"

/**
 * \class Operation
 * \brief ABC for Operation
 */
class Operation {
public:
  /**
   * \brief Constructor
   * \param id The intended identifier;
   */
  Operation(std::string id);
  /**
   * \brief execute this operation upon the given sub-tree
   * \param sub_tree The subtree upon which the operation should be executed
   */
  virtual Cell* exec (Cell* const sub_tree) const=0;

  /**
   * \brief Check if the given identifier matches the embeded identifier
   * \param identifier The identifier to be checked
   */
  bool is_operation (const std::string identifier) const;

  /**
   * \brief Virtual destructor
   */
  virtual ~Operation();
private:
  std::string identifier_m;
};

class SumOperation: Operation {
public:
  SumOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class SubtractOperation: Operation {
public:
  SubtractOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class MultiplyOperation: Operation {
public:
  MultiplyOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class DivideOperation: Operation {
public:
  DivideOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class CeilingOperation: Operation {
public:
  CeilingOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class FloorOperation: Operation {
public:
  FloorOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class IfOperation: Operation {
public:
  IfOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class QuoteOperation: Operation {
public:
  QuoteOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class ConsOperation: Operation {
public:
  ConsOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class CarOperation: Operation {
public:
  CarOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class CdrOperation: Operation {
public:
  CdrOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

class NullpOperation: Operation {
public:
  NullpOperation();
  virtual Cell* exec (Cell* const sub_tree) const;
};

#endif //OPERATION_HPP
