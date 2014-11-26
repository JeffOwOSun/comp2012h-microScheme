/**
 * \file test.cpp
 * \brief Test the hashtablemap
 */
#include "hashtablemap.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  hashtablemap<int, int> my_map;
  //test []
  //test insert
  //test find
  //test delete

  //test iterator
  //test ++
  //test * and ->

  vector<int> my_vector;
  for(int i = 0; i < 10; ++i) my_vector.push_back(i);

  random_shuffle(my_vector.begin(), my_vector.end());

  cout << "my random sequence is : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_vector[i] << ((i == 9) ? "\n" : " ");
  }

  cout << "their respect values r: ";
  for(int i = 0; i < 10; ++i) {
    cout << i << ((i == 9) ? "\n" : " ");
  }

  cout << "size before insertion: " << my_map.size() << endl;
  
  for(int i = 0; i < 10; ++i) {
    my_map[my_vector[i]] = i;
  }

  cout << "size after inserting 10 keys: " << my_map.size() << endl;

  cout << "counts for key 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map.count(i) << ((i == 9) ? "\n" : " ");
  }
  
  cout << "values of keys 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map[i] << ((i == 9) ? "\n" : " ");
  }

  cout << "deleting key 4 ...\n";
  my_map.erase(4);
  cout << "size after deletion: " << my_map.size() <<"\n";
  
  cout << "counts for key 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map.count(i) << ((i == 9) ? "\n" : " ");
  }
  /*
  cout << "values of keys 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map[i] << ((i == 9) ? "\n" : " ");
  }
  */

  cout << endl;
  cout << "traversal using iterator \n";
  for (hashtablemap<int,int>::iterator my_iter = my_map.begin(); my_iter != my_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }

  cout << endl;
  cout << "traversal using const_iterator \n";
  const hashtablemap<int,int> my_const_map = my_map;
  for (hashtablemap<int,int>::const_iterator my_iter = my_const_map.begin(); my_iter != my_const_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }

  cout << endl;
  cout << "now testing calling insert function\n";
  pair<hashtablemap<int,int>::iterator, bool> ret = my_map.insert(pair<int,int>(998, 113));
  cout << "the bool returned : " << ret.second <<"\n";
  cout << "the value pair revealed by the ret in (key,val) : ( " << ret.first -> first <<" , "<< ret.first -> second <<" )\n";
  cout << "traversal using iterator \n";
  for (hashtablemap<int,int>::iterator my_iter = my_map.begin(); my_iter != my_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }

  cout << endl;
  cout << "now try a failing erase \n";
  cout << "the number of removed pair is : " << my_map.erase(888) << "\n";
  cout << "traversal using iterator \n";
  for (hashtablemap<int,int>::iterator my_iter = my_map.begin(); my_iter != my_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }

  cout << endl;
  cout << "now try to erase using iterator" <<endl;
  hashtablemap<int,int>::iterator my_iter = my_map.begin();
  cout << "element to be erased : ";
  cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  my_map.erase(my_iter);
  cout << "After erase: traversal using iterator \n";
  for (hashtablemap<int,int>::iterator my_iter = my_map.begin(); my_iter != my_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }

  cout << endl;
  cout << "gonna clear \n";
  my_map.clear();
  cout << "After clear: traversal using iterator \n";
  for (hashtablemap<int,int>::iterator my_iter = my_map.begin(); my_iter != my_map.end(); ++my_iter) {
    cout << "key: " << my_iter -> first << " value: "<< my_iter -> second << "\n" ;
  }
  cout << "restore the table \n";
  cout << "my random sequence is : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_vector[i] << ((i == 9) ? "\n" : " ");
  }

  cout << "their respect values r: ";
  for(int i = 0; i < 10; ++i) {
    cout << i << ((i == 9) ? "\n" : " ");
  }

  cout << "size before insertion: " << my_map.size() << endl;
  
  for(int i = 0; i < 10; ++i) {
    my_map[my_vector[i]] = i;
  }

  cout << "size after inserting 10 keys: " << my_map.size() << endl;

  cout << "counts for key 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map.count(i) << ((i == 9) ? "\n" : " ");
  }
  
  cout << "values of keys 0..9 : ";
  for(int i = 0; i < 10; ++i) {
    cout << my_map[i] << ((i == 9) ? "\n" : " ");
  }  
  
  return 0;
}
  
