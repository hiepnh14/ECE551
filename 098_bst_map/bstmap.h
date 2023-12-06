#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
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
    Node * const * temp = &root;
    Node * traverse = *temp;
    while (traverse != NULL) {
      if (key == traverse->key)
        break;
      else if (key > traverse->key)
        traverse = traverse->right;
      else
        traverse = traverse->left;
    }

    if (traverse == NULL) {
      throw std::invalid_argument("The key is not found");
    }
    else
      return traverse->value;
  }
  virtual void remove(const K & key) { root = removeNode(root, key); }
  Node * removeNode(Node * node, const K & key) {
    if (node == NULL) {
      return node;
    }
    if (node->key == key) {
      if (node->left == NULL) {
        Node * temp = node->right;
        delete node;
        return temp;
      }
      else if (node->right == NULL) {
        Node * temp = node->left;
        delete node;
        return temp;
      }
      else {
        K keyTarget = findMinKey(node->right);
        V valueTarget = lookup(keyTarget);
        node->right = removeNode(node->right, keyTarget);
        node->key = keyTarget;
        node->value = valueTarget;
        return node;
      }
    }
    else if (key < node->key) {
      node->left = removeNode(node->left, key);
      return node;
    }
    else {
      node->right = removeNode(node->right, key);
      return node;
    }
  }
  K findMinKey(Node * node) {
    assert(node != NULL);
    Node * traverse = node;
    K temp = node->key;
    while (traverse != NULL) {
      temp = traverse->key;
      traverse = traverse->left;
    }
    return temp;
  }
  Node * findNode(Node * node, const K & key) {
    Node * traverse = node;
    while (traverse != NULL) {
      if (key == traverse->key)
        return traverse;
      else if (key > traverse->key)
        traverse = traverse->right;
      else
        traverse = traverse->left;
    }
    return traverse;
  }
  virtual ~BstMap<K, V>() {}
};
#endif
