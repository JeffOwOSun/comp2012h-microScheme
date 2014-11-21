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
    // your iterator definition goes here
  };
  class const_iterator {
    // like iterator, but points to a const
  };

public:
  // default constructor to create an empty map
  hashtablemap() {}

  // overload copy constructor to do a deep copy
  hashtablemap(const Self& x) {}

  // overload assignment to do a deep copy
  Self& operator=(const Self& x) {}

  // accessors:
  iterator begin() {}
  const_iterator begin() const {}
  iterator end() {}
  const_iterator end() const {}
  bool empty() const {}
  size_type size() const {}

  // insert/erase
  pair<iterator,bool> insert(const value_type& x) {}
  void erase(iterator pos) {}
  size_type erase(const Key& x) {}
  void clear() {}

  // map operations:
  iterator find(const Key& x) {}
  const_iterator find(const Key& x) const {}
  size_type count(const Key& x) const {}
  T& operator[](const Key& k) {}

};
