/**
 * \file helper.hpp
 * \brief contains global helper functions
 */

#ifndef HELPER_HPP
#define HELPER_HPP
#include "Cell.hpp"

class Cell;
// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;

/**
 * \brief A helper function for safely delete
 * \param c Reference to the pointer to be deleted. T should be a pointer type
 */
template<typename T>
inline void safe_delete(T& c)
{
  if (c != nil) delete c;
  c = NULL;
}

/**
 * \brief A helper function to copy char arrary
 * \param s Pointer to the source array
 */
inline char* str_copy(const char* const s)
{
  char* tmp = new char[strlen(s)+1];
  strcpy(tmp,s);
  return tmp;
}
#endif //HELPER_HPP
