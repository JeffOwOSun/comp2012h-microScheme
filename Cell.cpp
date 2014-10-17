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
Cell* const nil = new IntCell(0);

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

Cell* Cell::add(Cell* const c) const
{
  error_handler("add unimplemented");
}

Cell* Cell::subtract(Cell* const c) const
{
  error_handler("subtract unimplemented");
}

Cell* Cell::multiply(Cell* const c) const
{
  error_handler("multiply unimplemented");
}

Cell* Cell::divide_by(Cell* const c) const
{
  error_handler("divide_by unimplemented");
}

Cell::~Cell(){}

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
  if (this == nil) return nil;
  return new IntCell(int_m);
}

Cell* IntCell::add (Cell* const c) const
{
  if (c->is_int()) {
    return new IntCell(get_int() + c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() + c->get_double());
  } else error_handler("add operand invalid");
}
Cell* IntCell::subtract (Cell* const c) const
{
  if (c->is_int()) {
    return new IntCell(get_int() - c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() - c->get_double());
  } else error_handler("subtract operand invalid");

}
Cell* IntCell::multiply (Cell* const c) const
{
  if (c->is_int()) {
    return new IntCell(get_int() * c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_int() * c->get_double());
  } else error_handler("multiply operand invalid");
}
Cell* IntCell::divide_by (Cell* const c) const
{
  if (c->is_int()) {
    if (c->get_int() == 0) error_handler("divide by zero");
    return new IntCell(get_int() / c->get_int());
  } else if (c->is_double()) {
    if (c->get_double() == 0) error_handler("divide by zero");
    return new DoubleCell(get_int() / c->get_double());
  } else error_handler("divide_by operand invalid");
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
  if (this == nil) return nil;
  return new DoubleCell(double_m);
}

Cell* DoubleCell::add(Cell* const c) const
{
  if (c->is_int()) {
    return new DoubleCell(get_double() + c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() + c->get_double());
  } else error_handler("add operand invalid");
}
Cell* DoubleCell::subtract(Cell* const c) const
{
  if (c->is_int()) {
    return new DoubleCell(get_double() - c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() - c->get_double());
  } else error_handler("subtract operand invalid");

}
Cell* DoubleCell::multiply(Cell* const c) const
{
  if (c->is_int()) {
    return new DoubleCell(get_double() * c->get_int());
  } else if (c->is_double()) {
    return new DoubleCell(get_double() * c->get_double());
  } else error_handler("multiply operand invalid");
}
Cell* DoubleCell::divide_by(Cell* const c) const
{
  if (c->is_int()) {
    if (c->get_int() == 0) error_handler("divide by zero");
    return new DoubleCell(get_double() / c->get_int());
  } else if (c->is_double()) {
    if (c->get_double() == 0) error_handler("divide by zero");
    return new DoubleCell(get_double() / c->get_double());
  } else error_handler("divide_by operand invalid");
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
  if (this == nil) return nil;
  return new SymbolCell(symbol_m);
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
  if (this == nil) return nil;
  return new ConsCell(car_m->copy(), cdr_m->copy());
}

ConsCell::~ConsCell()
{
  if (car_m!=nil) delete car_m;
  if (cdr_m!=nil) delete cdr_m;
}
