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
   * \brief execute this operation upon the given sub-tree
   * \param sub_tree The subtree upon which the operation should be executed
   */
  virtual Cell* exec (const Cell* const sub_tree) const=0;

  /**
   * \brief Check if the given identifier matches the embeded identifier
   * \param identifier The identifier to be checked
   */
  virtual bool is_operation (const std::string identifier) const=0;

  /**
   * \brief Virtual destructor
   */
  virtual ~Operation();
};

class SumOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class SubractOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class MultiplyOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class DivideOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class CeilingOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class FloorOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class IfOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class QuoteOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class ConsOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class CarOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class CdrOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

class NullpOperation: Operation {
public:
  virtual Cell* exec (const Cell* const sub_tree) const;
  virtual bol is_operation (std::string identifier) const;
};

#endif //OPERATION_HPP
