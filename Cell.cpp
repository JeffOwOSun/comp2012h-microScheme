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
const Cell* nil = 0;

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
  conspair_m.car_m = my_car;
  conspair_m.cdr_m = my_cdr;
  return;
}

bool Cell::is_int()
{
  return tag_m == type_int;
}

bool Cell::is_double()
{
  return tag_m == type_double;
}

bool Cell::is_symbol()
{
  return tag_m == type_symbol;
}

bool Cell::is_cons()
{
  return tag_m == type_conspair;
}

int Cell::get_int()
{
  if (is_int()) {
    return int_m;
  } else {
    cerr << "In function Cell::get_int(), the corresponding Cell instance is not a int Cell!" << endl;
    exit(1);
  }
}

double Cell::get_double()
{
  if (is_double()) {
    return double_m;
  } else {
    cerr << "In function Cell::get_double(), the corresponding Cell instance is not a double Cell!" << endl;
    exit(1);
  }
}

string Cell::get_symbol()
{
  if (is_symbol()) {
    return new string (symbol_m);
  } else {
    cerr << "In function Cell::get_symbol(), the corresponding Cell instance is not a symbol Cell!" << endl;
    exit(1);
  }
}

Cell* Cell::get_car()
{
  if (is_cons()) {
    return conspair_m.car_m;
  } else {
    cerr << "In function Cell::get_car(), the corresponding Cell is not a cons Cell!" << endl;
    exit(1);
  }
}

Cell* Cell::get_cdr()
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
  os << sexpr_m;
}
