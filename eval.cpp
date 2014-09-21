/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"
#include <cmath>

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
    return c;
  }
  
  if (listp(c)) {
    //get car of c
    //if car is a symbol cell (it must, otherwise the eval() begins at wrong place)
    if (symbolp(car(c))){
      //get the symbol
      switch (get_symbol(car(c))){
      case "+":
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
	    error_handler();
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
	  } else {
	    //if value_cell is not an int cell
	    if (sum_is_double) {
	      double_sum += get_double(value_cell);
	    } else {
	      //migrate int_sum to double_sum and do related clean-ups
	      double_sum = int_sum;
	      int_sum = 0;
	      sum_is_double = true;
	      
	      double_sum += get_double(value_cell);
	    }
	  }

	  //move current_cell forward;
	  current_cell = cdr(current_cell);
	}
	
	return new Cell(sum_is_double ? double_sum : int_sum);
	break;
      case "ceiling":
	//current working cell
	Cell* current_cell = cdr(c);
	//take the ceiling and return
	return new Cell(ceiling(eval(car(current_cell))));
	break;
      case "if":
	//temporary Cell pointers;
	Cell* condition = cdr(c);
	Cell* if_true = cdr(condition);
	Cell* if_false = cdr(if_true);

	if (nullp(if_false)) {
	  return eval(car(if_true));
	} else {
	  return eval(car(condition)) ? eval(car(if_true)) : eval(car(if_false));
	}
	  
	break;
      default:
	error_handler();
      }
    } else {
      //car is not a symbol cell
      error_handler();
    }
  }
}
