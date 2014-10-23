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

Cell::~Cell(){}
///////////////////////////////////SchemeCell/////////////////////////////////////////////
template <typename T>
SchemeCell<T>::SchemeCell (T value): value_m(value){}

template <typename T>
SchemeCell<T>::~SchemeCell (){}

/////////////////////////////////////IntCell//////////////////////////////////////

IntCell::IntCell(const int i): SchemeCell<int>(i) {}

int IntCell::get_int() const throw ()
{
  return get_value();
}

bool IntCell::is_int() const
{
  return true;
}

void IntCell::print(ostream& os) const
{
  os << get_int();
}

Cell* IntCell::copy() const
{
  if (this == nil) return nil;
  return new IntCell(get_int());
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
////////////////////////////////////DoubleCell////////////////////////////////////

DoubleCell::DoubleCell(const double d): SchemeCell<double>(d) {}

double DoubleCell::get_double() const throw ()
{
  return get_value();
}

bool DoubleCell::is_double() const
{
  return true;
}

void DoubleCell::print(ostream& os) const
{
  os << fixed << setprecision(6) << get_double();
}

Cell* DoubleCell::copy() const
{
  if (this == nil) return nil;
  return new DoubleCell(get_double());
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
///////////////////////////////////SymbolCell/////////////////////////////////////

SymbolCell::SymbolCell(const char* const s): SchemeCell<char*>(str_copy(s)){}

string SymbolCell::get_symbol() const throw()
{
  return string(get_value());
}

bool SymbolCell::is_symbol() const
{
  return true;
}

void SymbolCell::print(ostream& os) const
{
  os << get_value();
}

Cell* SymbolCell::copy() const
{
  if (this == nil) return nil;
  return new SymbolCell(get_value());
}

SymbolCell::~SymbolCell()
{
  delete[] get_value();
}

///////////////////////////////////ConsCell/////////////////////////////////////

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr): SchemeCell<ConsPair>((ConsPair){my_car,my_cdr}){}

Cell* ConsCell::get_car() const throw()
{
  return get_value().car_m;
}

Cell* ConsCell::get_cdr() const throw()
{
  return get_value().cdr_m;
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
  return new ConsCell(get_car()->copy(), get_cdr()->copy());
}

Cell* ConsCell::get_not() const throw()
{
  return new IntCell(0);
}

ConsCell::~ConsCell()
{
  if(get_car()!=nil) delete get_car();
  if(get_cdr()!=nil) delete get_cdr();
}
