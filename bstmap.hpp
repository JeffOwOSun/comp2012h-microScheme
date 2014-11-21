#ifndef BSTMAP_HPP
#define BSTMAP_HPP

#include<utility>
#include<iterator>
using namespace std;

template <class Key, class T>
class bstmap
{
  typedef bstmap<Key, T>     Self;

public:
  typedef Key                key_type;
  typedef T                  data_type;
  typedef T                  mapped_type;
  typedef pair<const Key, T> value_type;
  typedef unsigned int       size_type;
  typedef int                difference_type;

public:
  class iterator {
  public:
    typedef std::input_iterator_tag iterator_category;
    typedef value_type value_type;
    typedef difference_type difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    //the ambient class should always be a friend
    friend class bstmap;

    // your iterator definition goes here
    iterator(bstmap* map, Node* node = NULL) : map_m(map), node_m(node) {}
    iterator(const iterator& x) : map_m(x.map_m), node_m(x.node_m) {}
    iterator& operator=(const iterator& x) {
      map_m = x.map_m;
      node_m = x.node_m;
      return *this;
    }

    bool operator==(const iterator& x) const {
      return node_m == x.node_m;
    }

    bool operator!=(const iterator& x) const {
      return !(*this == x);
    }
    
    reference operator*() {
      return node_m->value_m;
    }

    pointer operator->() {
      return &(node_m->value_m);
    }

    iterator& operator++() {
      node_m = map_m -> _successor(node_m);
      return node_m;
    }

    iterator& operator++(int) {
      iterator ret(*this);
      node_m = map_m -> _successor(node_m);
      return ret;
    }
    
  private:
    bstmap* map_m;
    Node* node_m;
    
  };
  class const_iterator {
    // like iterator, but points to a const
  };

public:
  // default constructor to create an empty map
  bstmap():size_m(0),root_m(NULL) {}

  // overload copy constructor to do a deep copy
  bstmap(const Self& x) {}

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

private:
  /**
   * \brief Algorithmic function, find the designated node based on the key supplied.
   * \param x Reference to the key to be found.
   * \return A pair whose first is the pointer to a node, and second is a boolean. When second is true, find is successful and first is the Node found. When second is false, find is unsuccessful and first is the Node under which the key would be if inserted.
   */
  pair<Node*, bool> _find(const Key& x) const {
    pair<Node*, bool> ret(NULL,false);
    Node* curr_parent = NULL;
    Node* curr = root_m;
    while (curr != NULL) {
      curr_parent = curr;
      if (x < curr->value_m.first) {
	curr = curr->left_m;
      } else if (curr->value_m.first < x) {
	curr = curr->right_m;
      } else {
	//curr is the node being searched for
	ret.first = curr;
	ret.second = true;
	return ret;
      }
    }
    //here nothing is found
    ret.first = curr_parent;
    return ret;
  }

  //return <Node*, bool> if second is false that means the thing is already there
  //here our bool simply is a sort of status code, indicating success or failure of the operation
  pair<Node*, bool> _insert(const value_type& x) {
    //try to find the key
    pair<Node*, bool> found = _find(x.first);
    //if it's there
    //return the found position and a false
    if (found.second) {
      found.second = false;
      return found;
    }
    //if it's not there
    else {
      //make a new node
      Node* my_node = new Node(x);
      //set its parent to be the found node
      my_node.parent_m = found.first;
      if (found.first -> value_m.first < x.first) {
	found.first -> right_m = my_node;
      } else {
	found.first -> left_m = my_node;
      }
      return pair<Node*, bool>(my_node, true);
    }
  }

  //deletion
  bool _delete(Node* const my_node) {
    
  }

  //find the min of the subtree rooted at my_node
  Node* _min(Node* const my_node) {
    if (my_node == NULL) return NULL;
      
    Node* curr_node = my_node;
    while (curr_node -> left_m != NULL) {
      curr_node = curr_node -> left_m;
    }
    return curr_node; 
  }
  
  //find the max of the subtree rooted at my_node
  Node* _max(Node* const my_node) {
    if (my_node == NULL) return NULL;

    Node* curr_node = my_node;
    while (curr_node -> right_m != NULL) {
      curr_node = curr_node -> right_m;
    }
    return curr_node;
  }

  Node* _successor(Node* my_node) const {
    if (my_node == NULL) return NULL;
    //case 1, if my_node has a right child, find the min of right subtree
    if (my_node -> right_m != NULL) {
      return _min(my_node -> right_m);
    }
    //margin case: my_node is root
    else if (my_node -> parent_m == NULL) {
      //I'm root, and no successor
      return NULL;
    }
    //case 2, if my_node doesn't have a right child
    //case 2.1, if my_node is a left child, return its parent
    else if (my_node -> parent_m -> left_m == my_node) {
      return my_node -> parent_m;
    }
    //case 2.2, if my_node is a right child, go back to its parent until it becomes a left child
    else {
      Node* curr_node = my_node;
      while (curr_node -> parent_m != NULL) {
	if (curr_node -> parent_m -> left_m == my_node) {
	  return curr_node -> parent_m;
	} else curr_node = curr_node -> parent_m;
      }
      return NULL;
    }
  }
  
  struct Node {
    Node* parent_m;
    Node* left_m;
    Node* right_m;
    value_type value_m;

    //type conversion constructor from a value_type
    Node(value_type& x) : value_m(x),
			  left_m(NULL),
			  right_m(NULL),
			  parent_m(NULL) {}

    //copy constructor
    Node(Node& source) : data_m(source.value_m),
			 left_m(source.left_m),
			 right_m(source.right_m),
			 parent_m(source.parent_m) {}
  };
  
  Node* root_m;
  int size_m;

  //atomic operations
  
};

#endif //BSTMAP_HPP
