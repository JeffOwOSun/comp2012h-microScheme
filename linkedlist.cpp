#include "linkedlist.hpp"

int list_size(const Node* n) {
  int count = 0;
  const Node* pos = n;
  
  //Judge if pos is actually pointing to a node
  if (pos){
    count++;
    //count on
    while (get_next(pos)){
      count++;
      pos = get_next(pos);
    }
  }
  //count will be 0 if n doesn't point to a valid node
  return count;
}

Cell* list_ith(Node* n, unsigned int i) {
  Node* pos = n;
  unsigned int remaining = i;
  //find and count the remaining nodes
  while (get_next(pos) && remaining >0) {
    pos = get_next(pos);
  }

  //If we have reached the end of the list but not the required index,
  if (remaining >0){
    //Give an error
    std::cerr << "Position index exceeded maximum length!" <<std::endl;
    return NULL;
  } else {
    return get_elem(pos);
  }
}

Node* list_erase(Node* n, Node* pos) {
  Node* p = pos;
  if ( n == p) {
    //Go to the second node, and assign its address to the first node's elem_m.
    p = get_next(n);
    get_elem(n) = get_elem(p);
    //Make sure second node's elem_m is cleared so that it's not affected
    //by the delete operation later on.
    get_elem(p) = NULL;
    //now the problem is the same as non-root situation
    //and will be processed by the remaining code
  }

  //We deal with erasing non-root nodes.
  if ( n != p ) {
    //Now that our given node is not root,
    
    //Search the list from n until get_next(i) is pos
    Node* i = n;
    while ( get_next(i) != p) {
      i = get_next(i);
    }

    //now i is the node right before pos
    //let get_next(i) = get_next(pos)
    get_next(i) = get_next(p);
    
    //destroy pos
    //first destroy get_elem(pos)
    delete get_elem(p);
    //then destroy pos
    delete p;
    
    return get_next(i);
  }
}

Node* list_insert(Node* n, Node* pos, Cell* c) {
  //If again our pos equals to n, which is the head node
  if (n == pos) {
    if (get_next(n)) {
      //then we first insert a Node AFTER head.
      //this node has next_m as original second node
      //and a elem_m that's originally head's.
      get_next(n) = make_node(get_elem(n), get_next(n));
      //append c to head node
      get_elem(n) = c;
    } else {
      //now that n is the only node in our linked list,
      get_next(n) = make_node(get_elem(n), NULL);
      get_elem(n) = c;
    }
    return n;
  } else {
    //normal situation, where we are not inserting in front of head :-)
    //search the list until get_next(i) is pos
    Node* i = n;
    while (get_next(i) != pos) {
      i = get_next(i);
    }

    //make a new node with the cell appended, and pointing to pos
    //append this node after i
    get_next(i) = make_node(c, pos);
    
    return get_next(i);
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
