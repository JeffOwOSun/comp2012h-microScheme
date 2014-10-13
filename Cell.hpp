/**
 * \mainpage COMP2012H Programming Assignment 2, Fall 2014
 *
 * \author SUN Yushi
 * \author 20176087
 * \author jeffsun@jowos.moe
 * \author LA1
 *
 * \date 2014-10-01
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.10.10 at 23:00 by CASS
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

//my own error handler :-)
#include "error.hpp"

/**
 * \class Cell
 * \brief Class Cell
 */
class Cell {
public:
  /**
   * \brief Check if this is an int cell.
   * \return True iff this is an int cell.
   */
  virtual bool is_int() const;

  /**
   * \brief Check if this is a double cell.
   * \return True iff this is a double cell.
   */
  virtual bool is_double() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return True iff this is a symbol cell.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell.
   */
  virtual bool is_cons() const;

  /**
   * \brief Accessor (error if this is not an int cell).
   * \return The value in this int cell.
   */
  virtual int get_int() const;

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return The value in this double cell.
   */
  virtual double get_double() const;

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return The symbol name in this symbol cell.
   */
  virtual std::string get_symbol() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  virtual Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  virtual Cell* get_cdr() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const = 0;

  /**
   * \brief Make a copy of current Cell.
   * \return Pointer to the newly made Cell;
   */
  virtual Cell* copy() const = 0;

  /**
   * \brief Evaluate the tree rooted at this Cell
   */
  virtual Cell* eval() const = 0;

  virtual Cell* add(Cell* const c) const;
  virtual Cell* subtract(Cell* const c) const;
  virtual Cell* multiply(Cell* const c) const;
  virtual Cell* divide_by(Cell* const c) const;
  /**
   * \brief virtual Destructor
   */
  virtual ~Cell();

};

// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;

/**
 * \class IntCell
 * \brief Class IntCell, derived from Cell to hold int type
 */
class IntCell : public Cell
{
public:
  /**
   * \brief Constructor
   */
  IntCell(const int i);

  /**
   * \brief Getter function to retrieve stored integer
   * \return The integer
   */
  virtual int get_int() const;

  /**
   * \brief judge if this Cell is an IntCell or not
   * \return True iff this Cell in an IntCell
   */
  virtual bool is_int() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

  /**
   * \brief Make a copy of current Cell.
   * \return Pointer to the newly made Cell;
   */
  virtual Cell* copy() const;

  /**
   * \brief Evaluate the tree rooted at this Cell
   */
  virtual Cell* eval() const;
  
  virtual Cell* add(Cell* const c) const;
  
  virtual Cell* subtract(Cell* const c) const;
  
  virtual Cell* multiply(Cell* const c) const;
  
  virtual Cell* divide_by(Cell* const c) const;
  
private:
  int int_m;
};

/**
 * \class DoubleCell
 * \brief Class SymbolCell, derived from Cell to hold double type
 */
class DoubleCell : public Cell
{
public:
  /**
   * \brief Constructor
   */
  DoubleCell(const double d);

  /**
   * \brief Getter function to retrieve stored integer
   * \return The integer
   */
  double get_double() const;

  /**
   * \brief judge if this Cell is an DoubleCell or not
   * \return True iff this Cell in an DoubleCell
   */
  bool is_double() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief Make a copy of current Cell.
   * \return Pointer to the newly made Cell;
   */
  Cell* copy() const;

  /**
   * \brief Evaluate the tree rooted at this Cell
   */
  Cell* eval() const;
  
  virtual Cell* add(Cell* const c) const;
  
  virtual Cell* subtract(Cell* const c) const;
  
  virtual Cell* multiply(Cell* const c) const;
  
  virtual Cell* divide_by(Cell* const c) const;
  
private:
  double double_m;
};


/**
 * \class SymbolCell
 * \brief Class SymbolCell, derived from Cell to hold int symbol type
 */
class SymbolCell : public Cell
{
public:
  /**
   * \brief Constructor
   */
  SymbolCell(const char* const s);

  /**
   * \brief Getter function to retrieve stored symbol
   * \return The string
   */
  std::string get_symbol() const;

  /**
   * \brief judge if this Cell is an SymbolCell or not
   * \return True iff this Cell is an SymbolCell
   */
  bool is_symbol() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

 /**
   * \brief Make a copy of current Cell.
   * \return Pointer to the newly made Cell;
   */
  Cell* copy() const;

  /**
   * \brief Evaluate the tree rooted at this Cell
   */
  Cell* eval() const;
  
  /**
   * \brief Destructor
   */
  ~SymbolCell();
  
private:
  char* symbol_m;
};

/**
 * \class ConsCell
 * \brief Class ConsCell, derived from Cell to hold Conspair type
 */
class ConsCell : public Cell
{
public:
  /**
   * \brief Constructor
   */
  ConsCell(Cell* const my_car, Cell* const my_cdr = nil);

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  Cell* get_cdr() const;
 
  /**
   * \brief judge if this Cell is an ConsCell or not
   * \return True iff this Cell is an ConsCell
   */
  bool is_cons() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief Make a copy of current Cell.
   * \return Pointer to the newly made Cell;
   */
  Cell* copy() const;

  /**
   * \brief Evaluate the tree rooted at this Cell
   */
  Cell* eval() const;
  
  /**
   * \brief Destructor
   */
  ~ConsCell();
    
private:
  Cell* car_m;
  Cell* cdr_m;
};

#endif // CELL_HPP
