#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(T key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;
  Node * copy(const Node * rhs) {
    if (rhs != NULL) {
      Node * cur = new Node(rhs->key);
      cur->left = copy(rhs->left);
      cur->right = copy(rhs->right);
      return cur;
    }
    return NULL;
  }

 public:
  BstSet<T>() : root(NULL) {}
  BstSet<T>(const BstSet & rhs) { root = copy(rhs.root); }
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      BstSet<T> temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }
  void destroy(Node * node) {
    if (node != NULL) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }
  Node * removeHelper(Node * node, const T & key) {
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
        node->right = removeHelper(node->right, replacement->key);
        return node;
      }
    }
    else if (key < node->key) {
      node->left = removeHelper(node->left, key);
      return node;
    }
    else {
      node->right = removeHelper(node->right, key);
      return node;
    }
  }
  virtual void add(const T & key) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if (key > (*cur)->key)
        cur = &(*cur)->right;
      else if (key < (*cur)->key)
        cur = &(*cur)->left;
      else {
        return;
      }
    }
    *cur = new Node(key);
  }
  virtual bool contains(const T & key) const {
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
      throw false;
    }
    else
      return true;
  }
  virtual void remove(const T & key) { root = removeHelper(root, key); }
  virtual ~BstSet<T>() { destroy(root); }
};
#endif
