#include <iostream>
#include "linkedlist.hpp"

int main(int argc, char** argv) {
  using namespace std;

  Node* mixed_list = make_node(make_int(1),NULL);
  Node* pos = mixed_list;

  for (int i = 2; i <= 5; ++i) {
    list_insert_int(mixed_list, pos, i);
    pos = get_next(pos);
  }

  for (int i = 1; i <=5; ++i) {
    double d = i * 0.1;
    list_insert_double(mixed_list, pos, d);
    pos = get_next(pos);
  }

  for (char c = 'a'; c < 'f'; ++c) {
    char* str = new char[1];
    str[0] = c;
    str[1] = '\0';
    list_insert_symbol(mixed_list, pos, str);
    pos = get_next(pos);
  }
  
  // Get all the even positioned elements (head at 1) and delete them
  int size = list_size(mixed_list);

  cout << "Size of the list is " << size << endl;
  cout << *mixed_list;

  // Write test cases for erase and ith
  return EXIT_SUCCESS;
}

