/**
 * \mainpage COMP151H Programming Assignment 4, Fall 2014
 *
 * \author SUN Yushi
 * \author 20176087
 * \author jeffsun@jowos.moe
 * \author LA1
 *
 * \date 2014.11.10
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.11.13 at 23:00 by CASS
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
#include <deque>
#include "exceptions.hpp"
#include <map>

/**
 * \class Cell
 * \brief Class Cell
 */
class Cell {
public:
  /**
   * \brief Check if this is an int cell.
   * \return True iff this is an int cell. Default return false in ABC.
   */
  virtual bool is_int() const;

  /**
   * \brief Check if this is a double cell.
   * \return True iff this is a double cell. Default return false in ABC.
   */
  virtual bool is_double() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return True iff this is a symbol cell. Default return false in ABC.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell. Default return false in ABC.
   */
  virtual bool is_cons() const;

  /**
   * \brief Check if this is a procedure cell
   * \return True iff this is a procedure cell. Default return false in ABC.
   */
  virtual bool is_procedure() const;
  
  /**
   * \brief Accessor (error if this is not an int cell).
   * \return The value in this int cell.
   */
  virtual int get_int() const throw(UnimplementedError);

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return The value in this double cell.
   */
  virtual double get_double() const throw(UnimplementedError);

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return The symbol name in this symbol cell.
   */
  virtual std::string get_symbol() const throw(UnimplementedError);

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  virtual Cell* get_car() const throw(UnimplementedError);

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  virtual Cell* get_cdr() const throw(UnimplementedError);

  /**
   * \brief Accessor to the assumed formals of a procedure cell. (error if this is not a procedure cell)
   * \return Pointer to the root of formals tree
   */
  virtual Cell* get_formals() const throw(UnimplementedError);

  /**
   * \brief Accessor to the assumed body of a procedure cell. (error if this is not a procedure cell)
   * \return Pointer to the root of body tree
   */
  virtual Cell* get_body() const throw(UnimplementedError);
  
  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation. Pure virtual function.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const = 0;

  /**
   * \brief Make a copy of current Cell. Pure virtual in ABC.
   * \return Pointer to the newly made Cell;
   */
  virtual Cell* copy() const = 0;

  /**
   * \brief Add operation. Throw an "unimplemented" error in ABC
   * \param c Cell pointer to the second operand
   * \return Cell pointer to the result Cell. This Cell should be made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* add(Cell* const c) const throw(UnimplementedError, OperandInvalidError);

  /**
   * \brief Subtract operation. Throw an "unimplemented" error in ABC
   * \param c Cell pointer to the second operand
   * \return Cell pointer to the result Cell. This Cell should be made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* subtract(Cell* const c) const throw(UnimplementedError, OperandInvalidError);

  /**
   * \brief Multiply operation. Throw an "unimplemented" error in ABC
   * \param c Cell pointer to the second operand
   * \return Cell pointer to the result Cell. This Cell should be made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* multiply(Cell* const c) const throw(UnimplementedError, OperandInvalidError);

  /**
   * \brief Divide_by operation. Throw an "unimplemented" error in ABC
   * \param c Cell pointer to the second operand
   * \return Cell pointer to the result Cell. This Cell should be made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* divide_by(Cell* const c) const throw(UnimplementedError, OperandInvalidError, DivideByZeroError);

  /**
   * \brief < operation. Throw an "unimplemented" error here in ABC
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool smaller_than(Cell* const c) const throw(UnimplementedError, OperandInvalidError);

  
  /**
   * \brief > operation. Throw an "unimplemented" error here in ABC
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool larger_than(Cell* const c) const throw(UnimplementedError, OperandInvalidError);

  /**
   * \brief Not operation. Throw an "unimplemented" error here in ABC
   * \return Pointer to the Cell containing the value
   */
  virtual Cell* get_not() const throw(UnimplementedError);

  /**
   * \brief Apply this function on the given parameters
   * \return Pointer to the Cell containing the result of the last function body
   */
  virtual Cell* apply(Cell* const args) const;

  /**
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result. Must be implemented in subclasses
   */
  virtual Cell* eval() const = 0;
  
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
  virtual int get_int() const throw();

  /**
   * \brief judge if this Cell is an IntCell or not
   * \return True.
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
   * \brief Add operation. 
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* add(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Subtract operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* subtract(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Multiply operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* multiply(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Divide_by operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* divide_by(Cell* const c) const throw (DivideByZeroError, OperandInvalidError);

  
  /**
   * \brief < operation.
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool smaller_than(Cell* const c) const throw(OperandInvalidError);

  
  /**
   * \brief > operation.
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool larger_than(Cell* const c) const throw(OperandInvalidError);

  /**
   * \brief Not operation.
   * \return Pointer to the Cell containing the value. Delete immediately after use
   */
  virtual Cell* get_not() const throw();

  /**
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result. Must be implemented in subclasses
   */
  virtual Cell* eval() const;
  
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
  double get_double() const throw();

  /**
   * \brief judge if this Cell is an DoubleCell or not
   * \return True.
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
   * \brief Add operation. 
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* add(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Subtract operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* subtract(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Multiply operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* multiply(Cell* const c) const throw (OperandInvalidError);

  /**
   * \brief Divide_by operation.
   * \param c Cell pointer to the second operand. Must be an IntCell or DoubleCell.
   * \return Cell pointer to the result Cell. This Cell is made using new. User should take care of proper deletion after using the returned Cell
   */
  virtual Cell* divide_by(Cell* const c) const throw (OperandInvalidError, DivideByZeroError);

  
  /**
   * \brief < operation.
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool smaller_than(Cell* const c) const throw(OperandInvalidError);

  
  /**
   * \brief > operation.
   * \param c Cell pointer to the second operand
   * \return A bool value indicating the result.
   */
  virtual bool larger_than(Cell* const c) const throw(OperandInvalidError);

  /**
   * \brief Not operation.
   * \return Pointer to the Cell containing the value. Delete immediately after use
   */
  virtual Cell* get_not() const throw();

  /**
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result
   */
  virtual Cell* eval() const;
  
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
  std::string get_symbol() const throw ();

  /**
   * \brief judge if this Cell is an SymbolCell or not
   * \return True.
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
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result
   */
  virtual Cell* eval() const;
  
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
   * \brief Constructor. ATTENTION: no internal copy of my_car and my_cdr will be made. Please explicitly make copies before the call. 
   */
  ConsCell(Cell* const my_car, Cell* const my_cdr);

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  Cell* get_car() const throw ();

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  Cell* get_cdr() const throw ();
 
  /**
   * \brief judge if this Cell is an ConsCell or not
   * \return True.
   */
  bool is_cons() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief Recursively make a copy of current Cell and its subtrees.
   * \return Pointer to the newly made Cell;
   */
  Cell* copy() const;

  /**
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result
   */
  virtual Cell* eval() const;
  
  /**
   * \brief Not operation.
   * \return Pointer to the Cell containing the value. Delete immediately after use
   */
  virtual Cell* get_not() const throw();

  /**
   * \brief Destructor. Recursively delete the whole tree rooted at this ConsCell. Use with caution.
   */
  ~ConsCell();
    
private:
  Cell* car_m;
  Cell* cdr_m;
};


/**
 * \class ProcedureCell
 * \brief Class ProcedureCell, derived from Cell to hold function type
 */
class ProcedureCell : public Cell
{
public:
  /**
   * \brief Constructor. ATTENTION: no internal copy of my_formals and my_body will be made. Please explicitly make copies before the call. 
   */
  ProcedureCell(Cell* const my_formals, Cell* const my_body);

  /**
   * \brief Accessor.
   * \return Pointer to the root of formals tree..
   */
  virtual Cell* get_formals() const throw ();

  /**
   * \brief Accessor.
   * \return Pointer to the root of body tree.
   */
  virtual Cell* get_body() const throw ();
 
  /**
   * \brief judge if this Cell is a ProcedureCell or not
   * \return True.
   */
  virtual bool is_procedure() const throw();

  /**
   * \brief Print the procedure cell. Constant no matter the definition of the function.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

  /**
   * \brief Make a copy of this ProcedureCell
   * \return Pointer to the newly made Cell
   */
  virtual Cell* copy() const;

  /**
   * \brief NOT this cell
   * \return Pointer to a temporary IntCell(0)
   */
  virtual Cell* get_not() const throw ();

  /**
   * \brief Apply this function on the given parameters
   * \param args The Pointer to the root of the args tree. An internal copy will be made.
   * \return Pointer to the Cell containing the result of the last function body
   */
  virtual Cell* apply(Cell* const args) const;

  /**
   * \brief Eval the tree rooted at this Cell
   * \return Pointer to the Cell containing the result
   */
  virtual Cell* eval() const;

  /**
   * \brief Destructor. Recursively delete the whole tree of formals and body.
   */
  virtual ~ProcedureCell();
    
private:
  Cell* formals_m;
  Cell* body_m;
};

/**
 * \brief The deque of definition maps. Front is global, back is local/current.
 */
extern std::deque<std::map<std::string, Cell*> > definition_stack;


/**
 * \brief Initializer for definition stack
 * \return a deque<map<string,Cell*>> type object that contains one global map
 */
std::deque<std::map<std::string, Cell*> > stack_initialize();

/**
 * \brief A helper function for safely delete
 * \param c Reference to the pointer to be deleted. T should be a pointer type
 */
template<typename T>
void safe_delete(T& c)
{
  if (c != nil) delete c;
  c = nil;
}
#endif // CELL_HPP
