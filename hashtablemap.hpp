/**
 * \file hashtablemap.hpp
 *
 * Template library of hashtablemap using STL interface.
 * Chaining is used when collision happens.
 *
 */

#ifndef HASHTABLEMAP_HPP
#define HASHTABLEMAP_HPP

#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

const int DEFAULT_SIZE = 2011;

/**
 * \class hashtablemap
 * \brief Template class hashtablemap.
 */
template <class Key, class T>
class hashtablemap
{
  typedef hashtablemap<Key, T>                                   Self;
  
public:
  template <typename value_T, typename map_T, typename iterator_T>
  class base_iterator;
  
  typedef Key                                                    key_type;
  typedef T                                                      data_type;
  typedef T                                                      mapped_type;
  typedef std::pair<const Key, T>                                value_type;
  typedef unsigned int                                           size_type;
  typedef int                                                    difference_type;

private:
  typedef unsigned long                                          index_type;
  
  typedef typename std::list<value_type>                         _value_list;
  typedef typename _value_list::iterator                         _value_iterator;
  typedef typename _value_list::const_iterator                   _value_const_iterator;
  
  typedef typename std::vector<_value_list*>                     _bucket_list;
  typedef typename _bucket_list::iterator                        _bucket_iterator;
  typedef typename _bucket_list::const_iterator                  _bucket_const_iterator;

public:
  typedef base_iterator<hashtablemap,
			value_type,
			_value_iterator>                         iterator;
  typedef base_iterator<const hashtablemap,
			const value_type,
			_value_const_iterator>                   const_iterator;

private:
  /**
   * \brief Template function for hashing user-defined key type.
   * \return The hash value.
   */
  template <typename convert_T>
  index_type _hash(convert_T key) const {
    return 0;
  }

  /**
   * \brief Template function for hashing standard string.
   * \return The hash value.
   */
  index_type _hash(std::string key) const {
    int hash = 0;
    for (unsigned int i = 0; i < key.size(); ++i) {
      hash += key[i] * (i + 1);
    }
    return hash % size_m;
  }

  /**
   * \brief Function for deep copying the internal vector.
   * \return Void.
   */
  void _deep_copy(const Self& x) {
    for (int i = 0; i < x.size_m; ++i) {
      bucket_list_m[i] = x.bucket_list_m[i];
    }
  }
  
public:
  /**
   * \class base_iterator
   * \brief Template inner class inside hashtablemap for iterating through the map.
   */
  template <typename map_T, typename value_T, typename iterator_T>
  class base_iterator {
  public:
    typedef std::input_iterator_tag                              forward_iterator;
    typedef value_T                                              value_type;
    typedef map_T                                                map_type;
    typedef iterator_T                                           iterator_type;
    typedef value_type&                                          reference;
    typedef const value_type&                                    const_reference;
    typedef value_type*                                          pointer;
    typedef const value_type*                                    const_pointer;
    
    friend class hashtablemap;

    /**
     * \brief Default constructor
     */
    base_iterator(map_type* my_map = NULL,
		  long my_index = -1,
		  iterator_type my_value_it = _value_iterator() )
      : map_m(my_map),
	bucket_index_m(my_index),
	value_it_m(my_value_it) {}

    /**
     * \brief Copy constructor.
     */
    base_iterator(const base_iterator& it) : map_m(it.map_m),
					     bucket_index_m(it.bucket_index_m),
                                             value_it_m(it.value_it_m) {}

    /**
     * \brief Overloading the = operator for iterator assignment.
     * \return The assigned iterator.
     */
    base_iterator& operator= (const base_iterator& it) {
      map_m = it.map_m;
      bucket_index_m = it.bucket_index_m;;
      value_it_m = it.value_it_m;
      return *this;
    }

    /**
     * \brief Overloading the == operator for iterator comparison.
     * \return True if equal, false if not.
     */
    bool operator== (const base_iterator& it) const {
      return (map_m == it.map_m) &&
	(bucket_index_m == it.bucket_index_m) &&
	(value_it_m == it.value_it_m);
    }

    /**
     * \brief Overloading the != operator for iterator comparison.
     * \return Opposite as the operator== ().
     */
    bool operator!= (const base_iterator& it) const {
      return !(operator==(it));
    }

    /**
     * \brief Overloading the * operator for iterator referencing.
     * \return The reference value.
     */
    reference operator* () {
      return *value_it_m;
    }

    /**
     * \brief Overloading the * operator for const_iterator referencing.
     * \return The const reference value.
     */
    const_reference operator* () const {
      return *value_it_m;
    }

    /**
     * \brief Overloading the -> operator for iterator referencing.
     * \return The address of the reference value.
     */
    pointer operator-> () {
      return &(operator*());
    }

    /**
     * \brief Overloading the -> operator for iterator referencing.
     * \return The address of the const reference value.
     */
    const_pointer operator-> () const {
      return &(operator*());
    }

    /**
     * \brief Overloading the ++ operator for iterator pre-increment.
     * \return The pre-incremented iterator.
     */
    base_iterator& operator++ () {
      if (map_m != NULL && ++value_it_m != map_m->bucket_list_m[bucket_index_m]->end()) {
      } else {
	while (map_m->bucket_list_m[++bucket_index_m] == NULL);
	if (bucket_index_m <= map_m->size_m) {
	  value_it_m = map_m->bucket_list_m[bucket_index_m]->begin();
	} else {
	  map_m = NULL;
	  bucket_index_m = -1;
	  value_it_m = _value_iterator();
	}
      }
      return *this;
    }

    /**
     * \brief Overloading the ++ operator for iterator post-increment.
     * \return The post-incremented iterator.
     */
    base_iterator operator++ (int) {
      base_iterator ret(*this);
      operator++();
      return ret;
    }

  private:
    map_type* map_m;
    long bucket_index_m;
    iterator_type value_it_m;
    
  };

public:
  /**
   * \brief Default constructor.
   */
  hashtablemap() : bucket_list_m(_bucket_list(DEFAULT_SIZE)), size_m(DEFAULT_SIZE) {}

  /**
   * \brief Copy constructor for deep copying.
   */
  hashtablemap(const Self& x) : bucket_list_m(x.bucket_list_m), size_m(x.size_m)  {
    _deep_copy(x);
  }

  /**
   * \brief Destructor.
   */
  ~hashtablemap() {
    clear();
  }

  /**
   * \brief Overloading the = operator for deep copying.
   * \return The copying object.
   */
  Self& operator= (const Self& x) {
    _deep_copy(x);
    return *this;
  }

  /**
   * \brief Accessor.
   * \return Iterator to the position of the first element.
   */
  iterator begin() {
    for (int i = 0; i < size_m; ++i) {
      if (bucket_list_m[i] != NULL) {
	return iterator(this, i, bucket_list_m[i]->begin());
      }
    }
    return end();
  }

  /**
   * \brief Accessor.
   * \return Const iterator to the position of the first element.
   */
  const_iterator begin() const {
    for (int i = 0; i < size_m; ++i) {
      if (bucket_list_m[i] != NULL) {
	return const_iterator(this, i, bucket_list_m[i]->begin());
      }
    }
    return end();
  }

  /**
   * \brief Accessor.
   * \return Iterator to the position after the last element.
   */
  iterator end() {
    return iterator();
  }

  /**
   * \brief Accessor.
   * \return Const iterator to the position after the last element.
   */
  const_iterator end() const {
    return const_iterator();
  }

  /**
   * \brief Check if the map is empty.
   * \return Boolean representing the result.
   */
  bool empty() const {
    return bucket_list_m.empty();
  }

  /**
   * \brief Size of the map.
   * \return Size in Integer.
   */
  size_type size() const {
    int size = 0;
    for (_bucket_const_iterator bit = bucket_list_m.begin(); bit != bucket_list_m.end(); ++bit) {
      if (*bit != NULL) {
	for (_value_const_iterator vit = (*bit)->begin(); vit != (*bit)->end(); ++vit) {
	  ++size;
	}
      }
    }
    return size;
  }

  /**
   * \brief Insert new pair.
   * \return The inserted or repeated pair.
   */
  std::pair<iterator, bool> insert(const value_type& x) {
    int hash_value = _hash(x.first);
    _value_list* bucket = bucket_list_m[hash_value];
    // collision occur
    if (bucket != NULL) {
      // find branches
      for (_value_iterator vit = bucket->begin(); vit != bucket->end(); ++vit) {
	if (vit->first == x.first) {
	  return std::make_pair(iterator(this, hash_value, vit), false);
	}
      }
      bucket->push_back(x);
      return std::make_pair(iterator(this, hash_value, --bucket->end()), true);
    }
    // no collision
    _value_list* new_chain = new _value_list();
    new_chain->push_back(x);
    bucket_list_m[hash_value] = new_chain;
    return std::make_pair(iterator(this, hash_value, --new_chain->end()), true);
  }

  /**
   * \brief Erase a pair through iterator.
   * \return Void.
   */
  void erase(iterator pos) {
    if (pos != end()) {
      bucket_list_m.erase(pos.value_it_m);
    }
  }

  /**
   * \brief Erase a pair by key value.
   * \return Number of pair being erased.
   */
  size_type erase(const Key& x) {
    _value_list* bucket = bucket_list_m[_hash(x)];
    if (bucket != NULL) {
      for (_value_iterator vit = bucket->begin(); vit != bucket->end(); ++vit) {
	if (vit->first == x) {
	  bucket->erase(vit);
	  return 1;
	}
      }
    }
    return 0;
  }

  /**
   * \brief Clearing the whole map.
   * \return Void.
   */
  void clear() {
    for (_bucket_iterator bit = bucket_list_m.begin(); bit != bucket_list_m.end(); ++bit) {
      if (*bit != NULL) {
	(*bit)->clear();
      }
    }
    bucket_list_m.clear();
  }

  /**
   * \brief Find data by key value.
   * \return Iterator pointing to the result.
   */
  iterator find(const Key& x) {
    int hash_value = _hash(x);
    _value_list* bucket = bucket_list_m[hash_value];
    if (bucket != NULL) {
      for (_value_iterator vit = bucket->begin(); vit != bucket->end(); ++vit) {
	if (vit->first == x) {
	  return iterator(this, hash_value, vit);
	}
      }
    }
    return end();
  }

  /**
   * \brief Find data by key value.
   * \return Const iterator pointing to the result.
   */
  const_iterator find(const Key& x) const {
    int hash_value = _hash(x);
    _value_list* bucket = bucket_list_m[hash_value];
    if (bucket != NULL) {
      for (_value_const_iterator vit = bucket->begin(); vit != bucket->end(); ++vit) {
	if (vit->first == x) {
	  return const_iterator(this, hash_value, vit);
	}
      }
    }
    return end();
  }

  /**
   * \brief Number of occurrance of a given key.
   * \return 0 or 1.
   */
  size_type count(const Key& x) const {
    return find(x) != end();
  }
  
  /**
   * \brief Accessing the corresponding data of a key directly.
   * \return The data.
   */
  T& operator[] (const Key& x) {
    return ((insert(value_type(x, T()))).first)->second;
  }

  /**
   * \brief Accessing the corresponding data of a key directly.
   * \return The const data.
   */
  const T& operator[] (const Key& x) const {
    return ((insert(value_type(x, T()))).first)->second;
  }

  /**
   * \brief Print function for debugging.
   * \return Void.
   */
  void print() {
    std::cout << "size: " << size() << std::endl;
    for (_bucket_iterator bit = bucket_list_m.begin(); bit != bucket_list_m.end(); ++bit) {
      if (*bit != NULL) {
	for (_value_iterator vit = (*bit)->begin(); vit != (*bit)->end(); ++vit) {
	  std::cout << _hash(vit->first) << ": (" << vit->first << ", " << vit->second << ")" << std::endl;
	}
      }
    }
    return;
  }
  
private:
  _bucket_list bucket_list_m;
  size_type size_m;
  
};

#endif // HASHTABLEMAP_HPP
