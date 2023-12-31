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
  Node * copy(const Node * rhs) {
    if (rhs != NULL) {
      Node * cur = new Node(rhs->key, rhs->value);
      cur->left = copy(rhs->left);
      cur->right = copy(rhs->right);
      return cur;
    }
    return NULL;
  }

 public:
  BstMap<K, V>() : root(NULL) {}
  BstMap<K, V>(const BstMap<K, V> & rhs) { root = copy(rhs.root); }
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }
  virtual void add(const K & key, const V & value) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if (key > (*cur)->key)
        cur = &(*cur)->right;
      else if (key < (*cur)->key)
        cur = &(*cur)->left;
      else {
        (*cur)->value = value;
        return;
      }
    }
    *cur = new Node(key, value);
  }
  /* if (root == NULL)
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
  }*/
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
        Node * replacement = node->right;
        while (replacement->left != NULL)
          replacement = replacement->left;
        node->key = replacement->key;
        node->value = replacement->value;
        node->right = removeNode(node->right, replacement->key);
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
  void destroy(Node * node) {
    if (node != NULL) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }
  virtual ~BstMap<K, V>() { destroy(root); }
};
#endif
