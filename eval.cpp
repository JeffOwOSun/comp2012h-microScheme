/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"

OperationCollection operations = OperationCollection(12);

operations.append(new SumOperation());
operations.append(new SubtractOperation());
operations.append(new MultiplyOperation());
operations.append(new DivideOperation());

operations.append(new CeilingOperation());
operations.append(new FloorOperation());

operations.append(new IfOperation());

operations.append(new QuoteOperation());

operations.append(new ConsOperation());
operations.append(new CarOperation());
operations.append(new CdrOperation());
operations.append(new NullpOperation());

/**
 * \brief The evaluation function that calculates the parsed s-expression tree
 * \param c A constant pointer to a Cell instance, which is the root of the tree to be computed
 * \return A pointer to the Cell containing the final answer.
 */
Cell* eval(Cell* const c)
{
  if (c == nil){
    return c;
  } else if ((*c).is_int() || (*c).is_double() || (*c).is_symbol()) {
    return (*c).copy();
  } else if ((*c).is_cons()) {
    Cell* returned_car_cell = eval((*c).get_car());
    if ((*returned_car_cell).is_symbol()){
      std::string operation = (*returned_car_cell).get_symbol();

      //go through each operation, execute matching one
      int operations_index = 0;
      for (; operations_index < operations.size(); ++operations_index) {
	if ((*(operations.at(operations_index))).is_operation(operation)){
	  (*(operations.at(operations_index))).exec((*c).get_cdr());
	  break;
	}
      }
      if (operations_index == operations.size()) error_handler("Invalid s-expression: unexpected operator \""+operation+"\"");
    } else error_handler ("Invalid s-expression: root of subtree is not a symbol cell");
  } else error_handler("Unidentified Cell type");
}
