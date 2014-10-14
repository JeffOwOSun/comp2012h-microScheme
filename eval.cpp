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
 * \return A pointer to the Cell containing the final answer. This Cell is always a temporary Cell that should be disposed of whenever it's no longer needed.
 */
Cell* eval(Cell* const c)
{
  if (c == nil) {
    return c;
  }

  if (c->is_int() || c->is_double() || c->is_symbol()) return c->copy();
  
  //retrieve the evaluated result of car
  Cell* returned_car_cell = eval(c->get_car());
  if ((*returned_car_cell).is_symbol()){
    //get the operator
    std::string operation = (*returned_car_cell).get_symbol();
    delete returned_car_cell;
    
    Cell* sub_tree = c->get_cdr();
    
    if (operation == "+") {
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      Cell* sum= new IntCell(0);
  
      //iterate every cons pair until meet a nil cdr
      while (current_cell != nil) {

	//current_cell is not nil, and it should be a conspair
	if (!current_cell->is_cons()) {
	  error_handler("cdr must be nil or conspair");
	}

	//pointer to the cell that contains the value to be added
	//here eval could be used against a conspair or a int/double cell
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell==nil)error_handler("add on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  delete value_cell;
	  error_handler("add operand invalid");
	}
    
	Cell* result = sum->add(value_cell);
	delete sum;
	delete value_cell;
	sum = result;
    
	//move current_cell forward;
	current_cell = current_cell->get_cdr();
      }
	
      return sum;
    } else if (operation == "-") {
      //error if no operand is supplied
      if (sub_tree == nil) error_handler("subtract on zero operand!");
  
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      //Value Cell that stores minuend
      Cell* minuend_cell;
    
      //if subtract only has one operand
      if (sub_tree->get_cdr() == nil) {
	if (!current_cell->is_cons()) error_handler("s-expression invalid: cdr must be nil or cons!");
    
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(-value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(-value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    delete value_cell;
	    error_handler("subtract operand invalid!");
	  }
	} else {
	  error_handler("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	minuend_cell = eval(current_cell->get_car());
	if (minuend_cell==nil) error_handler("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = eval(current_cell->get_car());
      
	  if (value_cell==nil) error_handler("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    delete value_cell;
	    error_handler("subtract operand invalid");
	  }
      
	  Cell* result_cell = minuend_cell->subtract(value_cell);
	  delete minuend_cell;
	  delete value_cell;
	  minuend_cell = result_cell;

	  current_cell = current_cell->get_cdr();
	}

	return minuend_cell;
      }
    } else if (operation == "*") {
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      Cell* product = new IntCell(1);

      //iterate every cons pair until meet a nil cdr
      while (current_cell != nil) {

	//current_cell is not nil, and it should be a conspair
	if (!current_cell->is_cons()) {
	  error_handler("cdr must be nil or conspair");
	}

	//pointer to the cell that contains the value to be added
	//here eval could be used against a conspair or a int/double cell
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell==nil) error_handler("multiply on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  delete value_cell;
	  error_handler("multiply operand invalid");
	}
          
	Cell* result = product->multiply(value_cell);
	delete product;
	delete value_cell;
	product = result;
   
	//move current_cell forward;
	current_cell = current_cell->get_cdr();
      }
	
      return product;
    } else if (operation == "/") {
      //error if no operand is supplied
      if (sub_tree == nil) error_handler("division on zero operand!");
  
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      //Value Cell that stores minuend
      Cell* dividend_cell;
    
      //if subtract only has one operand
      if (sub_tree->get_cdr() == nil) {
	if (!current_cell->is_cons()) error_handler("s-expression invalid: cdr must be nil or cons!");
    
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(1/value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(1/value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    delete value_cell;
	    error_handler("subtract operand invalid!");
	  }
	} else {
	  error_handler("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	dividend_cell = eval(current_cell->get_car());
	if (dividend_cell==nil) error_handler("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = eval(current_cell->get_car());
      
	  if (value_cell==nil) error_handler("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    delete value_cell;
	    error_handler("subtract operand invalid");
	  }
      
	  Cell* result_cell = dividend_cell->divide_by(value_cell);
	  delete dividend_cell;
	  delete value_cell;
	  dividend_cell = result_cell;

	  current_cell = current_cell->get_cdr();
	}

	return dividend_cell;
      }
    } else if (operation == "ceiling") {
      //current working cell
      Cell* current_cell = sub_tree;

      if (current_cell == nil || !current_cell -> is_cons()) error_handler("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) error_handler("s-expression invalid: ceiling on more than one operands");
	
      //take the ceiling and return
      Cell* returned_value = eval(current_cell->get_car());
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	if (ceilinged_value < returned_value->get_double()) ++ceilinged_value;
	delete returned_value;
	return new IntCell(ceilinged_value);
      } else {
	if(returned_value!=nil) delete returned_value;
	error_handler("s-expression invalid: ceiling operand invalid!");
      }
    } else if (operation == "floor") {
      //current working cell
      Cell* current_cell = sub_tree;

      if (current_cell == nil || !current_cell -> is_cons()) error_handler("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) error_handler("s-expression invalid: ceiling on more than one operands");
	
      //take the floor and return
      Cell* returned_value = eval(current_cell->get_car());
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	delete returned_value;
	return new IntCell(ceilinged_value);
      } else {
	if(returned_value!=nil) delete returned_value;
	error_handler("s-expression invalid: floor operand invalid");
      }
    } else if (operation == "if") {
      //temporary Cell pointers;
      Cell* condition = sub_tree;
      if (condition==nil || !condition->is_cons()) error_handler("s-expression invalid: if condition is not a conspair");
      Cell* if_true = condition->get_cdr();
      if (if_true==nil || !if_true->is_cons()) error_handler("s-expression invalid: the true return value is not a cospair");
      Cell* if_false = if_true->get_cdr(); 

      //directly return the second parameter if the third doesn't exist
      if (if_false==nil) {
	return eval(if_true->get_car());
      } else {
	if (if_false->get_cdr()!=nil) error_handler("s-expression invalid: if operator on more than three operands");
	  
	Cell* condition_cell = eval(condition->get_car());
	bool flag = false;
	  
	//retrieve values according to their types
	if (condition_cell->is_int()){
	  flag = condition_cell->get_int() ? true : false;
	} else if (condition_cell->is_double()) {
	  flag = condition_cell->get_double() ? true : false;
	} else if (condition_cell->is_symbol()) {
	  flag = condition_cell->get_symbol()!="" ? true : false;
	} else {
	  if(condition_cell!=nil) delete condition_cell;
	  error_handler("s-expression invalid: condition operand invalid to if");
	}

	if(condition_cell!=nil) delete condition_cell;
	  
	return flag ? eval(if_true->get_car()) : eval(if_false->get_car());
      }
    } else if (operation == "quote") {
      //return sub_tree's cdr directly, by making a deep copy first
      if (sub_tree==nil || !sub_tree->is_cons()) error_handler("operand for quote invalid");
      if (sub_tree->get_cdr()!=nil) error_handler("operand for quote more than one!");
      return sub_tree->get_car()->copy();
    } else if (operation == "cons") {
      if (sub_tree == nil) error_handler("operand for cons invalid");
  
      Cell* car_tobe = sub_tree;
      Cell* cdr_tobe = sub_tree->get_cdr();

      if (cdr_tobe == nil) error_handler("operand for cons invalid");
      if (cdr_tobe->get_cdr() != nil) error_handler("operand for cons more than two!");
  
      Cell* car_value = eval(car_tobe->get_car());
      Cell* cdr_value = eval(cdr_tobe->get_car());

      Cell* return_cell = new ConsCell(car_value, cdr_value);
            
      return return_cell;
    } else if (operation == "car") {
      if (sub_tree == nil) error_handler("zero operand for car");
      if (sub_tree->get_cdr() != nil) error_handler("more than one operands for car");

      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_car = value_cell->get_car()->copy();
	  delete value_cell;
	  return value_car;
	} else {
	  delete value_cell; 
	  error_handler("car on non-cons cell");
	}
      } else {
	error_handler ("car on nil");
      }
    } else if (operation == "cdr") {
      if (sub_tree == nil) error_handler("zero operand for cdr");
      if (sub_tree->get_cdr() != nil) error_handler("more than one operands for cdr");

      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_cdr = value_cell->get_cdr()->copy();
	  delete value_cell;
	  return value_cdr;
	} else {
	  delete value_cell; 
	  error_handler("cdr on non-cons cell");
	}
      } else {
	error_handler ("cdr on nil");
      }
    } else if (operation == "nullp") {
      if (sub_tree == nil) error_handler("zero operand for nullp");
      if (sub_tree->get_cdr() != nil) error_handler("more than one operands for nullp");

      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
	delete value_cell;
	return new IntCell(0);
      } else {
	return new IntCell(1);
      }
    } else {    
      //If this line is executed, it means that no matching operation found
      error_handler("Invalid s-expression: unexpected operator \""+operation+"\"");
    }
  } else {
    if (returned_car_cell!=nil) delete returned_car_cell;
    error_handler ("Invalid s-expression: root of subtree is not evaluated to be a symbol cell");
  }  
}


