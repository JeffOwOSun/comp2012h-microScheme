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
 * \param c A constant pointer to a Cell instance, which is the root of the tree to be computed
 * \return A pointer to the Cell containing the final answer.
 */
Cell* eval(Cell* const c)
{
  if (nullp(c)) {
    return c;
  }

  if (intp(c) || doublep(c) || symbolp(c)){
    return deep_copy(c);
  }
  
  if (listp(c)) {
    //get car of c
    //using eval will automatically evaluate the subtree, if car(c) is itself a conspair
    Cell* car_value = eval(car(c));
    
    //if car is a symbol cell (it must, otherwise the eval() begins at wrong place)
    if (symbolp(car_value)){
      //get the symbol
      //case 1: +
      if (get_symbol(car_value) == "+"){
	
	//delete car_value as it's not needed any more
	delete car_value;

	//temporary sums variables
	double double_sum = 0;
	int int_sum = 0;
	bool sum_is_double = false;

	//Cell pointer to the current working cell
	Cell* current_cell = cdr(c);

	//iterate every cons pair until meet a nil cdr
	while (!nullp(current_cell)) {

	  //current_cell is not nil, and it should be a conspair
	  if (!listp(current_cell)) {
	    error_handler("cdr must be nil or conspair");
	  }

	  //pointer to the cell that contains the value to be added
	  //here eval could be used against a conspair or a int/double cell
	  Cell* value_cell = eval(car(current_cell));
	  
	  //deal with value_cell, see if it's int or not
	  if (intp(value_cell)) {
	    if (sum_is_double) {
	      double_sum += get_int(value_cell);
	    } else {
	      int_sum += get_int(value_cell);
	    }
	  } else if (doublep(value_cell)) {
	    //if value_cell is not a double cell
	    if (sum_is_double) {
	      double_sum += get_double(value_cell);
	    } else {
	      //migrate int_sum to double_sum and do related clean-ups
	      double_sum = int_sum;
	      int_sum = 0;
	      sum_is_double = true;
	      
	      double_sum += get_double(value_cell);
	    }
	  } else {
	    if (!nullp(value_cell)) delete value_cell;
	    error_handler("s-expression invalid: + operands invalid");
	  }
	  if (!nullp(value_cell)) delete value_cell;
	  //move current_cell forward;
	  current_cell = cdr(current_cell);
	}
	
	return sum_is_double ? make_double(double_sum) : make_int(int_sum);
      }
      //case 2: ceiling
      else if (get_symbol(car_value) == "ceiling") {
	//delete car_value as it's no longer needed
	delete car_value;

	//current working cell
	Cell* current_cell = cdr(c);
	//take the ceiling and return
	Cell* returned_value = eval(car(current_cell));
	if (intp(returned_value)){
	  return returned_value;
	} else if (doublep(returned_value)){
	  int ceilinged_value = int(get_double(returned_value));
	  if (ceilinged_value < get_double(returned_value)) ++ceilinged_value;
	  delete returned_value;
	  return make_int(ceilinged_value);
	} else {
	  if(!nullp(returned_value)) delete returned_value;
	  error_handler("trying to apply ceiling to a symbol cell!");
	}
      }
      //case 3: if
      else if (get_symbol(car_value) == "if") {
	//delete car_value as it's no longer needed
	delete car_value;
	
	//temporary Cell pointers;
	Cell* condition = cdr(c);
	if (!listp(condition)) error_handler("s-expression invalid: condition is not a conspair");
	Cell* if_true = cdr(condition);
	if (!listp(if_true)) error_handler("s-expression invalid: the true return value is not a cospair");
	Cell* if_false = cdr(if_true); 

	//directly return the second parameter if the third doesn't exist
	if (nullp(if_false)) {
	  return eval(car(if_true));
	} else {
	  Cell* condition_cell = eval(car(condition));
	  bool flag = false;
	  
	  //retrieve values according to their types
	  if (intp(condition_cell)){
	    flag = get_int(condition_cell) ? true : false;
	  } else if (doublep(condition_cell)) {
	    flag = get_double(condition_cell) ? true : false;
	  } else if (symbolp(condition_cell)) {
	    flag = get_symbol(condition_cell)!="" ? true : false;
	  } else {
	    if(!nullp(car_value)) delete condition_cell;
	    error_handler("s-expression invalid: parameter invalid to if");
	  }

	  if(!nullp(car_value)) delete condition_cell;
	  
	  return flag ? eval(car(if_true)) : eval(car(if_false));
	}
      } else {
	//delete car_value as it's no longer needed
	delete car_value;
	
	error_handler("s-expression invalid: operator not one of +, ceiling or if");
      }
    } else {
      //delete car_value as it's no longer needed
      if(!nullp(car_value)) delete car_value;
	
      //value_car is not a symbol cell
      error_handler("s-expression invalid: the first element of the tree/subtree is not a proper operator");
    }
  }
}
