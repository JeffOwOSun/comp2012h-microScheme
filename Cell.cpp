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
Cell* const nil = new ConsCell(nil, nil);

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

bool Cell::is_procedure() const
{
  return false;
}

int Cell::get_int() const throw(UnimplementedError)
{
  throw UnimplementedError("get_int");
}

double Cell::get_double() const throw(UnimplementedError)
{
  throw UnimplementedError("get_double");
}

string Cell::get_symbol() const throw(UnimplementedError)
{
  throw UnimplementedError("get_symbol");
}

Cell* Cell::get_car() const throw(UnimplementedError)
{
  throw UnimplementedError("get_car");
}

Cell* Cell::get_cdr() const throw(UnimplementedError)
{
  throw UnimplementedError("get_cdr");
}

Cell* Cell::get_formals() const throw(UnimplementedError)
{
  throw UnimplementedError("get_formals");
}

Cell* Cell::get_body() const throw(UnimplementedError)
{
  throw UnimplementedError("get_body");
}

Cell* Cell::add(Cell* const c) const throw(UnimplementedError, OperandInvalidError)
{
  throw UnimplementedError("add"); 
}

Cell* Cell::subtract(Cell* const c) const throw(UnimplementedError, OperandInvalidError)
{
  throw UnimplementedError("subtract");
}

Cell* Cell::multiply(Cell* const c) const throw(UnimplementedError, OperandInvalidError)
{
  throw UnimplementedError("multiply");
}

Cell* Cell::divide_by(Cell* const c) const throw(UnimplementedError, OperandInvalidError, DivideByZeroError)
{
  throw UnimplementedError("divide_by");
}

bool Cell::smaller_than(Cell* const c) const throw(UnimplementedError, OperandInvalidError)
{
  throw UnimplementedError("smaller_than");
}

bool Cell::larger_than(Cell* const c) const throw(UnimplementedError, OperandInvalidError)
{
  throw UnimplementedError("larger_than");
}

Cell* Cell::get_not() const throw(UnimplementedError)
{
  throw UnimplementedError("get_not");
}

Cell* Cell::apply(Cell* const args) const
{
  throw UnimplementedError("apply");
}

Cell* Cell::eval() const
{
  throw UnimplementedError("eval");
}

Cell::~Cell(){}

/////////////////////////////////////IntCell//////////////////////////////////////

IntCell::IntCell(const int i): int_m(i) {}

int IntCell::get_int() const throw ()
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
  if (this == nil) return nil;
  return new IntCell(int_m);
}

Cell* IntCell::add (Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new IntCell(get_int() + c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() + c->get_double());
  } else throw OperandInvalidError("add");
}
Cell* IntCell::subtract (Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new IntCell(get_int() - c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() - c->get_double());
  } else throw OperandInvalidError("subtract");

}
Cell* IntCell::multiply (Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new IntCell(get_int() * c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() * c->get_double());
  } else throw OperandInvalidError("multiply");
}
Cell* IntCell::divide_by (Cell* const c) const throw (DivideByZeroError, OperandInvalidError)
{
  if (c->is_int()) {
    if (c->get_int() == 0) throw DivideByZeroError();
    return new IntCell(get_int() / c->get_int());
  } else if (c->is_double()) {
    if (c->get_double() == 0) throw DivideByZeroError();
    return new DoubleCell(get_int() / c->get_double());
  } else throw OperandInvalidError("divide_by");
}
bool IntCell::smaller_than(Cell* const c) const throw(OperandInvalidError)
{
  if (c->is_int()) {
    return get_int() < c->get_int();
  } else if (c->is_double()) {
    return get_int() < c->get_double();
  } else throw OperandInvalidError("smaller_than");
}

bool IntCell::larger_than(Cell* const c) const throw(OperandInvalidError)
{
  if (c->is_int()) {
    return get_int() > c->get_int();
  } else if (c->is_double()) {
    return get_int() > c->get_double();
  } else throw OperandInvalidError ("larger_than");
}

Cell* IntCell::get_not() const throw()
{
  if (get_int() == 0) {
    return new IntCell(1);
  } else return new IntCell(0);
}

Cell* IntCell::eval() const
{
  return copy();
}
////////////////////////////////////DoubleCell////////////////////////////////////

DoubleCell::DoubleCell(const double d): double_m(d) {}

double DoubleCell::get_double() const throw ()
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
  if (this == nil) return nil;
  return new DoubleCell(double_m);
}

Cell* DoubleCell::add(Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new DoubleCell(get_double() + c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() + c->get_double());
  } else throw OperandInvalidError("add");
}
Cell* DoubleCell::subtract(Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new DoubleCell(get_double() - c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() - c->get_double());
  } else throw OperandInvalidError("subtract");

}
Cell* DoubleCell::multiply(Cell* const c) const throw (OperandInvalidError)
{
  if (c->is_int()) {
    return new DoubleCell(get_double() * c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() * c->get_double());
  } else throw OperandInvalidError("multiply");
}
Cell* DoubleCell::divide_by(Cell* const c) const throw (DivideByZeroError, OperandInvalidError)
{
  if (c->is_int()) {
    if (c->get_int() == 0) throw DivideByZeroError();
    return new DoubleCell(get_double() / c->get_int());
  } else if (c->is_double()) {
    if (c->get_double() == 0) throw DivideByZeroError();
    return new DoubleCell(get_double() / c->get_double());
  } else throw OperandInvalidError("divide_by");
}
bool DoubleCell::smaller_than(Cell* const c) const throw(OperandInvalidError)
{
  if (c->is_int()) {
    return get_double() < c->get_int();
  } else if (c->is_double()) {
    return get_double() < c->get_double();
  } else throw OperandInvalidError("smaller_than");
}

bool DoubleCell::larger_than(Cell* const c) const throw(OperandInvalidError)
{
  if (c->is_int()) {
    return get_double() > c->get_int();
  } else if (c->is_double()) {
    return get_double() > c->get_double();
  } else throw OperandInvalidError ("larger_than");
}

Cell* DoubleCell::get_not() const throw()
{
  if (get_double() == 0) {
    return new IntCell(1);
  } else return new IntCell(0);  
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

string SymbolCell::get_symbol() const throw()
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
  if (this == nil) return nil;
  return new SymbolCell(symbol_m);
}

SymbolCell::~SymbolCell()
{
  delete[] symbol_m;
}

Cell* SymbolCell::eval() const
{
  std::string expr = get_symbol();
  //first lookup local
  if (definition_stack.back().count(expr)!=0) {
    return definition_stack.back().at(expr)->copy();
  //then lookup global
  } else if (definition_stack.size()>1 && definition_stack.front().count(expr)!=0) {
    return definition_stack.front().at(expr)->copy();
  } else throw runtime_error("attempt to reference an undefined symbol \""+expr+"\"");
}

///////////////////////////////////ConsCell/////////////////////////////////////

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr): car_m(my_car), cdr_m(my_cdr){}

Cell* ConsCell::get_car() const throw()
{
  return car_m;
}

Cell* ConsCell::get_cdr() const throw()
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
  if (this == nil) return nil;
  return new ConsCell(car_m->copy(), cdr_m->copy());
}

Cell* ConsCell::get_not() const throw()
{
  return new IntCell(0);
}

Cell* ConsCell::eval() const
{
  if (this == nil) throw runtime_error("root of tree is nil");
  //Need the following line because the codes are migrated from eval.cpp
  const Cell* const c = this;
  
  //allow only the situation that
  //1. car of root is a symbol cell
  //2. car of root is a cons cell, and its result is a procedure cell

  //if the first car of the tree is evaluated to be a ProcedureCell
  //apply the rest of the tree to the procedure cell
  if (get_car()->is_cons()){
    //case 2
    Cell* returned_car_cell = get_car()->eval();
    Cell* value_to_return;
    //directly call apply. Cell will handle error if returned car cell is not a procedure cell
    try {
      value_to_return = returned_car_cell -> apply(c->get_cdr());
    } catch (...) {
      safe_delete(returned_car_cell);
      throw;
    }
    safe_delete(returned_car_cell);
    return value_to_return;
  } else if (get_car()->is_symbol()){
    //case 1
    //get the operator
    std::string operation = get_car()->get_symbol();
    
    Cell* sub_tree = c->get_cdr();
    
//////////////////////////////////////+//////////////////////////////////////////    
    if (operation == "+") {
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      Cell* sum= new IntCell(0);
  
      //iterate every cons pair until meet a nil cdr
      while (current_cell != nil) {

	//current_cell is not nil, and it should be a conspair
	if (!current_cell->is_cons()) {
	  throw runtime_error("cdr must be nil or conspair");
	}

	//pointer to the cell that contains the value to be added
	//here eval could be used against a conspair or a int/double cell
	Cell* value_cell = current_cell->get_car()->eval();

	if (value_cell==nil)throw runtime_error("add on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  safe_delete(value_cell);
	  throw runtime_error("add operand invalid");
	}
    
	Cell* result = sum->add(value_cell);
	safe_delete(sum);
	safe_delete(value_cell);
	sum = result;
    
	//move current_cell forward;
	current_cell = current_cell->get_cdr();
      }
    
      return sum;
////////////////////////////////////-////////////////////////////////////////////      
    } else if (operation == "-") {

      //error if no operand is supplied
      if (sub_tree == nil) throw runtime_error("subtract on zero operand!");
  
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      //Value Cell that stores minuend
      Cell* minuend_cell;
    
      //if subtract only has one operand
      if (sub_tree->get_cdr() == nil) {
	if (!current_cell->is_cons()) throw runtime_error("s-expression invalid: cdr must be nil or cons!");
    
	Cell* value_cell = current_cell->get_car()->eval();

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(-value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(-value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    safe_delete(value_cell);
	    throw runtime_error("subtract operand invalid!");
	  }
	} else {
	  throw runtime_error("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	minuend_cell = current_cell->get_car()->eval();
	if (minuend_cell==nil) throw runtime_error("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = current_cell->get_car()->eval();
      
	  if (value_cell==nil) throw runtime_error("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    safe_delete(value_cell);
	    throw runtime_error("subtract operand invalid");
	  }
      
	  Cell* result_cell = minuend_cell->subtract(value_cell);
	  safe_delete(minuend_cell);
	  safe_delete(value_cell);
	  minuend_cell = result_cell;

	  current_cell = current_cell->get_cdr();
	}

	return minuend_cell;
      }
//////////////////////////////////////*//////////////////////////////////////////
    } else if (operation == "*") {
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      Cell* product = new IntCell(1);

      //iterate every cons pair until meet a nil cdr
      while (current_cell != nil) {

	//current_cell is not nil, and it should be a conspair
	if (!current_cell->is_cons()) {
	  throw runtime_error("cdr must be nil or conspair");
	}

	//pointer to the cell that contains the value to be added
	//here eval could be used against a conspair or a int/double cell
	Cell* value_cell = current_cell->get_car()->eval();

	if (value_cell==nil) throw runtime_error("multiply on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  safe_delete(value_cell);
	  throw runtime_error("multiply operand invalid");
	}
          
	Cell* result = product->multiply(value_cell);
	safe_delete(product);
	safe_delete(value_cell);
	product = result;
   
	//move current_cell forward;
	current_cell = current_cell->get_cdr();
      }
    
      return product;
//////////////////////////////////// / ///////////////////////////////////////////
    } else if (operation == "/") {
      //error if no operand is supplied
      if (sub_tree == nil) throw runtime_error("division on zero operand!");
      
      //Cell pointer to the current working cell
      Cell* current_cell = sub_tree;
      //Value Cell that stores minuend
      Cell* dividend_cell;
    
      //if subtract only has one operand
      if (sub_tree->get_cdr() == nil) {
	if (!current_cell->is_cons()) throw runtime_error("s-expression invalid: cdr must be nil or cons!");
    
	Cell* value_cell = current_cell->get_car()->eval();

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(1/value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(1/value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    safe_delete(value_cell);
	    throw runtime_error("subtract operand invalid!");
	  }
	} else {
	  throw runtime_error("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	dividend_cell = current_cell->get_car()->eval();
	if (dividend_cell==nil) throw runtime_error("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = current_cell->get_car()->eval();
      
	  if (value_cell==nil) throw runtime_error("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    safe_delete(value_cell);
	    throw runtime_error("subtract operand invalid");
	  }
      
	  Cell* result_cell = dividend_cell->divide_by(value_cell);
	  safe_delete(dividend_cell);
	  safe_delete(value_cell);
	  dividend_cell = result_cell;

	  current_cell = current_cell->get_cdr();
	}
	
	return dividend_cell;
      }
//////////////////////////////////////ceiling//////////////////////////////////////////      
    } else if (operation == "ceiling") {
      //current working cell
      Cell* current_cell = sub_tree;

      if (current_cell == nil || !current_cell -> is_cons()) throw runtime_error("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) throw runtime_error("s-expression invalid: ceiling on more than one operands");
    
      //take the ceiling and return
      Cell* returned_value = current_cell->get_car()->eval();
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	if (ceilinged_value < returned_value->get_double()) ++ceilinged_value;
	safe_delete(returned_value);
	return new IntCell(ceilinged_value);
      } else {
	safe_delete(returned_value);
	throw runtime_error("s-expression invalid: ceiling operand invalid!");
      }
/////////////////////////////////////floor///////////////////////////////////////////      
    } else if (operation == "floor") {
      //current working cell
      Cell* current_cell = sub_tree;

      if (current_cell == nil || !current_cell -> is_cons()) throw runtime_error("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) throw runtime_error("s-expression invalid: ceiling on more than one operands");
    
      //take the floor and return
      Cell* returned_value = current_cell->get_car()->eval();
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	safe_delete(returned_value);
	return new IntCell(ceilinged_value);
      } else {
	safe_delete(returned_value);
	throw runtime_error("s-expression invalid: floor operand invalid");
      }
///////////////////////////////////////if/////////////////////////////////////////      
    } else if (operation == "if") {
      //temporary Cell pointers;
      Cell* condition = sub_tree;
      if (condition==nil || !condition->is_cons()) throw runtime_error("s-expression invalid: if condition is not a conspair");
      Cell* if_true = condition->get_cdr();
      if (if_true==nil || !if_true->is_cons()) throw runtime_error("s-expression invalid: the true return value is not a cospair");
      Cell* if_false = if_true->get_cdr(); 

      //directly return the second parameter if the third doesn't exist
      if (if_false==nil) {
	return if_true->get_car()->eval();
      } else {
	if (if_false->get_cdr()!=nil) throw runtime_error("s-expression invalid: if operator on more than three operands");
      
	Cell* condition_cell = condition->get_car()->eval();
	bool flag = false;
      
	//retrieve values according to their types
	if (condition_cell==nil){
	  flag = false;
	} else if (condition_cell->is_int()){
	  flag = condition_cell->get_int() ? true : false;
	} else if (condition_cell->is_double()) {
	  flag = condition_cell->get_double() ? true : false;
	} else if (condition_cell->is_symbol()) {
	  flag = condition_cell->get_symbol()!="" ? true : false;
	} else {
	  safe_delete(condition_cell);
	  throw runtime_error("s-expression invalid: condition operand invalid to if");
	}

	safe_delete(condition_cell);
      
	return flag ? if_true->get_car()->eval() : if_false->get_car()->eval();
      }
//////////////////////////////////////quote//////////////////////////////////////////      
    } else if (operation == "quote") {
      //return sub_tree's cdr directly, by making a deep copy first
      if (sub_tree==nil || !sub_tree->is_cons()) throw runtime_error("operand for quote invalid");
      if (sub_tree->get_cdr()!=nil) throw runtime_error("operand for quote more than one!");
      return sub_tree->get_car()->copy();
///////////////////////////////////////cons/////////////////////////////////////////
    } else if (operation == "cons") {
      if (sub_tree == nil) throw runtime_error("operand for cons invalid");
      //ConsCell pointers. 
      Cell* car_tobe = sub_tree;
      Cell* cdr_tobe = sub_tree->get_cdr();

      if (cdr_tobe == nil) throw runtime_error("operand for cons invalid");
      if (cdr_tobe->get_cdr() != nil) throw runtime_error("operand for cons more than two!");
  
      Cell* car_value = car_tobe->get_car()->eval();
      Cell* cdr_value = cdr_tobe->get_car()->eval();

      Cell* return_cell = new ConsCell(car_value, cdr_value);
            
      return return_cell;
//////////////////////////////////////car//////////////////////////////////////////      
    } else if (operation == "car") {
      if (sub_tree == nil) throw runtime_error("zero operand for car");
      if (sub_tree->get_cdr() != nil) throw runtime_error("more than one operands for car");
      //retrieve the cell upon which car should be taken
      Cell* value_cell = sub_tree->get_car()->eval();
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_car = value_cell->get_car()->copy();
	  safe_delete(value_cell);
	  return value_car;
	} else {
	  safe_delete(value_cell); 
	  throw runtime_error("car on non-cons cell");
	}
      } else {
	throw runtime_error ("car on nil");
      }
///////////////////////////////////////cdr/////////////////////////////////////////      
    } else if (operation == "cdr") {
      if (sub_tree == nil) throw runtime_error("zero operand for cdr");
      if (sub_tree->get_cdr() != nil) throw runtime_error("more than one operands for cdr");
      //retrieve the cell upon which cdr should be taken
      Cell* value_cell = sub_tree->get_car()->eval();
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_cdr = value_cell->get_cdr()->copy();
	  safe_delete(value_cell);
	  return value_cdr;
	} else {
	  safe_delete(value_cell); 
	  throw runtime_error("cdr on non-cons cell");
	}
      } else {
	throw runtime_error ("cdr on nil");
      }
////////////////////////////////////////nullp////////////////////////////////////////      
    } else if (operation == "nullp") {
      if (sub_tree == nil) throw runtime_error("zero operand for nullp");
      if (sub_tree->get_cdr() != nil) throw runtime_error("more than one operands for nullp");

      Cell* value_cell = sub_tree->get_car()->eval();
      if (value_cell != nil) {
        safe_delete(value_cell);
        return new IntCell(0);
      } else {
        return new IntCell(1);
      }
////////////////////////////////////////define////////////////////////////////////////      
    } else if (operation == "define") {
      if (sub_tree == nil || sub_tree->get_cdr() == nil || sub_tree->get_cdr()->get_cdr()!=nil) throw OperandNumberMismatchError("define","2");

      //retrieve the key
      Cell* key_cell = sub_tree->get_car()->copy();
      try {
        if (key_cell == nil || !key_cell->is_symbol()) throw OperandInvalidError("define");
        //look up the map if the key prexists
        if (definition_stack.back().count(key_cell->get_symbol())!=0) throw runtime_error(key_cell->get_symbol()+" already exists in this scope!");
      } catch (...) {
        safe_delete(key_cell);
        throw;
      }
      //retrieve the defintion
      Cell* definition_cell = sub_tree->get_cdr()->get_car()->eval();
      //if (definition_cell == nil) throw OperandInvalidError("define");     
      //store the key and the evaluated cell to the map
      definition_stack.back()[key_cell->get_symbol()] = definition_cell;
      return nil;
////////////////////////////////////////<////////////////////////////////////////      
    } else if (operation == "<") {
      //for zero operand
      if (sub_tree == nil) return new IntCell(1);

      Cell* current_cell = sub_tree;
      //while there's more than one operand left
      Cell* result_cell;
      while (current_cell->get_cdr()!=nil) {
	if (!(result_cell = current_cell->get_car()->eval()) -> smaller_than(current_cell -> get_cdr() -> get_car()->eval())) {
	  safe_delete(result_cell);
	  return new IntCell(0); 
	}
	safe_delete(result_cell);
	current_cell = current_cell->get_cdr();
      }
      //directly return 1, including the case where only one operand is supplied
      return new IntCell(1);
////////////////////////////////////////not////////////////////////////////////////      
    } else if (operation == "not") {
      //operand number check. throw error
      if (sub_tree == nil || sub_tree->get_cdr()!=nil) throw OperandNumberMismatchError("not","exactly 1");

      Cell* result_cell = sub_tree->get_car()->eval();
      Cell* not_cell = result_cell->get_not();
      safe_delete(result_cell);
      return not_cell;
////////////////////////////////////////print////////////////////////////////////////      
    } else if (operation == "print") {
      //limit to one operand
      if (sub_tree == nil || sub_tree->get_cdr() != nil) throw OperandNumberMismatchError("print","exactly 1");

      Cell* result_cell = sub_tree->get_car()->eval();
      result_cell->print(cout);
      cout<<endl;
      safe_delete(result_cell);
      return nil;
////////////////////////////////////////eval////////////////////////////////////////      
    } else if (operation == "eval") {
      //limit to one operand
      if (sub_tree == nil || sub_tree -> get_cdr() != nil) throw OperandNumberMismatchError("eval","exactly 1");

      Cell* car_result = sub_tree->get_car()->eval();
      Cell* eval_result = car_result->eval();
      safe_delete(car_result);
      return eval_result;
////////////////////////////////////////lambda////////////////////////////////////////
    } else if (operation == "lambda") {
      //assert two or more operands
      if (sub_tree == nil || sub_tree->get_cdr() == nil) throw OperandNumberMismatchError("lambda","2 or more");

      //check the formals are valid
      for (Cell* i = sub_tree->get_car(); i != nil; i=i->get_cdr()){
	if (!i->get_car()->is_symbol()) throw OperandInvalidError("lambda");
      }

      //car of cdr as formals
      //cdr of cdr directly as body
      return new ProcedureCell(sub_tree->get_car()->copy(), sub_tree->get_cdr()->copy());
////////////////////////////////////////apply////////////////////////////////////////
    } else if (operation == "apply") {
      //assert two operands
      if (sub_tree == nil || sub_tree->get_cdr() == nil || sub_tree->get_cdr()->get_cdr() != nil) throw OperandNumberMismatchError("apply", "exactly 2");

      //evaluate the first operand only once to get the func
      Cell* func = nil;
      Cell* param = nil;
      Cell* apply_result = nil;

      func = sub_tree->get_car()->eval();
      try {
	param = sub_tree->get_cdr()->get_car()->eval();
	try {
	  apply_result=func->apply(param);
	} catch (...) {
	  safe_delete(param);
	  throw;
	}
	safe_delete(param);
      } catch (...) {
	safe_delete(func);
	throw;
      }
      safe_delete(func);
      
      return apply_result;
    
////////////////////////////////////////lookup dictionary////////////////////////////////////////       
    } else {
      Cell* func = nil;
      Cell* apply_result = nil;
      try {
	//eval will help look up the dictionary, as defined in SymbolCell::eval()
	//It will throw an error if the required expression is nowhere to look up
	func = get_car()->eval();
	try {
	  //try to apply the function
	  apply_result = func->apply(sub_tree);
	} catch (...) {
	  safe_delete(func);
	  throw;
	}
	//normal clean up
	safe_delete(func);
      } catch (...) {
	throw;
      }
      return apply_result;
    }
  } else {
    throw runtime_error("root of tree invalid");
  }
}

ConsCell::~ConsCell()
{
  safe_delete(car_m);
  safe_delete(cdr_m);
}

///////////////////////////////////ProcedureCell/////////////////////////////////////
ProcedureCell::ProcedureCell(Cell* const my_formals, Cell* const my_body): formals_m(my_formals), body_m(my_body){}

Cell* ProcedureCell::get_formals() const throw()
{
  return formals_m;
}

Cell* ProcedureCell::get_body() const throw()
{
  return body_m;
}

bool ProcedureCell::is_procedure() const throw()
{
  return true;
}

void ProcedureCell::print(std::ostream& os) const
{
  os << "#<function>";
}

Cell* ProcedureCell::copy() const
{
  return new ProcedureCell(formals_m->copy(), body_m->copy());
}

Cell* ProcedureCell::get_not() const throw()
{
  return new IntCell(0);
}

Cell* ProcedureCell::apply(Cell* const args) const
{
  //define the local map of variables
  map<string,Cell*> my_map;
  try {
    //iterate each formal, define the local map
    const Cell* my_arg = args;
    for (const Cell* my_formal = get_formals(); my_formal!=nil; my_formal = my_formal->get_cdr()){
      if (my_arg == nil) throw runtime_error("lambda function operand number not enough");
      //retrieve the formal name
      string formal_name = my_formal->get_car()->get_symbol();
      //retrieve the definition. A copy is made to ensure uniform deletion of the map is legal
      Cell* arg_def = my_arg->get_car()->eval();
      try {
	//put them into the map
	if (my_map.count(formal_name)!=0) throw runtime_error("duplicate formal name: "+formal_name);
	my_map[formal_name]=arg_def;
      } catch (...) {
	safe_delete(arg_def);
	throw;
      }
      my_arg = my_arg -> get_cdr();
    }
    if (my_arg != nil) throw runtime_error("too many lambda function operands");
  } catch (...) {
    //release the allocated memory spaces
    for (map<string, Cell*>::iterator my_iter = my_map.begin();my_iter != my_map.end(); ++my_iter){
      safe_delete(my_iter -> second);
    }
    throw;
  }
  //push the local map into the stack
  definition_stack.push_back(my_map);
  Cell* eval_result = nil;
  try {
    //start evaluating the functions
    
    //retrieve each line
    for (const Cell* my_body = body_m; my_body!=nil; my_body = my_body->get_cdr()){
      //safe delete the result that remains from last time of loop
      safe_delete(eval_result);
      //evaluate
      try {
	eval_result = my_body->get_car()->eval();
      } catch (...) {
	safe_delete(eval_result);
	throw;
      }
    }
  } catch (...) {
    //pop the stack and clean up
    my_map = definition_stack.back();
    for (map<string, Cell*>::iterator my_iter = my_map.begin();my_iter != my_map.end(); ++my_iter){
      safe_delete(my_iter -> second);
    }
    definition_stack.pop_back();
    throw;
  }
  
  //normal exit
  //pop the stack and clean up
  my_map = definition_stack.back();
  for (map<string, Cell*>::iterator my_iter = my_map.begin();my_iter != my_map.end(); ++my_iter){
    safe_delete(my_iter -> second);
  }
  definition_stack.pop_back();

  //return the last result
  return eval_result;
}

Cell* ProcedureCell::eval() const
{
  throw UnimplementedError("eval");
}

ProcedureCell::~ProcedureCell()
{
  safe_delete(formals_m);
  safe_delete(body_m);
}

deque<map<string,Cell*> > stack_initialize()
{
  deque<map<string,Cell*> > my_dq;
  map<string,Cell*> my_map;
  //do something with my_map if necessary
  my_dq.push_back(my_map);
  return my_dq;
}

std::deque<std::map<std::string, Cell*> > definition_stack = stack_initialize();
