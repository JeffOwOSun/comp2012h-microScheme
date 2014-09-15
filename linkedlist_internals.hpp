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
  Cell* my_cell = (Cell*) malloc(sizeof(Cell));
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
  Cell* my_cell = (Cell*) malloc(sizeof(Cell));
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
  Cell* my_cell = (Cell*) malloc(sizeof(Cell));
  my_cell->tag_m = type_symbol;
  my_cell->symbol_m =(char*) malloc(strlen(s)+1);
  strcpy(my_cell->symbol_m,s);
  return my_cell;
}


/**
 * \brief Make a linked list node.
 * \param my_elem Pointer to the element to be held by this node.
 * \param my_next Pointer to the next node.
 */
inline Node* make_node(Cell* my_elem, Node* my_next)
{
  Node* my_node = (Node*)malloc(sizeof(Node));
  my_node->elem_m = my_elem;
  my_node->next_m = my_next;
  return my_node;
}

/**
 * \brief Check if d points to an int node.
 * \return True iff d points to an int node. Also false if c is NULL.
 */
inline bool intp(const Cell* c)
{
  return c ? c->tag_m == type_int : false;
}

/**
 * \brief Check if d points to a double node.
 * \return True iff d points to a double node. Also false if c is NULL.
 */
inline bool doublep(const Cell* c)
{
  return c ?  c->tag_m == type_double : false;
}

/**
 * \brief Check if d points to a symbol node.
 * \return True iff d points to a symbol node. Also false if c is NULL.
 */
inline bool symbolp(const Cell* c)
{
  return c ? c->tag_m == type_symbol : false;
}

/**
 * \brief Accessor (error if d is not an int node).
 * \return The value in the int node pointed to by c.
 */
inline int get_int(const Cell* c)
{
  if (intp(c)){
    return c->int_m;
  } else {
    //print out error
    std::cerr << "ERROR" <<std::endl;
    exit(1);
  }
}

/**
 * \brief Accessor (error if d is not a double node).
 * \return The value in the double node pointed to by c.
 */
inline double get_double(const Cell* c)
{
  if (doublep(c)){
    return c->double_m;
  } else {
    //print out error
    std::cerr << "ERROR" <<std::endl;
    exit(1);
  }  
}

/**
 * \brief Retrieve the symbol name as a string (error if d is not a
 * symbol node).
 * \return The symbol name in the symbol node pointed to by c.
 */
inline char* get_symbol(const Cell* c)
{
  if (symbolp(c)){
    return c->symbol_m;
  } else {
    //print out error
    std::cerr << "ERROR" <<std::endl;
    exit(1);
  }
}

/**
 * \brief Accessor.
 * \return The elem pointer in the linked list node pointed to by c. NULL if n is not a valid Node*.
 */
inline Cell* get_elem(const Node* n)
{
  //make sure passed in n points to a valid Node*
  return n ? n->elem_m : (Cell*)NULL;
}

/**
 * \brief Accessor.
 * \return The pointer in the linked list node pointed to by c. NULL if n is not a valid Node*.
 */
inline Node* get_next(const Node* n)
{
  return n ? n->next_m : (Node*)NULL;
}

/**
 * \brief Print the linked list rooted at n in parentheses.
 * \param os The output stream to print to.
 * \param n The root node of the linked list to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Node& n)
{
  const Node* p = &n;
  //print the opening paren
  os << "(";

  //an "infinite loop" printing each node
  //break upon end
  while(p) {
    
    if (intp(get_elem(p))) {
      os<<get_int(get_elem(p));
    } else if (doublep(get_elem(p))){
      os<<get_double(get_elem(p));
    } else if (symbolp(get_elem(p))){
      os<<get_symbol(get_elem(p));
    }
    
    //move to the next node if exsits
    //otherwise break the loop
    if (get_next(p)) {
      //remeber to print a space
      os << " ";
      p = get_next(p);
    } else break;
  }

  //print the closing paren
  os << ")";
  
  return os;
}

#endif // LINKEDLIST_INTERNALS_HPP
