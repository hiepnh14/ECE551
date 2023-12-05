#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    if (root == NULL)
      root = new Node(key, value);
    else {
      Node * traverse = root;
      while (true) {
        if (key > traverse->key) {
          if (traverse->right == NULL) {
            traverse->right = new Node(key, value);
            break;
          }
          else
            traverse = traverse->right;
        }
        else {
          if (traverse->left == NULL) {
            traverse->left = new Node(key, value);
            break;
          }
          else
            traverse = traverse->left;
        }
      }
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * target = findNode(this->root, key);
    if (target == NULL) {
      throw std::invalid_argument("The key is not found");
    }
    else
      return target->value;
  }
  virtual void remove(const K & key) {}
  virtual ~BstMap<K, V>() {}
};
#endif
