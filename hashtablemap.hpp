#ifndef HASHTABLEMAP_HPP
#define HASHTABLEMAP_HPP

#include <iostream>
#include <list>
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

public:
  class iterator {
    typedef value_type value_type;
    typedef difference_type difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    
    // your iterator definition goes here
  public:

    friend class hashtablemap;

    iterator() : list_iter_m(data_m[0].begin()) {}
    iterator(typename list<value_type>::iterator my_iter) : list_iter_m(my_iter) {}
    iterator(const iterator& x) : list_iter_m(x.list_iter_m) {}
    iterator& operator=(const iterator& x) {
      list_iter_m = x.list_iter_m;
      return *this;
    }

    bool operator==(const iterator& x) const {
      return list_iter_m == x.list_iter_m;
    }
    bool operator!=(const iterator& x) const {
      return list_iter_m != x.list_iter_m;
    }
    reference operator*() {
      return *list_iter_m;
    }
    pointer operator->() {
      return &(*list_iter_m);
    }
    iterator& operator++() {
      list_iter_m = _next(list_iter_m);
      return *this;
    }
    iterator& operator++(int) {
      iterator& ret(*this);
      list_iter_m = _next(list_iter_m);
      return ret;
    }
  private:
    typename list<hashtablemap::value_type>::iterator list_iter_m;
  };

  
  class const_iterator {
    typedef const value_type value_type;
    typedef difference_type difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    
    // your const_iterator definition goes here
  public:

    friend class hashtablemap;

    const_iterator() : list_iter_m(data_m[0].begin()) {}
    const_iterator(typename list<value_type>::const_iterator my_iter) : list_iter_m(my_iter) {}
    const_iterator(const const_iterator& x) : list_iter_m(x.list_iter_m) {}
    const_iterator& operator=(const const_iterator& x) {
      list_iter_m = x.list_iter_m;
      return *this;
    }

    bool operator==(const const_iterator& x) const {
      return list_iter_m == x.list_iter_m;
    }
    bool operator!=(const const_iterator& x) const {
      return list_iter_m != x.list_iter_m;
    }
    reference operator*() {
      return *list_iter_m;
    }
    pointer operator->() {
      return &(*list_iter_m);
    }
    const_iterator& operator++() {
      list_iter_m = _next(list_iter_m);
      return *this;
    }
    const_iterator& operator++(int) {
      const_iterator& ret(*this);
      list_iter_m = _next(list_iter_m);
      return ret;
    }
  private:
    typename list<hashtablemap::value_type>::iterator list_iter_m;
  };
 
public:
  // default constructor to create an empty map
  hashtablemap() {}

  // overload copy constructor to do a deep copy
  hashtablemap(const Self& x) {
    for (size_type i = 0; i < prime_m; ++i) {
      list<value_type> tmp_list = x.data_m[i];
      swap(data_m[i], tmp_list);      
    }
  }

  // overload assignment to do a deep copy
  Self& operator=(const Self& x) {
    for (size_type i = 0; i < prime_m; ++i) {
      list<value_type> tmp_list = x.data_m[i];
      swap(data_m[i], tmp_list);
    }
  }

  // accessors:
  iterator begin() {
    //search the hash table until the list is not empty
    for (size_type i=0; i < prime_m; ++i) {
      if (data_m[i].size() > 0) {
	//return the iterator pointing to the first list item
	return iterator(data_m[i].begin());
      }
    }
    //here, we just return the 0 position, constructed by the default constructor of iterator
    return iterator();
  }
  const_iterator begin() const {
    for (size_type i=0; i < prime_m; ++i) {
      if (data_m[i].size() > 0) {
	//return the iterator pointing to the first list item
	return const_iterator(data_m[i].begin());
      }
    }
    //here, we just return the 0 position, constructed by the default constructor of iterator
    return const_iterator();
  }
  iterator end() {
    //return the iterator that wraps in itself the end() of the last non zero list
    for (size_type i = prime_m - 1; i >= 0; --i) {
      if (data_m[i].size() > 0) {
	return iterator(data_m[i].end());
      }
    }
    return iterator();
  }
  const_iterator end() const {
  //return the iterator that wraps in itself the end() of the last non zero list
    for (size_type i = prime_m - 1; i >= 0; --i) {
      if (data_m[i].size() > 0) {
	return const_iterator(data_m[i].end());
      }
    }
    return const_iterator();
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
    //first search for the key
    pair<iterator, bool> found = find(x.first);
    //if it's already there, return the found iterator and a false
    if (found.second) {
      return pair<iterator, bool>(found.first, false);
    } else {
      //found.first is the place to insert
      data_m[_hash(x.first)].insert(found.first, x);
      ++size_m;
      return pair<iterator, bool>(find(x.first), true);
    }
    
  }
  void erase(iterator pos) {
    //first find the pos
    //erase it
    data_m[_hash(pos->first)].erase(pos.list_iter_m);
    --size_m;
  }
  size_type erase(const Key& x) {
    iterator my_iter = find(x);
    if (my_iter == end()) {
      return 0;
    } else {
      erase(my_iter);
      return 1;
    }
  }
  void clear() {
    for (size_type i = 0; i < prime_m; ++i) {
      data_m[i].clear();
    }
    size_m = 0;
  }

  // map operations:
  iterator find(const Key& x) {
    pair<list<value_type>::iterator, bool> found = _find(x);
    if (found.second) {
      //wrap the list iterator into the custom iterator and return
      return iterator(found.first);
    } else {
      return end();
    }
  }
  const_iterator find(const Key& x) const {
    pair<list<value_type>::iterator, bool> found = _find(x);
    if (found.second) {
      //wrap the list iterator into the custom iterator and return
      return const_iterator(found.first);
    } else {
      return end();
    }
  }
  size_type count(const Key& x) const {
    return (_find(x).second) ? 1 : 0;
  }
  T& operator[](const Key& k) {
    //_find for the key
    pair<list<value_type>::iterator, bool> found = _find(k);
    //if found
    if (found.second) {
      return found.first -> second;
    }
    //if not found
    else {
      //insert the key, and initialize the value with default constructor
      value_type fresh_pair(k,T());
      data_m[_hash(k)].insert(found.first, fresh_pair);
      ++size_m;
      //call this function once again
      return operator[](k);
    }
  }

private:
  //constant integer indicating the length of the hashtable
  //also used in _hash function
  //default value is 47^2
  enum {prime_m = 47*47};

  //the array that stores the hash table
  //Current implementation utilizes a fixed length array
  //an array of lists
  //RULE: lists here have keys in increasing order
  list<value_type> data_m[prime_m];

  //variable containing the number of elements in the hash table
  //using C++11 way of inline initializer
  size_type size_m = 0;

  //private find function
  //return value is a pair
  //first field is the iterator to the list
  //second field is another pair, first is the hash, second a boolean
  //for the hash, it's used for insertion
  //for the boolean, it's true if found, false if not
  //when found, iterator is at the found element
  //when not found, iterator is on the position that should be supplied to the insert function and keeps the incrementing property
  pair<list<value_type>::iterator, bool> _find(const Key& k) {
    //get the hash
    size_type my_hash = _hash(k);
    //check on that list
    for (list<value_type>::iterator my_iter = data_m[my_hash].begin(); my_iter != data_m[my_hash].end(); ++my_iter) {
      if (my_iter -> first == k) return pair<list<value_type>::iterator, bool>(my_iter, true);
      //because keys are in increasing order, so if we have already come to a larger key, break and return
      if (my_iter -> first > k) return pair<list<value_type>::iterator, bool>(my_iter, false);
    }
    //if come to this place, then the list either empty or all values are smaller than key.
    //directly return the end.
    return pair<list<value_type>::iterator, bool>(data_m[my_hash].end(), false);
  }

  //get the next element of pos. special care for end elements of lists
  list<value_type>::iterator _next(const list<value_type>::iterator& pos) {
    //assuming pos is dereferenceable
    //it actually must be, otherwise we cannot know where is the iterator
    
    //calculate the hash
    try {
      size_type my_hash = _hash(pos->first);
    } catch (...) {
      throw runtime_error("iterator pos undereferenceable!");
    }			
    //take ++ of the iterator
    list<value_type>::iterator my_iter = pos;
    ++my_iter;
    //if the iterator is not end of list, just return it
    if (my_iter != data_m[my_hash].end()) {
      return my_iter;
    }
    //if it's the end of list, take the begin of the next available. if none, just return end
    else {
      for (size_type i = my_hash + 1; i < prime_m; ++i) {
	if (data_m[i].size() > 0) return data_m[i].begin();
      }
      return data_m[my_hash].end();
    }
  }
   
  //private hash function
  //take an object to hash
  //returns the corresponding hash
  size_type _hash(const Key& my_key) const{
    //cast my_key to an array of chars
    char* char_arr = new char[sizeof(my_key)];
    memcpy(char_arr, &my_key, sizeof(my_key));
    //calculate the hash
    size_type result = 0;
    
    for (int i=0; i < sizeof(my_key); ++i) {
      size_type partial_result = char_arr[i];
      for (int j=0; j < i; ++j) {
	partial_result = (partial_result << 8) % my_prime;
      }
      result = (result + partial_result) % my_prime;
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
	partial_result = (partial_result << 8) % my_prime;
      }
      result = (result + partial_result) % my_prime;
    }

    return result;
  }

};
#endif //HASHTABLEMAP_HPP
