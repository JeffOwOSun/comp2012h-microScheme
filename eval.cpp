/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"

/**
 * \brief The evaluation function that calculates the parsed s-expression tree
 * \param c A constant pointer to a Cell instance, which is the root of the tree to be computed. Root of tree must not be nil, or error occurs.
 * \return A pointer to the Cell containing the final answer. This Cell is always a temporary Cell that should be disposed of whenever it's no longer needed.
 */
Cell* eval(Cell* const c)
{
  return c->eval();
}


