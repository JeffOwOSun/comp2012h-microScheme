#include "linkedlist.hpp"

int list_size(const Node* n) {
  int count = 0;
  Node* pos = n;
  
  //Judge if pos is actually pointing to a node
  if (pos){
    count++;
    //count on
    while (pos->next_m){
      count++;
      pos=next_m;
    }
  }
  //count will be 0 if n doesn't point to a valid node
  return count;
}

Cell* list_ith(Node* n, unsigned int i) {
  
}

Node* list_erase(Node* n, Node* pos) {
}

Node* list_insert(Node* n, Node* pos, Cell* c) {
}

Node* list_insert_int(Node* n, Node* pos, const int value) {
}

Node* list_insert_double(Node* n, Node* pos, const double value) {
}

Node* list_insert_symbol(Node* n, Node* pos, const char* value) {
}
