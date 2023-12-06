#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

using namespace std;


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  ~List() {
    clear();
  }

  List(const List &other)
    : first(nullptr), last(nullptr) {
      copy_all(other);
  }

  List() : first(nullptr), last(nullptr) { }

  List & operator=(const List &rhs) {
    if (this == &rhs) { return *this; } 
    clear();
    copy_all(rhs);
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    if (first == nullptr && last == nullptr) {
      return true;
    }
    return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    int count = 0;
    Node *temp = first;
    while (temp != nullptr) {
      count++;
      temp = temp->next;
    }
    return count;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;

  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *p = new Node;
    p->datum = datum;
    p->next = first;
    first = p;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *new_node = new Node;
    new_node->datum = datum;
    new_node->next = nullptr;
    new_node->prev = last;
    if (empty()) {
      first = last = new_node;
    } 
    else {
      last->next = new_node;
      new_node->prev = last;
      last = new_node;

			//last->next = new_node;
      // last->next = new_node;
			// last = new_node;
			//last->prev->next = last;
      /* cout << "else applies" << endl;
      new_node->prev = last;
      cout << "prev" << endl;
      //last->next = new_node;
      cout << "new next" << endl;
      last = last->next; */
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *new_first = first->next;  // temporary keeps track of new first
    delete first;
    first = new_first;

    /* assert(!empty());
    Node *temp = first;
    first = first->next;
    delete temp; */
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *temp = last;
    last = last->prev;
    delete temp;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while(!empty()) {
      pop_front();
    }
  }


  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    assert(empty());
    //cout << "size: " << other.size() << endl;
    
    for (Node *i = other.first; i != nullptr; i = i->next) {
      //cout << "data: " << i->datum << endl;
      push_back(i->datum);
      //cout << "current size: " << size() << endl;
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

    

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      //assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const {
      //assert(node_ptr);
      return node_ptr->datum;
    }
 
    Iterator & operator++() {
      //assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }
 
    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }
 
    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

    Iterator & operator=(const Iterator &rhs)  {
      node_ptr = rhs.node_ptr;
      return *this;
    } 
        

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) { }
    Iterator() : node_ptr(nullptr) { }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
		if (begin() == i){
			pop_front();
		}
		else if (last == i.node_ptr){
			pop_back();
		}
		else{
			i.node_ptr->prev->next = i.node_ptr->next;
			i.node_ptr->next->prev = i.node_ptr->prev;
			delete i.node_ptr; 
      i.node_ptr = nullptr;
		}
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {

    //assert(!(i == end()));
		if (begin() == i || empty()){
			push_front(datum);
		}
		else if (i == end()){
			push_back(datum);
		}
		else{
			Node *temp = new Node;
			temp->datum = datum;
			temp->prev = i.node_ptr->prev;
			temp->next = i.node_ptr;
			temp->next->prev = temp;
			temp->prev->next = temp;
		}
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
