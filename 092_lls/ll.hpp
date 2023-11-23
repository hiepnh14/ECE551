#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
using namespace std;
//YOUR CODE GOES HERE
class Tester;

template<typename T>
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
  friend class Tester;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  head = NULL;
  tail = NULL;
  Node * temp = rhs.head;
  while (temp != NULL) {
    addBack(temp->data);
    temp = temp->next;
  }
}
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs) {
  if (this != &rhs) {
    LinkedList<T> temp(rhs);
    //std::swap(head, temp.head);
    //std::swap(tail, temp.tail);
    Node * temp1 = head;
    head = temp.head;
    temp.head = temp1;
    Node * temp2 = tail;
    tail = temp.tail;
    temp.tail = temp2;
  }
  return *this;
}
template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * temp = head->next;
    delete head;
    head = temp;
  }
  head = NULL;
  tail = NULL;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  head = new Node(item, head, NULL);
  if (tail == NULL) {
    tail = head;
  }
  else
    head->next->prev = head;
}
template<typename T>
void LinkedList<T>::addBack(const T & item) {
  tail = new Node(item, NULL, tail);
  if (head == NULL)
    head = tail;
  else
    tail->prev->next = tail;
}
template<typename T>
bool LinkedList<T>::remove(const T & item) {
  if (head == NULL)
    return false;
  else if (head->next == NULL && head->data == item) {
    delete head;
    head = NULL;
    tail = NULL;
    return true;
  }
  else if (head->next != NULL && head->data == item) {
    Node * temp = head;
    head = temp->next;
    head->prev = NULL;
    delete temp;
    return true;
  }
  else {
    Node * temp = head;
    while (temp != NULL) {
      if (temp->data == item) {
        if (tail == temp) {
          tail = temp->prev;
          tail->next = NULL;
          delete temp;
          return true;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        if (head == temp) {
          head = temp->next;
          head->prev = NULL;
        }

        delete temp;
        return true;
      }
      temp = temp->next;
    }
    return false;
  }
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  assert(index >= 0 && index < getSize());
  Node * temp = head;
  for (int i = 0; i < index; i++) {
    temp = temp->next;
  }
  return temp->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  assert(index >= 0 && index < getSize() && head != NULL);
  Node * temp = head;
  for (int i = 0; i < index; i++) {
    temp = temp->next;
  }
  return temp->data;
}
template<typename T>
int LinkedList<T>::find(const T & item) {
  if (head == NULL)
    return -1;
  Node * temp = head;
  int count = 0;
  while (temp != NULL) {
    if (temp->data == item)
      return count;
    count++;
    temp = temp->next;
  }
  return -1;
}
template<typename T>
int LinkedList<T>::getSize() const {
  if (head == NULL || tail == NULL)
    return 0;
  int count = 1;
  Node * temp = head;

  while (temp != tail) {
    count++;
    temp = temp->next;
  }
  return count;
}
#endif
