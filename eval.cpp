/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */

#include "eval.hpp"
#include <map>

/**
 * \brief The map container used by eval to support define
 */
map <string, Cell*> definition_map;

/**
 * \brief The evaluation function that calculates the parsed s-expression tree
 * \param c A constant pointer to a Cell instance, which is the root of the tree to be computed. Root of tree must not be nil, or error occurs.
 * \return A pointer to the Cell containing the final answer. This Cell is always a temporary Cell that should be disposed of whenever it's no longer needed.
 */
Cell* eval(Cell* const c)
{
  if (c == nil) {
    throw runtime_error("root of tree is nil");
  }

  if (c->is_int() || c->is_double()) return c->copy();

  //look up dictionary for symbol cells
  if (c->is_symbol()) {
    string expr = c->get_symbol();
    if (definition_map.count(expr) != 0) {
      return definition_map.at(expr)->copy();
    } else throw runtime_error("attempt to reference an undefined symbol \""+expr+"\"");
  }

  //retrieve the evaluated result of car
  //only evaluate the car when it's a conspair
  //This is especially important for a symbolcell car
  //We don't want to look up the dictionary for our operator
  //as it will report "symbol undefined" error
  Cell* returned_car_cell = c->get_car()->is_cons() ? eval(c->get_car()) : c->get_car()->copy();
  if (returned_car_cell == nil) throw runtime_error("invalid s-expression: root of tree is nil");
  
  if ((*returned_car_cell).is_symbol()){
    //get the operator
    std::string operation = (*returned_car_cell).get_symbol();
    delete returned_car_cell;
    
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
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell==nil)throw runtime_error("add on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  delete value_cell;
	  throw runtime_error("add operand invalid");
	}
    
	Cell* result = sum->add(value_cell);
	delete sum;
	delete value_cell;
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
    
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(-value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(-value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    delete value_cell;
	    throw runtime_error("subtract operand invalid!");
	  }
	} else {
	  throw runtime_error("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	minuend_cell = eval(current_cell->get_car());
	if (minuend_cell==nil) throw runtime_error("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = eval(current_cell->get_car());
      
	  if (value_cell==nil) throw runtime_error("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    delete value_cell;
	    throw runtime_error("subtract operand invalid");
	  }
      
	  Cell* result_cell = minuend_cell->subtract(value_cell);
	  delete minuend_cell;
	  delete value_cell;
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
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell==nil) throw runtime_error("multiply on nil");
	if (value_cell->is_cons() || value_cell->is_symbol()){
	  delete value_cell;
	  throw runtime_error("multiply operand invalid");
	}
          
	Cell* result = product->multiply(value_cell);
	delete product;
	delete value_cell;
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
    
	Cell* value_cell = eval(current_cell->get_car());

	if (value_cell!=nil) {
	  if (value_cell->is_int()) {
	    return new IntCell(1/value_cell->get_int());
	  } else if (value_cell->is_double()) {
	    return new DoubleCell(1/value_cell->get_double());
	  } else {
	    //directly delete, for value_cell is ensured to be non nil
	    delete value_cell;
	    throw runtime_error("subtract operand invalid!");
	  }
	} else {
	  throw runtime_error("subtract on nil cell");
	}
      } else {   
	// subtract with two operands or more
    
	dividend_cell = eval(current_cell->get_car());
	if (dividend_cell==nil) throw runtime_error("subtract on nil cell");
	current_cell = current_cell->get_cdr();

	while (current_cell != nil) {
	  Cell* value_cell = eval(current_cell->get_car());
      
	  if (value_cell==nil) throw runtime_error("subtract on nil");
	  if (value_cell->is_cons() || value_cell->is_symbol()){
	    delete value_cell;
	    throw runtime_error("subtract operand invalid");
	  }
      
	  Cell* result_cell = dividend_cell->divide_by(value_cell);
	  delete dividend_cell;
	  delete value_cell;
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
      Cell* returned_value = eval(current_cell->get_car());
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	if (ceilinged_value < returned_value->get_double()) ++ceilinged_value;
	delete returned_value;
	return new IntCell(ceilinged_value);
      } else {
	if(returned_value!=nil) delete returned_value;
	throw runtime_error("s-expression invalid: ceiling operand invalid!");
      }
/////////////////////////////////////floor///////////////////////////////////////////      
    } else if (operation == "floor") {
      //current working cell
      Cell* current_cell = sub_tree;

      if (current_cell == nil || !current_cell -> is_cons()) throw runtime_error("s-expression invalid: invalid ceiling operand!");

      if (current_cell->get_cdr()!=nil) throw runtime_error("s-expression invalid: ceiling on more than one operands");
    
      //take the floor and return
      Cell* returned_value = eval(current_cell->get_car());
      if (returned_value->is_double()){
	int ceilinged_value = int(returned_value->get_double());
	delete returned_value;
	return new IntCell(ceilinged_value);
      } else {
	if(returned_value!=nil) delete returned_value;
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
	return eval(if_true->get_car());
      } else {
	if (if_false->get_cdr()!=nil) throw runtime_error("s-expression invalid: if operator on more than three operands");
      
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
	  throw runtime_error("s-expression invalid: condition operand invalid to if");
	}

	if(condition_cell!=nil) delete condition_cell;
      
	return flag ? eval(if_true->get_car()) : eval(if_false->get_car());
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
  
      Cell* car_value = eval(car_tobe->get_car());
      Cell* cdr_value = eval(cdr_tobe->get_car());

      Cell* return_cell = new ConsCell(car_value, cdr_value);
            
      return return_cell;
//////////////////////////////////////car//////////////////////////////////////////      
    } else if (operation == "car") {
      if (sub_tree == nil) throw runtime_error("zero operand for car");
      if (sub_tree->get_cdr() != nil) throw runtime_error("more than one operands for car");
      //retrieve the cell upon which car should be taken
      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_car = value_cell->get_car()->copy();
	  delete value_cell;
	  return value_car;
	} else {
	  delete value_cell; 
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
      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
	if (value_cell->is_cons()) {
	  Cell* value_cdr = value_cell->get_cdr()->copy();
	  delete value_cell;
	  return value_cdr;
	} else {
	  delete value_cell; 
	  throw runtime_error("cdr on non-cons cell");
	}
      } else {
	throw runtime_error ("cdr on nil");
      }
////////////////////////////////////////nullp////////////////////////////////////////      
    } else if (operation == "nullp") {
      if (sub_tree == nil) throw runtime_error("zero operand for nullp");
      if (sub_tree->get_cdr() != nil) throw runtime_error("more than one operands for nullp");

      Cell* value_cell = eval(sub_tree->get_car());
      if (value_cell != nil) {
        delete value_cell;
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
        if (definition_map.count(key_cell->get_symbol())!=0) throw runtime_error(key_cell->get_symbol()+" already exists!");
      } catch (...) {
        delete key_cell;
        throw;
      }
      //retrieve the defintion
      Cell* definition_cell = eval(sub_tree->get_cdr()->get_car());
      //if (definition_cell == nil) throw OperandInvalidError("define");     
      //store the key and the evaluated cell to the map
      definition_map[key_cell->get_symbol()] = definition_cell;
      return nil;
////////////////////////////////////////<////////////////////////////////////////      
    } else if (operation == "<") {
      //for zero operand
      if (sub_tree == nil) return new IntCell(1);

      Cell* current_cell = sub_tree;
      //while there's more than one operand left
      while (current_cell->get_cdr()!=nil) {
	if (!eval(current_cell->get_car()) -> smaller_than(eval(current_cell -> get_cdr() -> get_car()))) {
	  return new IntCell(0); 
	}
	current_cell = current_cell->get_cdr();
      }
      //directly return 1, including the case where only one operand is supplied
      return new IntCell(1);

////////////////////////////////////////lookup dictionary////////////////////////////////////////       
    } else if (definition_map.count(operation)!=0) {
      //retrieve and make a copy of the definition
      return definition_map.at(operation)->copy();
/////////////////////////////////////invalid operation///////////////////////////////////////////      
    } else {    
      //If this line is executed, it means that no matching operation found
      throw runtime_error("Invalid s-expression: unexpected operator \""+operation+"\"");
    }
  } else {
    if (returned_car_cell!=nil) delete returned_car_cell;
    throw runtime_error("Invalid s-expression: root of subtree is not evaluated to be a symbol cell");
  }  
}


