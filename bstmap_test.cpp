#include "bstmap.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  bstmap<int, int> my_map;

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
  
  return 0;
}
