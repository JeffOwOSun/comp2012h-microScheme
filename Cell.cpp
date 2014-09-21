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
const Cell* nil = new Cell(0);

using namespace std;

Cell::Cell(int i) 
{
  tag_m = type_int;
  int_m = i;
  return;
}

Cell::Cell(double d)
{
  tag_m = type_double;
  double_m = d;
  return;
}

Cell::Cell(const char* s)
{
  tag_m = type_symbol;
  symbol_m = new char[strlen(s)+1];
  strcpy (symbol_m, s);
  return;
}

Cell::Cell(const Cell* my_car, const Cell* my_cdr)
{
  tag_m = type_conspair;
  conspair_m.car_m = (Cell*) my_car;
  conspair_m.cdr_m = (Cell*) my_cdr;
  return;
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
  
  if (is_int()){
    os << get_int();
    return;
  }

  if (is_double()){
    os << fixed <<setprecision(6) << get_double();
    return;
  }

  if (is_symbol()){
    os << get_symbol();
    return;
  }
  
  os << "(";

  //THIS is supposed to be the root of a tree
  const Cell* current_cell = this;

  while (current_cell!=nil){
  //get car
  //if car is conspair, call print on the subtree
    if (current_cell->get_car()->is_cons()){
      current_cell->get_car()->print(os);
    } else{
      //else get the value and output it
      os << current_cell->to_string();
    }
  //loop to the cdr
    current_cell = current_cell->get_cdr();
  }
  os << ")";
  return;
}

string Cell::to_string() const
{
  stringstream ss;
  if (is_int()) {
    ss << get_int();
  } else if (is_double()) {
    ss << fixed << setprecision(6) << get_double();
  } else if (is_symbol()) {
    return get_symbol();
  } else return "";

  return ss.str();
}
