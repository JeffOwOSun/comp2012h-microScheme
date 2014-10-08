/**
 * \file OperationCollection.cpp
 */

#include "OperationCollection.hpp"

OperationCollection::OperationCollection(const int n):MAX_SIZE(n), size(0) {
  array = new Operation* [MAX_SIZE];
}

OperationCollection::size() const
{
  return size;
}

OperationCollection::append(const Operation* operation)
{
  array[size] = operation;
  ++size;
}

OperationCollection::at(const int i) const
{
  return array[i];
}

OperationCollection::~OperationCollection()
{
  for (int i=0; i<size; ++i){
    delete array[i];
  }
  delete[] array;
}
