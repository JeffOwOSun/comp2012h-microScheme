/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"

//the operations collection to be used by eval
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
 * \return A pointer to the Cell containing the final answer. This Cell is always a temporary Cell that should be disposed of whenever it's no longer needed.
 */
Cell* eval(Cell* const c)
{
  if (c == nil){
    return c;
  } else if ((*c).is_int() || (*c).is_double() || (*c).is_symbol()) {
    return (*c).copy();
  } else if ((*c).is_cons()) {
    //retrieve the evaluated result of car
    Cell* returned_car_cell = eval((*c).get_car());
    if ((*returned_car_cell).is_symbol()){
      //get the operator
      std::string operation = (*returned_car_cell).get_symbol();

      //go through each operation, execute matching one
      for (int i=0; i< operations.size(); ++i_) {
	if ((*(operations.at(i))).is_operation(operation)){
	  return (*(operations.at(i))).exec((*c).get_cdr());
	}
      }
      //If this line is executed, it means that no matching operation found
      if (returned_car_cell!=nil) delete returned_car_cell;
      error_handler("Invalid s-expression: unexpected operator \""+operation+"\"");
    } else {
      if (returned_car_cell!=nil) delete returned_car_cell;
      error_handler ("Invalid s-expression: root of subtree is not evaluated to be a symbol cell");
    }
  } else error_handler("Unidentified Cell type");
}
