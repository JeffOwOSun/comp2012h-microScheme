/**
 * \file linkedlist_internals.hpp
 *
 * Encapsulates an abstract interface layer for a cons list ADT,
 * without using member functions. Makes no assumptions about what
 * kind of concrete type Cell will be defined to be.
 */

#ifndef LINKEDLIST_INTERNALS_HPP
#define LINKEDLIST_INTERNALS_HPP

#include "Node.hpp"
#include "Cell.hpp"
#include <string>
#include <iostream>

/**
 * \brief Make an int cell.
 * \param i The initial int value to be stored in the new cell.
 */
inline Cell* make_int(int i)
{
  Cell* my_cell = new Cell();
  my_cell->tag_m = type_int;
  my_cell->int_m = i;
  return my_cell;
}

/**
 * \brief Make a double cell.
 * \param d The initial double value to be stored in the new cell.
 */
inline Cell* make_double(double d)
{
  Cell* my_cell = new Cell();
  my_cell->tag_m = type_double;
  my_cell->double_m = d;
  return my_cell;
}

/**
 * \brief Make a symbol cell.
 * \param s The initial symbol name to be stored in the new cell.
 */
inline Cell* make_symbol(const char* s)
{
std::cerr<<"linkedlist_internals.hpp make_symbol line 1"<<std::endl;
  Cell* my_cell = new Cell();
std::cerr<<"linkedlist_internals.hpp make_symbol line 49"<<std::endl;
  my_cell->tag_m = type_symbol;
std::cerr<<"linkedlist_internals.hpp make_symbol line 51"<<std::endl;
  strcpy(my_cell->symbol_m,s);
std::cerr<<"linkedlist_internals.hpp make_symbol line 53"<<std::endl;
  return my_cell;
}


/**
 * \brief Make a linked list node.
 * \param my_elem Pointer to the element to be held by this node.
 * \param my_next Pointer to the next node.
 */
inline Node* make_node(Cell* my_elem, Node* my_next)
{
  return new Node(my_elem, my_next);
}

/**
 * \brief Check if d points to an int node.
 * \return True iff d points to an int node.
 */
inline bool intp(const Cell* c)
{
  return c->tag_m == type_int;
}

/**
 * \brief Check if d points to a double node.
 * \return True iff d points to a double node.
 */
inline bool doublep(const Cell* c)
{
  return c->tag_m == type_double;
}

/**
 * \brief Check if d points to a symbol node.
 * \return True iff d points to a symbol node.
 */
inline bool symbolp(const Cell* c)
{
  return c->tag_m == type_symbol;
}

/**
 * \brief Accessor (error if d is not an int node).
 * \return The value in the int node pointed to by c.
 */
inline int get_int(const Cell* c)
{
  if (c->tag_m == type_int){
    return c->int_m;
  } else {
    //print out error
    std::cerr << "Cell type not match!" <<std::endl;
  }
}

/**
 * \brief Accessor (error if d is not a double node).
 * \return The value in the double node pointed to by c.
 */
inline double get_double(const Cell* c)
{
  if (c->tag_m == type_double){
    return c->double_m;
  } else {
    //print out error
    std::cerr << "Cell type not match!" <<std::endl;
  }  
}

/**
 * \brief Retrieve the symbol name as a string (error if d is not a
 * symbol node).
 * \return The symbol name in the symbol node pointed to by c.
 */
inline char* get_symbol(const Cell* c)
{
  if (c->tag_m == type_symbol){
    return c->symbol_m;
  } else {
    //print out error
    std::cerr << "Cell type not match!" <<std::endl;
  }
}

/**
 * \brief Accessor.
 * \return The elem pointer in the linked list node pointed to by c.
 */
inline Cell* get_elem(const Node* n)
{
  return n->elem_m;
}

/**
 * \brief Accessor.
 * \return The next pointer in the linked list node pointed to by c.
 */
inline Node* get_next(const Node* n)
{
  return n->next_m;
}

/**
 * \brief Print the linked list rooted at n in parentheses.
 * \param os The output stream to print to.
 * \param n The root node of the linked list to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Node& n)
{
  const Node* p = &n;
  do {
    if (intp(p->elem_m)) {
      os<<get_int(p->elem_m);
    } else if (doublep(p->elem_m)){
      os<<get_double(p->elem_m);
    } else if (symbolp(p->elem_m)){
      os<<get_symbol(p->elem_m);
    }
    //move to the next node if exsits
    //otherwise break the loop
    if (p->next_m) {
      p = p->next_m;
    } else break;
  } while (true);
  return os;
}

#endif // LINKEDLIST_INTERNALS_HPP
