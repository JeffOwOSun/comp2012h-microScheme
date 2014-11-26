#ifndef HASHTABLEMAP_HPP
#define HASHTABLEMAP_HPP

#include <iostream>
#include <iterator>
#include <utility>
#include <stdexcept>

using namespace std;

template <class Key, class T>
class hashtablemap
{
  typedef hashtablemap<Key, T>     Self;

public:
  typedef Key                key_type;
  typedef T                  data_type;
  typedef T                  mapped_type;
  typedef pair<const Key, T> value_type;
  typedef unsigned int       size_type;
  typedef int                difference_type;

private:
  struct Node {
    Node* next_m;
    value_type value_m;
    bool sentinel_p;

    //default constructor and sentinel constructor
    Node(Node* next = NULL) : next_m(next),
			      sentinel_p(true) {}

    //type conversion constructor from a value_type
    Node(value_type& x) : value_m(x),
			  next_m(NULL),
			  sentinel_p(false) {}

    //copy constructor
    Node(Node& source) : value_m(source.value_m),
			 next_m(source.next_m),
			 sentinel_p(source.sentinel_p) {}

    Node* copy() {
      if (next_m == NULL) {
        return new Node(*this);
      } else {
	//recursively copy the subsequence
	Node* ret = new Node(*this);
	ret -> next_m = next_m -> copy();
      }
    }
  };
  
private:
  template <class value_type,
	    class different_type>
  class _base_iterator {
    typedef value_type& reference;
    typedef value_type* pointer;
    
    // your iterator definition goes here
  public:

    friend class hashtablemap;

    _base_iterator(hashtablemap* map = NULL, Node* node = NULL) : map_m(map), node_m(node) {}
    _base_iterator(const _base_iterator& x) : map_m(x.map_m), node_m(x.node_m){}
    _base_iterator& operator=(const _base_iterator& x) {
      map_m = x.map_m;
      node_m = x.node_m;
      return *this;
    }

    bool operator==(const _base_iterator& x) const {
      return node_m == x.node_m;
    }
    bool operator!=(const _base_iterator& x) const {
      return !(node_m == x.node_m);
    }
    reference operator*() {
      return node_m->value_m;
    }
    pointer operator->() {
      return &(node_m->value_m);
    }
    _base_iterator& operator++() {
      node_m = map_m->_next(node_m);
      return *this;
    }
    _base_iterator& operator++(int) {
      _base_iterator ret(*this);
      node_m = map_m->_next(node_m);
      return ret;
    }
  private:
    hashtablemap* map_m;
    Node* node_m;
  };

public:
  typedef _base_iterator<value_type, difference_type> iterator;
  typedef _base_iterator<const value_type, difference_type> const_iterator;

private:
  //constant integer indicating the length of the hashtable
  //also used in _hash function
  //default value is 47^2
  enum {prime_m = 47*47};

  //variable containing the number of elements in the hash table
  //CANNOT using C++11 way of inline initializer
  size_type size_m;
  
public:
  // default constructor to create an empty map
  hashtablemap() : size_m(0), data_m(_initialize_data()) {}
  
  // overload copy constructor to do a deep copy
  hashtablemap(const Self& x) : size_m(x.size_m) {
    data_m = new Node*[prime_m+1];
    //copy the entire sequence of linked lists
    data_m[0] = x.data_m[0] -> copy();
    //start from the second element, record each sentinel pointer
    size_type i = 1;
    Node* my_iter = data_m[0] -> next_m;
    while (my_iter != NULL) {
      if (my_iter -> sentinel_p) {
	data_m[i] = my_iter;
	++i;
      }
      my_iter = my_iter -> next_m;
    }
  }

  ~hashtablemap() {
    //release the linked list
    _release(data_m[0]);
    delete[] data_m;
  }

  //overload assignment to do a deep copy
  Self& operator=(const Self& x) {
    //use copy constructor once;
    Self tmp_table(x);
    //swap data_m's
    Node** tmp_data = data_m;
    data_m = tmp_table.data_m;
    tmp_table.data_m = tmp_data;

    size_m = x.size_m;
    //supposedly tmp_table will carry the old data and get destructed when out of scope
  }

  // accessors:
  iterator begin() {
    return iterator(this,_next(data_m[0]));
  }
  const_iterator begin() const {
    return const_iterator(this,_next(data_m[0]));
  }
  iterator end() {
    return iterator(this,NULL);
  }
  const_iterator end() const {
    return const_iterator(this,NULL);
  }
  bool empty() const {
    return size_m == 0;
  }
  size_type size() const {
    return size_m;
  }

  // insert/erase
  //the returned iterator is supposed to point either to the newly inserted pair or the pair with equivalent key
  pair<iterator,bool> insert(const value_type& x) {
    //first find the key
    pair<Node*, bool> found = _find(x.first);
    //if it's there, just return the wrapped iterator
    if (found.second) {
      return pair<iterator, bool>(iterator(this,found.first), false);
    }
    //if it's not there, insert a new node at the position
    else {
      Node* ret = _insert(found.first, new Node(x));
      ++size_m;
      return pair<iterator, bool>(iterator(this,ret), true);
    }
  }
  void erase(iterator pos) {
    //first find the key
    Key x = pos -> first;
    //then start from the root of respective bucket to find its parent
    _erase_child(_find_parent(x));
    //_erase_child
    --size_m;
  }
  size_type erase(const Key& x) {
    //first _find
    pair<Node*, bool> found = _find(x);
    //if not found, return zero
    if (!found.second) {
      return 0;
    } else {
      //found
      _erase_child(_find_parent(x));
      --size_m;
      return 1;
    }
  }
  void clear() {
    //basically restore it to the original state
    _release(data_m[0]);
    delete[] data_m;
    data_m = _initialize_data();
    size_m = 0;
  }

  // map operations:
  iterator find(const Key& x) {
    pair<Node*, bool> found = _find(x);
    return iterator(this,found.first);
  }
  const_iterator find(const Key& x) const {
    pair<Node*, bool> found = _find(x);
    return const_iterator(this,found.first);
  }
  size_type count(const Key& x) const {
    return (_find(x).second) ? 1 : 0;
  }
  T& operator[](const Key& k) {
    //_find for the key
    pair<Node*, bool> found = _find(k);
    //if found
    if (found.second) {
      return found.first -> value_m.second;
    }
    //if not found
    else {
      //insert the key, and initialize the value with default constructor
      value_type fresh_pair(k,T());
      Node* ret = _insert(found.first, new Node(fresh_pair));
      ++size_m;
      //call this function once again
      return ret -> value_m.second;
    }
  }

private:

  //the array that stores the hash table
  //Current implementation utilizes a fixed length array
  //an array of lists
  //RULE: lists here have keys in increasing order
  Node** data_m;

  Node** _initialize_data() {
    
    Node** my_data = new Node*[prime_m+1];
    
    //prime_m-th line with a bottom sentinel node
    //this extra line guards the code
    my_data[prime_m] = new Node();
    
    //from prime_m-1 th line down to line 0, each is a sentinel that points directly to the next element
    for (int i = 1; i <= prime_m; ++i) {
    
      my_data[prime_m-i] = new Node(my_data[prime_m-i+1]);
    }
    return my_data;
  }

  //literally remove everything recursively
  //even the invisible sentinels
  void _release(Node* my_node) {
    if (my_node == NULL) return;
    _release(my_node -> next_m);
    delete my_node;
  }
  
  //private find function
  //return value is a pair
  //first field is the iterator to the list
  //second field is another pair, first is the hash, second a boolean
  //for the hash, it's used for insertion
  //for the boolean, it's true if found, false if not
  //when found, iterator is at the found element
  //when not found, iterator is on the position that should be supplied to the insert function and keeps the incrementing property
  pair<Node*, bool> _find(const Key& k) {
    //get the hash
    size_type my_hash = _hash(k);
    //check on that list
    Node* my_iter = data_m[my_hash]->next_m;
    Node* last_iter = data_m[my_hash];
    
    while(!(my_iter -> sentinel_p)) {      
      if (my_iter -> value_m.first == k) return pair<Node*, bool>(my_iter, true);
      //because keys are in increasing order, so if we have already come to a larger key, break and return
      if (my_iter -> value_m.first > k) return pair<Node*, bool>(last_iter, false);
      last_iter = my_iter;
      my_iter = my_iter -> next_m;
    }
    //if come to this place, then the list either empty or all values are smaller than key.
    //directly return the NULL
    return pair<Node*, bool>(last_iter, false);
  }
  //const version
  pair<const Node*, bool> _find(const Key& k) const {
    //get the hash
    size_type my_hash = _hash(k);
    //check on that list
    Node* my_iter = data_m[my_hash]->next_m;
    Node* last_iter = data_m[my_hash];
    
    while(!(my_iter -> sentinel_p)) {      
      if (my_iter -> value_m.first == k) return pair<const Node*, bool>(my_iter, true);
      //because keys are in increasing order, so if we have already come to a larger key, break and return
      if (my_iter -> value_m.first > k) return pair<const Node*, bool>(last_iter, false);
      last_iter = my_iter;
      my_iter = my_iter -> next_m;
    }
    //if come to this place, then the list either empty or all values are smaller than key.
    //directly return the NULL
    return pair<const Node*, bool>(last_iter, false);
  }
  //only needed to be called when key is already there
  const Node* _find_parent(const Key& k) const {
    //first find itself
    pair<const Node*, bool> found = _find(k);
    //if not found, just return the found value cuz it contains the parent
    if (!found.second) {
      return found.first;
    } else {
      //found
      //calculate the hash
      size_type my_hash = _hash(k);
      //iterate the bucket
      const Node* last_iter = data_m[my_hash];
      for (const Node* my_iter = data_m[my_hash] -> next_m;
	   !my_iter -> sentinel_p;
	   my_iter = my_iter -> next_m) {
	if (my_iter -> value_m.first) return last_iter;
	last_iter = my_iter;
      }
      return last_iter;
    }
  }
  //non const find parent
  Node* _find_parent(const Key& k){
    //first find itself
    pair<Node*, bool> found = _find(k);
    //if not found, just return the found value cuz it contains the parent
    if (!found.second) {
      return found.first;
    } else {
      //found
      //calculate the hash
      size_type my_hash = _hash(k);
      //iterate the bucket
      Node* last_iter = data_m[my_hash];
      for (Node* my_iter = data_m[my_hash] -> next_m;
	   !my_iter -> sentinel_p;
	   my_iter = my_iter -> next_m) {
	if (my_iter -> value_m.first) return last_iter;
	last_iter = my_iter;
      }
      return last_iter;
    }
  }

  
  //get the next element of pos. special care for end elements of lists
  //_next will never stop on sentinel nodes
  //the returned pointer value either points to a valide value node or NULL indicating the end
  Node* _next(Node* const pos) {
    if (pos == NULL) return NULL;
    //advance the pointer, so that it points to the next valid value node
    Node* my_pointer = pos;
    do {
      my_pointer = my_pointer -> next_m;
    } while (my_pointer != NULL && my_pointer -> sentinel_p);
    return my_pointer;
  }

  //insertion after the node pos
  //_insert won't mess with size_m
  //it's only supposed to know about the node structure
  Node* _insert(Node* const pos, Node* const fresh_node) {
    fresh_node -> next_m = pos -> next_m;
    pos -> next_m = fresh_node;
    return fresh_node;
  }

  void _erase_child(Node* const parent_pos)
  {
    Node* const pos = parent_pos -> next_m;
    if (pos == NULL) throw runtime_error("erasing NULL");
    if (pos -> sentinel_p) throw runtime_error("trying to erase a sentinel");
    parent_pos -> next_m = pos -> next_m;
    delete pos;
  }
   
  //private hash function
  //take an object to hash
  //returns the corresponding hash
  size_type _hash(const int my_key) const{
    //cast my_key to an array of chars
    char* char_arr = new char[sizeof(my_key)];
    memcpy(char_arr, &my_key, sizeof(my_key));
    //calculate the hash
    size_type result = 0;
    
    for (int i=0; i < sizeof(my_key); ++i) {
      size_type partial_result = char_arr[i];
      for (int j=0; j < i; ++j) {
	partial_result = (partial_result << 8) % prime_m;
      }
      result = (result + partial_result) % prime_m;
    }
    return result;
  }

  size_type _hash(const string my_key) const {
    const char* char_arr = my_key.c_str();
    //calculate the hash
    size_type result = 0;
    
    for (int i=0; i < my_key.length(); ++i) {
      size_type partial_result = char_arr[i];
      for (int j=0; j < i; ++j) {
	partial_result = (partial_result << 8) % prime_m;
      }
      result = (result + partial_result) % prime_m;
    }

    return result;
  }

};
#endif //HASHTABLEMAP_HPP
