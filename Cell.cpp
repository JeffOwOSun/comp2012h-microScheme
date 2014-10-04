/**
 * \file Cell.cpp
 *
 * A partial dummy implementation of the Cell.hpp interface for
 * example purposes, to support the cons list ADT interface specified
 * in cons.hpp.  Just barely enough is implemented to allow the parser
 * to run.  None of the accessor member functions are implemented.
 *
 * You need to replace this with a real implementation that actually
 * builds a tree data structure and then lets the user access the tree.
 *
 * You don't necessarily need to understand the ugly details of this
 * dummy implementation, which you'll throw away anyhow.
 */

#include "Cell.hpp"
// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.
Cell* const nil = new ConsCell(new IntCell(0));

using namespace std;

//////////////////////////////////////Cell////////////////////////////////////////

bool Cell::is_int() const
{
  return false;
}

bool Cell::is_double() const
{
  return false;
}

bool Cell::is_symbol() const
{
  return false;
}

bool Cell::is_cons() const
{
  return false;
}

int Cell::get_int() const
{
  error_handler("get_int unimplemented");
}

double Cell::get_double() const
{
  error_handler("get_double unimplemented");
}

string Cell::get_symbol() const
{
  error_handler("get_symbol unimplemented");
}

Cell* Cell::get_car() const
{
  error_handler("get_car unimplemented");
}

Cell* Cell::get_cdr() const
{
  error_handler("get_cdr unimplemented");
}

/////////////////////////////////////IntCell//////////////////////////////////////

IntCell::IntCell(const int i): int_m(i) {}

int IntCell::get_int() const
{
  return int_m;
}

bool IntCell::is_int() const
{
  return true;
}

void IntCell::print(ostream& os) const
{
  os << int_m;
}

Cell* IntCell::copy() const
{
  return new IntCell(int_m);
}

Cell* IntCell::eval() const
{
  return copy();
}

////////////////////////////////////DoubleCell////////////////////////////////////

DoubleCell::DoubleCell(const double d): double_m(d) {}

double DoubleCell::get_double() const
{
  return double_m;
}

bool DoubleCell::is_double() const
{
  return true;
}

void DoubleCell::print(ostream& os) const
{
  os << fixed << setprecision(6) << double_m;
}

Cell* DoubleCell::copy() const
{
  return new DoubleCell(double_m);
}

Cell* DoubleCell::eval() const
{
  return copy();
}

///////////////////////////////////SymbolCell/////////////////////////////////////

SymbolCell::SymbolCell(const char* const s)
{
  symbol_m = new char[strlen(s)+1];
  strcpy(symbol_m, s);
}

string SymbolCell::get_symbol() const
{
  return string(symbol_m);
}

bool SymbolCell::is_symbol() const
{
  return true;
}

void SymbolCell::print(ostream& os) const
{
  os << symbol_m;
}

Cell* SymbolCell::copy() const
{
  return new SymbolCell(symbol_m);
}

Cell* SymbolCell::eval() const
{
  return copy();
}

SymbolCell::~SymbolCell()
{
  delete[] symbol_m;
}

///////////////////////////////////ConsCell/////////////////////////////////////

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr): car_m(my_car), cdr_m(my_cdr){}

Cell* ConsCell::get_car() const
{
  return car_m;
}

Cell* ConsCell::get_cdr() const
{
  return cdr_m;
}

bool ConsCell::is_cons() const
{
  return true;
}

void ConsCell::print(ostream& os) const
{
  os << "(";
  const Cell* current_cell = this;
  
  while (current_cell!=nil){
    //get car
    //print car
    current_cell->get_car()->print(os);
    
    //loop to the cdr
    current_cell = current_cell->get_cdr();
    
    if (current_cell != nil) {
      os << " ";
    }
  }
  os << ")";
}

Cell* ConsCell::copy() const
{
  return new ConsCell(car_m, cdr_m);
}

Cell* ConsCell::eval() const
{
  if (this == nil) {
    error_handler("Trying to evaluate nil");
  }
  
  //get car of c
  //using eval will automatically evaluate the subtree, if car(c) is itself a conspair
  Cell* car_value = car_m->eval();
    
  //if car is a symbol cell (it must, otherwise the eval() begins at wrong place)
  if (car_value->is_symbol()){
    //get the symbol
    //case 1: +
    if (car_value->get_symbol() == "+"){
	
      //delete car_value as it's not needed any more
      delete car_value;

      //temporary sums variables
      double double_sum = 0;
      int int_sum = 0;
      bool sum_is_double = false;

      //Cell pointer to the current working cell
      Cell* current_cell = cdr_m;

      //iterate every cons pair until meet a nil cdr
      while (current_cell != nil) {

	//current_cell is not nil, and it should be a conspair
	if (!current_cell->is_cons()) {
	  error_handler("cdr must be nil or conspair");
	}

	//pointer to the cell that contains the value to be added
	//here eval could be used against a conspair or a int/double cell
	Cell* value_cell = current_cell->get_car()->eval();
	  
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
    
    //case 2: ceiling
    else if (car_value->get_symbol() == "ceiling") {
      //delete car_value as it's no longer needed
      delete car_value;

      //current working cell
      Cell* current_cell = cdr_m;

      if (current_cell == nil || !current_cell -> is_cons()) error_handler("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) error_handler("s-expression invalid: ceiling on more than one operands");
	
      //take the ceiling and return
      Cell* returned_value = current_cell->get_car()->eval();
      if (returned_value->is_int()){
	delete returned_value;
	error_handler("s-expression invalid: ceiling on integer!");
      } else if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	if (ceilinged_value < returned_value->get_double()) ++ceilinged_value;
	delete returned_value;
	return new IntCell(ceilinged_value);
      } else {
	if(returned_value!=nil) delete returned_value;
	error_handler("s-expression invalid: ceiling on symbol!");
      }
    }
    //case 3: if
    else if (car_value->get_symbol() == "if") {
      //delete car_value as it's no longer needed
      delete car_value;
	
      //temporary Cell pointers;
      Cell* condition = cdr_m;
      if (condition==nil || !condition->is_cons()) error_handler("s-expression invalid: condition is not a conspair");
      Cell* if_true = condition->get_cdr();
      if (if_true==nil || !if_true->is_cons()) error_handler("s-expression invalid: the true return value is not a cospair");
      Cell* if_false = if_true->get_cdr(); 

      //directly return the second parameter if the third doesn't exist
      if (if_false==nil) {
	return if_true->get_car()->eval();
      } else {
	if (if_false->get_cdr()!=nil) error_handler("s-expression invalid: if operator on more than three operands");
	  
	Cell* condition_cell = condition->get_car()->eval();
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
	  
	return flag ? if_true->get_car()->eval() : if_false->get_car()->eval();
      }
    }
    
    else {
      //delete car_value as it's no longer needed
      delete car_value;
	
      error_handler("s-expression invalid: operator not one of +, ceiling or if");
    }
  } else {
    //delete car_value as it's no longer needed
    if(car_value!=nil) delete car_value;
	
    //value_car is not a symbol cell
    error_handler("s-expression invalid: the first element of the tree/subtree is not a proper operator");
  }

  
}

ConsCell::~ConsCell()
{
  delete car_m;
  delete cdr_m;
}
