#ifndef BSTMAP_HPP
#define BSTMAP_HPP

#include<iostream>
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

private:
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
    Node(Node& source) : value_m(source.value_m),
			 left_m(source.left_m),
			 right_m(source.right_m),
			 parent_m(source.parent_m) {}
  };

  
  template <class value_type,
	    class difference_type,
	    class pointer,
	    class reference>
  class _base_iterator {
  public:
    typedef std::input_iterator_tag iterator_category;

    //the ambient class should always be a friend
    friend class bstmap;

    // your iterator definition goes here
    _base_iterator(bstmap* map, Node* node = NULL) : map_m(map), node_m(node) {}
    _base_iterator(const _base_iterator& x) : map_m(x.map_m), node_m(x.node_m) {}

    _base_iterator& operator=(const _base_iterator& x) {
      map_m = x.map_m;
      node_m = x.node_m;
      return *this;
    }

    bool operator==(const _base_iterator& x) const {
      return node_m == x.node_m;
    }

    bool operator!=(const _base_iterator& x) const {
      return !(*this == x);
    }
    
    reference operator*() {
      return node_m->value_m;
    }

    pointer operator->() {
      return &(node_m->value_m);
    }

    _base_iterator& operator++() {
      node_m = map_m -> _successor(node_m);
      return node_m;
    }

    _base_iterator& operator++(int) {
      iterator ret(*this);
      node_m = map_m -> _successor(node_m);
      return ret;
    }
    
  private:
    bstmap* map_m;
    Node* node_m;
    
  };

public:
  typedef _base_iterator<value_type, difference_type, value_type*, value_type&> iterator;
  typedef _base_iterator<const value_type, difference_type, value_type*, value_type&> const_iterator;

public:
  // default constructor to create an empty map
  bstmap():size_m(0),root_m(NULL) {}

  // overload copy constructor to do a deep copy
  bstmap(const Self& x) {
    size_m = x.size_m;
    root_m = _recursive_copy(x.root_m);
  }

  // overload assignment to do a deep copy
  Self& operator=(const Self& x) {
  }

  // accessors:
  iterator begin() {
    //get the min of the tree, wrap it into an iterator
    return iterator(this, _min(root_m));
  }
  const_iterator begin() const {
    return const_iterator(this, _min(root_m));
  }
  //called when this is non const
  iterator end() {
    return iterator(this, NULL);
  }
  //called when this is const
  const_iterator end() const {
    return const_iterator(this, NULL);
  }
  bool empty() const {
    return size_m > 0;
  }
  size_type size() const {
    return size_m;
  }
 
  // insert/erase
  pair<iterator,bool> insert(const value_type& x) {
    pair<Node*, bool> inserted = _insert(x);
    return pair<iterator, bool>(iterator(this, inserted.first), inserted.second);
  }
  void erase(iterator pos) {
    _erase(pos.node_m);
  }
  size_type erase(const Key& x) {
    //first find it
    pair<Node*, bool> found = _find(x);
    //then erase
    if (found.second) {
      if (_erase(found.first)) {
	return 1;
      } 
      else {
	return 0;
      }
    }
    else {
      return 0;
    }
  }
  
  void clear() {
    _clear(root_m);
  }

  // map operations:
  iterator find(const Key& x) {
    //call the private _find function
    pair<Node*, bool> found = _find(x);
    //judging from the return value, return the corresponding iterator
    if (found.second) {
      return iterator(this, found.first);
    } else {
      return end();
    }
  }
  const_iterator find(const Key& x) const {
    //call the private _find function
    pair<Node*, bool> found = _find(x);
    //judging from the return value, return the corresponding iterator
    if (found.second) {
      return const_iterator(this, found.first);
    } else {
      return end();
    }
  }
  size_type count(const Key& x) const {
    //call _find once
    pair<Node*, bool> found = _find(x);
    //none found, return zero; found, return one
    return found.second ? 1 : 0;
  }
  T& operator[](const Key& k) {
    //first find the key
    pair<Node*, bool> find_ret = _find(k);
    //if found, retrieve the value and return
    if (find_ret.second) {
      return find_ret.first -> value_m.second;
    } 
    //if not found, create the node with the default parameters
    else {
      T tmp_val;
      value_type my_value(k, tmp_val); //supposedly the second field of the pair contains a default value
      
      pair<Node*, bool> insert_ret = _insert(my_value);
      //return the second field of the newly created pair
      
      return insert_ret.first -> value_m.second;
    }
  }

  //private:
public: //debug only
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
    //if root_m is empty, just insert there
    if (root_m == NULL) {
      //create a new node with the given value
      value_type val(x); //to avoid conversion from const value_type to value_type
      Node* fresh_node = new Node(val);
      //set its parent to be NULL
      fresh_node -> parent_m = NULL;
      //insert it under root_m
      root_m = fresh_node;
      //set size to be 1
      size_m = 1;
      //return the new node pointer and a true
      return pair<Node*, bool>(fresh_node, true);
    }

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
      value_type val(x);
      Node* my_node = new Node(val);
      //set its parent to be the found node
      my_node->parent_m = found.first;
      //prevent seg fault if found.first is NULL
      if (found.first) {
	if (found.first -> value_m.first < x.first) {
	  found.first -> right_m = my_node;
	} else {
	  found.first -> left_m = my_node;
	}
      }
      ++size_m;
      return pair<Node*, bool>(my_node, true);
    }
  }

  //erase the given node while preserving the tree structure
  bool _erase(Node* const my_node) {
    //case 1, my_node is a leaf node
    if (my_node->left_m == NULL && my_node->right_m == NULL) {
      //if my_node here is the root
      if (my_node == root_m) {
	root_m = NULL;
	delete my_node;
	size_m = 0;
      } else {
	//my_node has a parent, clear itself from its parent
	if (my_node -> parent_m -> left_m == my_node) {
	  my_node -> parent_m -> left_m = NULL;
	} else {
	  my_node -> parent_m -> right_m = NULL;
	}
	delete my_node;
	--size_m;
      }
      return true;
    } 
    //case 2, my_node has one child
    else if (my_node -> left_m == NULL || my_node -> right_m == NULL) {
      if (my_node == root_m) {
	//if my_node here is the root
	root_m = (my_node -> left_m != NULL) ? (my_node -> left_m) : (my_node -> right_m);
      } else {
	// my_node has a parent
	if (my_node -> parent_m -> left_m == my_node) {
	  my_node -> parent_m -> left_m = (my_node -> left_m != NULL) ? (my_node -> left_m) : (my_node -> right_m);
	} else {
	  my_node -> parent_m -> right_m = (my_node -> left_m != NULL) ? (my_node -> left_m) : (my_node -> right_m);
	}
      }
      delete my_node;
      --size_m;
      return true;
    }
    //case 3, my_node has two children
    else {
      //fint its successor, swap the values, and delete the successor
      Node* my_successor = _successor(my_node);
      _swap_val(my_node, my_successor);
      return _erase(my_successor);
    }
  }

  //empty the tree rooted at given node
  void _clear(Node* const my_node) {
    if (my_node == NULL) return;
    //recursively _clear subtrees, in postorder traversal sequence
    _clear(my_node -> left_m);
    _clear(my_node -> right_m);
    if (root_m == my_node) root_m = NULL;
    delete my_node;
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

  Node* _successor(Node* my_node) {
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



  //swap the values of the given two nodes
  void _swap_val(Node* my_first, Node* my_second) {
    value_type tmp_val(my_first -> value_m);
    my_first -> value_m.first = my_second -> value_m.first;
    my_first -> value_m.second = my_second -> value_m.second;
    my_second -> value_m.first = tmp_val.first;
    my_second -> value_m.second = tmp_val.second;
  }

  Node* _recursive_copy(Node* my_root) {
    if (my_root == NULL) return NULL;
    //first copy the root node
    Node* ret = new Node(my_root);
    //then recursively copy the children and substitute root's children
    ret->left_m = _recursive_copy(ret->left_m);
    ret->right_m = _recursive_copy(ret->right_m);

    //set parent for children
    ret->left_m->parent_m = ret;
    ret->right_m->parent_m = ret;
    ret->parent_m = NULL;

    return ret;
  }
  
  
  Node* root_m;
  int size_m;
};

#endif //BSTMAP_HPP
