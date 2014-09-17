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
  ostringstream outs;
  outs << i;
  sexpr_m = outs.str();
}

Cell::Cell(double d)
{
  ostringstream outs;
  outs << d;
  sexpr_m = outs.str();
}

Cell::Cell(const char* s)
{
  sexpr_m = string(s);
}

Cell::Cell(const Cell* my_car, const Cell* my_cdr)
{
  if (my_cdr == nil || my_cdr->sexpr_m == "()") {
    sexpr_m = "("
      + ( (my_car == nil) ? "()" : my_car->sexpr_m )
      + ")";
  } else if (my_cdr->sexpr_m[0] == '(') {
    sexpr_m = "("
      + ( (my_car == nil) ? "()" : my_car->sexpr_m )
      + " "
      + my_cdr->sexpr_m.substr(1, my_cdr->sexpr_m.length() - 1);
  } else {
    cout << "error: can't cons a car ";
    my_car->print(cout);
    cout << " onto a cdr ";
    my_cdr->print(cout);
    cout << " that is not a list" << endl;
    exit(1);
  }
}

void Cell::print(ostream& os) const
{
  os << sexpr_m;
}
