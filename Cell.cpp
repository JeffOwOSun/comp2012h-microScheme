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
Cell* const nil = new Cell(0);

using namespace std;

Cell::Cell(const int i):tag_m(type_int),int_m(i)
{}

Cell::Cell(const double d):tag_m(type_double), double_m(d)
{}

Cell::Cell(const char* const s)
{
  tag_m = type_symbol;
  symbol_m = new char[strlen(s)+1];
  strcpy (symbol_m, s);
  return;
}

Cell::Cell(Cell* const my_car, Cell* const my_cdr):tag_m(type_conspair)
{
  conspair_m.car_m = my_car;
  conspair_m.cdr_m = my_cdr;
}

bool Cell::is_int() const
{
  return tag_m == type_int;
}

bool Cell::is_double() const
{
  return tag_m == type_double;
}

bool Cell::is_symbol() const
{
  return tag_m == type_symbol;
}

bool Cell::is_cons() const
{
  return tag_m == type_conspair;
}

int Cell::get_int() const
{
  if (is_int()) {
    return int_m;
  } else {
    cerr << "In function Cell::get_int(), the corresponding Cell instance is not a int Cell!" << endl;
    exit(1);
  }
}

double Cell::get_double() const
{
  if (is_double()) {
    return double_m;
  } else {
    cerr << "In function Cell::get_double(), the corresponding Cell instance is not a double Cell!" << endl;
    exit(1);
  }
}

string Cell::get_symbol() const
{
  if (is_symbol()) {
    return string(symbol_m);
  } else {
    cerr << "In function Cell::get_symbol(), the corresponding Cell instance is not a symbol Cell!" << endl;
    exit(1);
  }
}

Cell* Cell::get_car() const
{
  if (is_cons()) {
    return conspair_m.car_m;
  } else {
    cerr << "In function Cell::get_car(), the corresponding Cell is not a cons Cell!" << endl;
    exit(1);
  }
}

Cell* Cell::get_cdr() const
{
  if (is_cons()) {
    return conspair_m.cdr_m;
  } else {
    cerr << "In function Cell::get_cdr(), the corresponding Cell is not a cons Cell!" << endl;
    exit(1);
  }
}

void Cell::print(ostream& os) const
{
  if (this == nil) {
    error_handler("Trying to print nil!");
  }
  
  if (is_int() || is_double() || is_symbol()) {
    os << to_string();
  } else if (is_cons()) {
    os << "(";
    const Cell* current_cell = this;

    while (current_cell!=nil){
      //get car
      //if car is conspair, call print on the subtree
      if (current_cell->get_car()->is_cons()){
	current_cell->get_car()->print(os);
      } else{
	//else get the value and output it
	os << current_cell->get_car()->to_string();
      }
      //loop to the cdr
      current_cell = current_cell->get_cdr();

      if (current_cell != nil) {
	os << " ";
      }
    }
    os << ")";
  }
}

string Cell::to_string() const
{
  stringstream ss;
  if (is_int()) {
    ss << get_int();
  } else if (is_double()) {
    ss << fixed << setprecision(6) << get_double();
  } else if (is_symbol()) {
    ss << get_symbol();
  } else ss << "";
  return ss.str();
}

Cell* Cell::copy() const
{
  if (this == nil) {
    return nil;
  }
  
  if (is_int()) {
    return new Cell(get_int());
  } else if (is_double()) {
    return new Cell(get_double());
  } else if (is_symbol()) {
    return new Cell(symbol_m);
  } else if (is_cons()) {
    return new Cell(get_car(), get_cdr());
  }
}

Cell::Cell(const Cell& c)
{
  if (&c == nil) error_handler("trying to deep copy a nil Cell!");
  
  if (c.is_int()){
    tag_m = type_int;
    int_m = c.get_int();
  } else if (c.is_double()){
    tag_m = type_double;
    double_m = c.get_double();
  } else if (c.is_symbol()){
    tag_m = type_symbol;
    symbol_m = new char[c.get_symbol().size()+1];
    strcpy(symbol_m, c.get_symbol().c_str());
  } else if (c.is_cons()){
    tag_m = type_conspair;
    conspair_m.car_m = c.get_car();
    conspair_m.cdr_m = c.get_cdr();
  }
}

Cell::~Cell(){
  
  //prevent deletion of nil
  if (this == nil) return;

  if (is_cons()){
    delete get_car();
    delete get_cdr();
  } else if (is_symbol()) {
    delete[] symbol_m;
  }
}
