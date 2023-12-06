#ifndef MAP_H
#define MAP_H
/* Map.h
 *
 * Abstract data type representing a map of key-value pairs with
 * unique keys. A subset of the std::map interface
 * http://www.cplusplus.com/reference/map/map/
 * Project UID db1f506d06d84ab787baf250c265e24e
 *
 * By Andrew DeOrio <awdeorio@umich.edu>
 *    Amir Kamil    <akamil@umich.edu>
 *    James Juett   <jjuett@umich.edu>
 * Updated
 *   2016-11-23
 *
 * DO NOT modify the public interface. Modify anything else you need to.
 */

#include "BinarySearchTree.h"
#include <cassert>  //assert
#include <utility>  //pair

template <typename Key_type, typename Value_type,
          typename Key_compare=std::less<Key_type> // default argument
         >
class Map {

private:
  // Type alias for an element, the combination of a key and mapped
  // value stored in a std::pair.
  // See http://www.cplusplus.com/reference/utility/pair/
  using Pair_type = std::pair<Key_type, Value_type>;

  // A custom comparator
  class PairComp {
    private:
    //instance of Kep compare
    Key_compare less;
    public:
      bool operator()(Pair_type pair1, Pair_type pair2) const {
        return less(pair1.first, pair2.first);
        //return instance of Key_compare(pair1 key, pair2key);
      } 
  };

public:

  // OVERVIEW: Maps are associative containers that store elements
  // formed by a combination of a key value and a mapped value,
  // following a specific order.
  //
  // NOTE: This Map should be represented using a BinarySearchTree that
  //       stores (key, value) pairs. See Pair_type above. You will
  //   also need to define an appropriate comparator type (PairComp) for the
  //       BinarySearchTree to use in comparing elements, so that they
  //       are compared based on the key stored in the first member of
  //       the pair, rather than the built-in behavior that compares the
  //       both the key and the value stored in first/second of the pair.

  // Type alias for iterator type. It is sufficient to use the Iterator
  // from BinarySearchTree<Pair_type> since it will yield elements of 
  //Pair_type
  // in the appropriate order for the Map.
  using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;

  // You should add in a default constructor, destructor, copy
  // constructor, and overloaded assignment operator, if appropriate.
  // If these operations will work correctly without defining them,
  // you should omit them. A user of the class must be able to create,
  // copy, assign, and destroy Maps.


  // EFFECTS : Returns whether this Map is empty.
  bool empty() const;

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
  size_t size() const;

  // EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  // HINT: Since Map is implemented using a BinarySearchTree that stores
  //       (key, value) pairs, you'll need to construct a dummy value
  //       using "Value_type()".
  Iterator find(const Key_type& k) const;

  // MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //
  // HINT:     In the case the key was not found, and you must insert a
  //           new element, use the expression {k, Value_type()} to create
  //           that element. This ensures the proper 
  //           value-initialization is done.
  //
  // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
  Value_type& operator[](const Key_type& k);

  // MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
  std::pair<Iterator, bool> insert(const Pair_type &val);

  // EFFECTS : Returns an iterator to the first key-value pair in this Map.
  Iterator begin() const;

  // EFFECTS : Returns an iterator to "past-the-end".
  Iterator end() const;

private:
  BinarySearchTree<Pair_type, PairComp> map;
  Value_type value = Value_type();
};

// You may implement member functions below using an "out-of-line" definition
// or you may simply define them "in-line" in the class definition above.
// If you choose to define them "out-of-line", here is an example.
// (Note that we're using K, V, and C as shorthands for Key_type,
// Value_type, and Key_compare, respectively - the compiler doesn't
// mind, and will just match them up by position.)

// EFFECTS : Returns an iterator to the first key-value pair in this Map.
template <typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::begin() const {
  return map.begin();
}

// EFFECTS : Returns whether this Map is empty.
template <typename K, typename V, typename C>
bool Map<K, V, C>::empty() const {
  return map.empty();
}

// EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  // HINT: Since Map is implemented using a BinarySearchTree that stores
  //       (key, value) pairs, you'll need to construct a dummy value
  //       using "Value_type()".
template <typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::find(const K& k) const {
  std::pair<K,V> pair1(k, value);
  return map.find(pair1);
}

// MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //
  // HINT:     In the case the key was not found, and you must insert a
  //           new element, use the expression {k, Value_type()} to create
  //           that element. This ensures the proper value-initialization 
  // is done.
  //
  // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
template <typename K, typename V, typename C>
V& Map<K, V, C>::operator[](const K& k) {
  std::pair<K,V> pair1;
  pair1 = {k, value};
  if(find(k) == end()) {
    insert(pair1);
    return find(k)->second;
  }
  return find(k)->second;
}

// MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
template <typename K, typename V, typename C>
std::pair<typename Map<K, V, C>::Iterator, bool> 
      Map<K, V, C>::insert(const Pair_type &val) {
  std::pair<Iterator,bool> pair1;
  if(find(val.first) == end()) {
    pair1 = {map.insert(val), true};
    return pair1;
  }
  else {
    pair1 = {find(val.first), false};
    return pair1;
  }
}

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
template <typename K, typename V, typename C>
size_t Map<K, V, C>::size() const {
  return map.size();
}

// EFFECTS : Returns an iterator to "past-the-end".
template <typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::end() const {
  return map.end();
}

#endif // DO NOT REMOVE!!!
