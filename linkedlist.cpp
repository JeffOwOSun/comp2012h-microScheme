#include "linkedlist.hpp"

int list_size(const Node* n) {
  int count = 0;
  const Node* pos = n;
  
  //Judge if pos is actually pointing to a node
  if (pos){
    count++;
    //count on
    while (pos->next_m){
      count++;
      pos=pos->next_m;
    }
  }
  //count will be 0 if n doesn't point to a valid node
  return count;
}

Cell* list_ith(Node* n, unsigned int i) {
  Node* pos = n;
  unsigned int remaining = i;
  //find and count the remaining nodes
  while (pos->next_m && remaining >0) {
    pos = pos->next_m;
  }

  //If we have reached the end of the list but not the required index,
  if (remaining >0){
    //Give an error
    std::cerr << "Position index exceeded maximum length!" <<std::endl;
    return NULL;
  } else {
    return pos->elem_m;
  }
}

Node* list_erase(Node* n, Node* pos) {
  Node* p = pos;
  if ( n == p) {
    //Go to the second node, and assign its address to the first node's elem_m.
    p = n->next_m;
    n->elem_m = p->elem_m;
    //Make sure second node's elem_m is cleared so that it's not affected
    //by the delete operation later on.
    p->elem_m = NULL;
    //now the problem is the same as non-root situation
    //and will be processed by the remaining code
  }

  //We deal with erasing non-root nodes.
  if ( n != p ) {
    //Now that our given node is not root,
    
    //Search the list from n until i->next_m is pos
    Node* i = n;
    while ( i->next_m != p) {
      i = i->next_m;
    }

    //now i is the node right before pos
    //let i->next_m = pos->next_m
    i->next_m = p->next_m;
    
    //destroy pos
    //first destroy pos->elem_m
    delete p->elem_m;
    //then destroy pos
    delete p;
    
    return i->next_m;
  }
}

Node* list_insert(Node* n, Node* pos, Cell* c) {
std::cerr<<"linkedlist.cpp function list_insert Line1"<<std::endl;
  //If again our pos equals to n, which is the head node
  if (n == pos) {
    if (n->next_m) {
      //then we first insert a Node AFTER head.
      //this node has next_m as original second node
      //and a elem_m that's originally head's.
      n->next_m = make_node(n->elem_m, n->next_m);
      //append c to head node
      n->elem_m = c;
    } else {
      //now that n is the only node in our linked list,
      n->next_m = make_node(n->elem_m, NULL);
      n->elem_m = c;
    }
    return n;
  } else {
    //normal situation, where we are not inserting in front of head :-)
    //search the list until i->next_m is pos
    Node* i = n;
    while (i->next_m != pos) {
      i = i->next_m;
    }

    //make a new node with the cell appended, and pointing to pos
    //append this node after i
    i->next_m = make_node(c, pos);
    
    return i->next_m;
  }
}

Node* list_insert_int(Node* n, Node* pos, const int value) {
  //we make a cell of int,
  //then call list_insert
  return list_insert(n, pos, make_int(value));
}

Node* list_insert_double(Node* n, Node* pos, const double value) {
  //make a cell of double,
  //then call list_insert
  return list_insert(n, pos, make_double(value));
}

Node* list_insert_symbol(Node* n, Node* pos, const char* value) {
  //make a cell of symbols,
  //then call list_insert
  return list_insert(n, pos, make_symbol(value));
}
