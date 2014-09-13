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
  if (!(n)){
    std::cerr<<"In function list_ith, param n invalid!"<<std::endl;
    exit(1);
  }
  Node* pos = n;
  unsigned int remaining = i;
  //find and count the remaining nodes
  while (get_next(pos) && remaining >0) {
    pos = get_next(pos);
    remaining--;
  }

  //If we have reached the end of the list but not the required index,
  if (remaining >0){
    //Give an error
    std::cerr << "Position index i exceeded maximum length!:" <<i<<std::endl;
    exit(1);
  } else {
    return get_elem(pos);
  }
}

Node* list_erase(Node* n, Node* pos) {
  if (!(n && pos)){
    std::cerr<<"In function list_erase, param n or pos invalid!"<<std::endl;
    exit(1);
  }
  
  Node* p = pos;
  if (n == p) {
    //if n doesn't have any descendant then exit code with error;
    if (!get_next(n)){
      std::cerr<<"Can't delete when there's only one element in the list!"<<std::endl;
      exit(1);
    }
    //Go to the second node, and copy its elem_m to the first node's elem_m.
    p = get_next(n);
    n->elem_m = get_elem(p);
    //Make sure second node's elem_m is cleared so that it's not affected
    //by the delete operation later on.
    p->elem_m = NULL;
    //now the problem is the same as non-root situation
    //and will be processed by the remaining code
  }

  //From now on we deal with erasing non-root nodes.
  //Now that our given node is not root,
  //search the list from n until get_next(i) is pos
  Node* i = n;
  while ( get_next(i) && get_next(i) != p) {
    i = get_next(i);
  }
    
  //exit the code if pos is not a descendant of n
  if (!get_next(i)) {
    std::cerr<<"pos not a descendant of n!"<<std::endl;
    exit(1);
  }

  //now i is the node right before pos
  //let get_next(i) = get_next(pos)
  i->next_m = get_next(p);

  //delete[] char* of the Cell if exists
  if (symbolp(get_elem(p))){
    delete[] get_elem(p)->symbol_m;
  }

  //destroy the Cell
  delete p->elem_m;
    
  //then destroy the Node
  delete p;

  return get_next(i);
}

Node* list_insert(Node* n, Node* pos, Cell* c) {
  if (!(n)){
    std::cerr<<"In function list_insert, param n invalid!"<<std::endl;
    exit(1);
  }
  //If again our pos equals to n, which is the head node
  if (n == pos) {
    if (get_next(n)) {
      //then we first insert a Node AFTER head.
      //this node has original second node as next_m
      //and a elem_m that's originally head's.
      n->next_m = make_node(get_elem(n), get_next(n));
      //append c to head node
      n->elem_m = c;
    } else {
      //now that n is the only node in our linked list,
      n->next_m = make_node(get_elem(n), NULL);
      n->elem_m = c;
    }
    return n;
  } else {
    //normal situation, where we are not inserting in front of head :-)
    //search the list until get_next(i) is pos
    Node* i = n;
    while (get_next(i) && get_next(i) != pos) {
      i = get_next(i);
    }
    //exit the code if pos is not NULL (tail) but not a descendant of n
    if (!get_next(i) && pos) {
      std::cerr<<"pos not a descendant of n!"<<std::endl;
      exit(1);
    }
    //make a new node with the cell appended, and pointing to pos
    //append this node after i
    i->next_m = make_node(c, pos);
    
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
