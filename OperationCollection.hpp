/**
 * \file OperationCollection.hpp
 *
 * The collection class for operations
 */

#ifndef OPERATION_COLLECTION_HPP
#define OPERATION_COLLECTION_HPP

#include "Operation.hpp"
#include "error.hpp"

/**
 * \class OperationCollection
 * \brief Collection for operations
 */
class OperationCollection {
public:
  OperationCollection(const int n);
  int size() const;
  void append(const Operation* operation);
  Operation* at(const int i) const;
  ~OperationCollection();
private:
  const int MAX_SIZE;
  Operation* array[];
  int size;
};

#endif //OPERATION_COLLECTION_HPP
