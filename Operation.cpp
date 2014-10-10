/**
 * \file Operation.cpp
 */

#include "Operation.hpp"
#include "eval.hpp"

//////////////////////////////////Operation/////////////////////////////////////
Operation::Operation(std::string id): identifier_m(id){};

Operation::is_operation (const std::string identifier) const
{
  return identifier == identifier_m;
}

////////////////////////////////SumOperation////////////////////////////////////
SumOperation::SumOperation(): Operation("+"){};

SumOperation::exec (Cell* const sub_tree) const
{
  //temporary sums variables
  double double_sum = 0;
  int int_sum = 0;
  bool sum_is_double = false;

  //Cell pointer to the current working cell
  Cell* current_cell = sub_tree;

  //iterate every cons pair until meet a nil cdr
  while (current_cell != nil) {

    //current_cell is not nil, and it should be a conspair
    if (!current_cell->is_cons()) {
      error_handler("cdr must be nil or conspair");
    }

    //pointer to the cell that contains the value to be added
    //here eval could be used against a conspair or a int/double cell
    Cell* value_cell = eval(current_cell->get_car());
	  
    //deal with value_cell, see if it's int or not
    if (value_cell->is_int()) {
      if (sum_is_double) {
	double_sum += value_cell->get_int();
      } else {
	int_sum += value_cell->get_int();
      }
    } else if (value_cell->is_double()) {
      //if value_cell is not a double cell
      if (sum_is_double) {
	double_sum += value_cell->get_double();
      } else {
	//migrate int_sum to double_sum and do related clean-ups
	double_sum = int_sum;
	int_sum = 0;
	sum_is_double = true;
	      
	double_sum += value_cell->get_double();
      }
    } else {
      if (value_cell != nil) delete value_cell;
      error_handler("s-expression invalid: + operands invalid");
    }
    if (value_cell != nil) delete value_cell;
    //move current_cell forward;
    current_cell = current_cell->get_cdr();
  }
	
  return sum_is_double ? (Cell*)new DoubleCell(double_sum) : (Cell*)new IntCell(int_sum);
}

////////////////////////////SubtractOperation///////////////////////////////////
SubtractOperation::SubtractOperation():Operation("-"){};

Cell* SubtractOperation::exec(Cell* const sub_tree)
{
  //error if no operand is supplied
  if (sub_tree == nil) error_handler("subtract on zero operand!");
  
  //Cell pointer to the current working cell
  Cell* minuend_cell = sub_tree;
  Cell* subtrahend_cell = minuend_cell->get_cdr();
  
  //if subtract only has one operand
  if (subtrahend_cell == nil) {
    if (!minuend_cell->is_cons()) error_handler("s-expression invalid: cdr must be nil or cons!");
    
    Cell* value_cell = eval(minuend_cell->get_car());

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
    //more than one operand
  
    //temporary results variables
    double double_result = 0;
    int int_result = 0;
    bool result_is_double = false;

    if (minuend_cell->is_int()) {
      int_result = minuend_cell->get_int();
    } else if (minuend_cell->is_double()) {
      result_is_double=true;
      double_result = minuend_cell->get_double();
    }
      
    //iterate every cons pair until meet a nil cdr
    while (subtrahend_cell != nil) {

      //substrahend_cell is not nil, and it should be a conspair
      if (!subtrahend_cell->is_cons()) {
	error_handler("s-expression invalid: cdr must be nil or conspair");
      }

      //pointer to the cell that contains the value to be added
      //here eval could be used against a conspair or a int/double cell
      Cell* value_cell = eval(subtrahend_cell->get_car());
	  
      //deal with value_cell, see if it's int or not
      if (value_cell->is_int()) {
	if (result_is_double) {
	  double_result -= value_cell->get_int();
	} else {
	  int_result -= value_cell->get_int();
	}
      } else if (value_cell->is_double()) {
	//if value_cell is not a double cell
	if (result_is_double) {
	  double_result -= value_cell->get_double();
	} else {
	  //migrate int_result to double_result and do related clean-ups
	  double_result = int_result;
	  int_result = 0;
	  result_is_double = true;
	      
	  double_result -= value_cell->get_double();
	}
      } else {
	if (value_cell != nil) delete value_cell;
	error_handler("s-expression invalid: - operands invalid");
      }
      if (value_cell != nil) delete value_cell;
      //move subtrahend_cell forward;
      subtrahend_cell = subtrahend_cell->get_cdr();
    }
	
    return result_is_double ? (Cell*)new DoubleCell(double_result) : (Cell*)new IntCell(int_result);
  }
}

////////////////////////////MultiplyOperation///////////////////////////////////
MultiplyOperation::MultiplyOperation():Operation("*"){};

Cell* MultiplyOperation::exec(Cell* const sub_tree)
{

  //temporary products variables
  double double_product = 1.0;
  int int_product = 1;
  bool product_is_double = false;

  //Cell pointer to the current working cell
  Cell* current_cell = sub_tree;

  //iterate every cons pair until meet a nil cdr
  while (current_cell != nil) {

    //current_cell is not nil, and it should be a conspair
    if (!current_cell->is_cons()) {
      error_handler("s-expression invalid: cdr must be nil or conspair");
    }

    //pointer to the cell that contains the value to be mulplied
    //here eval could be used against a conspair or a int/double cell
    Cell* value_cell = eval(current_cell->get_car());
	  
    //deal with value_cell, see if it's int or not
    if (value_cell->is_int()) {
      if (product_is_double) {
	double_product *= value_cell->get_int();
      } else {
	int_product *= value_cell->get_int();
      }
    } else if (value_cell->is_double()) {
      //if value_cell is not a double cell
      if (product_is_double) {
	double_product *= value_cell->get_double();
      } else {
	//migrate int_product to double_product and do related clean-ups
	double_product = int_product;
	int_product = 1;
	product_is_double = true;
	      
	double_product *= value_cell->get_double();
      }
    } else {
      if (value_cell != nil) delete value_cell;
      error_handler("s-expression invalid: * operands invalid");
    }
    if (value_cell != nil) delete value_cell;
    //move current_cell forward;
    current_cell = current_cell->get_cdr();
  }
	
  return product_is_double ? (Cell*)new DoubleCell(double_product) : (Cell*)new IntCell(int_product);
}

////////////////////////////DivideOperation///////////////////////////////////
DivideOperation::DivideOperation():Operation("/"){};

Cell* DivideOperation::exec(Cell* const sub_tree)
{
    //error if no operand is supplied
  if (sub_tree == nil) error_handler("divide on zero operand!");
  
  //Cell pointer to the current working cell
  Cell* dividend_cell = sub_tree;
  Cell* divisor_cell = dividend_cell->get_cdr();
  
  //if subtract only has one operand
  if (divisor_cell == nil) {
    if (!dividend_cell->is_cons()) error_handler("s-expression invalid: cdr must be nil or cons!");
    
    Cell* value_cell = eval(dividend_cell->get_car());

    if (value_cell!=nil) {
      if (value_cell->is_int()) {
	if (value_cell->get_int()==0) error_handler("divide by 0");
	return new DoubleCell(1/value_cell->get_int());
      } else if (value_cell->is_double()) {
	if (value_cell->get_double()==0) error_handler("divide by 0");
	return new DoubleCell(1/value_cell->get_double());
      } else {
	//directly delete, for value_cell is ensured to be non nil
	delete value_cell;
	error_handler("divide operand invalid!");
      }
    } else {
      error_handler("divide on nil cell");
    }
  } else {   
    //more than one operand
  
    //temporary results variable
    double result = 0;
    
    if (dividend_cell->is_int()) {
      result = dividend_cell->get_int();
    } else if (dividend_cell->is_double()) {
      result = dividend_cell->get_double();
    }
      
    //iterate every cons pair until meet a nil cdr
    while (divisor_cell != nil) {

      //substrahend_cell is not nil, and it should be a conspair
      if (!divisor_cell->is_cons()) {
	error_handler("s-expression invalid: cdr must be nil or conspair");
      }

      //pointer to the cell that contains the value to be added
      //here eval could be used against a conspair or a int/double cell
      Cell* value_cell = eval(divisor_cell->get_car());
	  
      //deal with value_cell, see if it's int or not
      if (value_cell->is_int()) {
	result /= value_cell->get_int();
      } else if (value_cell->is_double()) {
	  double_result /= value_cell->get_double();
      } else {
	if (value_cell != nil) delete value_cell;
	error_handler("s-expression invalid: / operands invalid");
      }
      if (value_cell != nil) delete value_cell;
      //move divisor_cell forward;
      divisor_cell = divisor_cell->get_cdr();
    }
	
    return (Cell*)new DoubleCell(result);
  }
}

////////////////////////////CeilingOperation///////////////////////////////////
CeilingOperation::CeilingOperation():Operation("ceiling"){};

Cell* CeilingOperation::exec(Cell* const sub_tree)
{
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
}

////////////////////////////FloorOperation///////////////////////////////////
FloorOperation::FloorOperation():Operation("floor"){};

Cell* FloorOperation::exec(Cell* const sub_tree)
{
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
}

////////////////////////////IfOperation///////////////////////////////////
IfOperation::IfOperation():Operation("if"){};

Cell* IfOperation::exec(Cell* const sub_tree)
{
  //temporary Cell pointers;
  Cell* condition = sub_tree;
  if (condition==nil || !condition->is_cons()) error_handler("s-expression invalid: if condition is not a conspair");
  Cell* if_true = condition->get_cdr();
  if (if_true==nil || !if_true->is_cons()) error_handler("s-expression invalid: the true return value is not a cospair");
  Cell* if_false = if_true->get_cdr(); 

  //directly return the second parameter if the third doesn't exist
  if (if_false==nil) {
    return if_true->get_car()->eval();
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
      if(car_value!=nil) delete condition_cell;
      error_handler("s-expression invalid: condition operand invalid to if");
    }

    if(car_value!=nil) delete condition_cell;
	  
    return flag ? eval(if_true->get_car()) : eval(if_false->get_car());
  }
}

////////////////////////////QuoteOperation///////////////////////////////////
QuoteOperation::QuoteOperation():Operation("quote"){};

Cell* QuoteOperation::exec(Cell* const sub_tree)
{
  //return sub_tree's cdr directly, by making a deep copy first
  if (sub_tree==nil || !sub_tree->is_cons()) error_handler("operand for quote invalid");
  if (sub_tree->get_cdr()!=nil) error_handler("operand for quote more than one!");
  return sub_tree->get_car()->copy();
}

////////////////////////////ConsOperation///////////////////////////////////
ConsOperation::ConsOperation():Operation("cons"){};

Cell* ConsOperation::exec(Cell* const sub_tree)
{
  if (sub_tree == nil) error_handler("operand for cons invalid");
  
  Cell* car_tobe = sub_tree;
  Cell* cdr_tobe = sub_tree->get_cdr();

  if (cdr_tobe == nil) error_handler("operand for cons invalid");
  if (cdr_tobe->get_cdr() != nil) error_handler("operand for cons more than two!");
  
  Cell* car_value = eval(car_tobe->get_car());
  Cell* cdr_value = eval(cdr_tobe->get_car());
  Cell* return_cell = new ConsCell(car_value, cdr_value);
  if(car_value!=nil) delete car_value;
  if(cdr_value!=nil) delete cdr_value;
  return return_cell;
}

///////////////////////////CarOperation///////////////////////////////////
CarOperation::CarOperation():Operation("car"){};

Cell* CarOperation::exec(Cell* const sub_tree)
{
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
}

////////////////////////////CdrOperation///////////////////////////////////
CdrOperation::CdrOperation():Operation("cdr"){};

Cell* CdrOperation::exec(Cell* const sub_tree)
{
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
}

////////////////////////////NullpOperation///////////////////////////////////
NullpOperation::NullpOperation():Operation("nullp"){};

Cell* NullpOperation::exec(Cell* const sub_tree)
{
  if (sub_tree == nil) error_handler("zero operand for nullp");
  if (sub_tree->get_cdr() != nil) error_handler("more than one operands for nullp");

  Cell* value_cell = eval(sub_tree->get_car());
  if (value_cell != nil) {
    delete value_cell;
    return new IntCell(0);
  } else {
    return new IntCell(1);
  }
}
