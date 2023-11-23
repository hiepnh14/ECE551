#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"
using namespace std;
typedef LinkedList<int> IntList;
class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    IntList il2(il);
    assert(il2.head == NULL);
    assert(il2.tail == NULL);
    assert(il2.getSize() == 0);

    IntList il3 = il;
    assert(il3.head == NULL);
    assert(il3.tail == NULL);
    assert(il3.getSize() == 0);

  }  // example of another method you might want to write
  void testAddFront() {
    //2-9 WRITE ME
    IntList il;
    IntList il2;
    il.addFront(3);
    assert(il[0] == 3);
    assert(il.head == il.tail);
    assert(il.tail->data == 3 && il.head->data == 3);
    assert(il.head->prev == NULL);
    std::cout << il.find(3) << std::endl;
    assert(il.find(3) == 0);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL && il.tail->prev == NULL);
    assert(il.head != NULL && il.tail != NULL);

    il2 = il;
    assert(il2.head == il2.tail && il2.head->data == 3 && il2.head->next == NULL &&
           il2.tail->prev == NULL && il2.find(3) == 0 && il2[0] == 3);

    IntList il3(il);
    cout << "1" << endl;
    assert(il3.head == il3.tail && il3.head->data == 3 && il3.head->next == NULL &&
           il3.tail->prev == NULL && il3.find(3) == 0 && il3[0] == 3);
    assert(!il.remove(0));

    assert(il.head == il.tail && il.head->data == 3 && il.head->next == NULL &&
           il.tail->prev == NULL && il.find(3) == 0 && il[0] == 3);
    cout << "2\n";
    il.addFront(1);  // 1 -> 3
    assert(il[1] == 3 && il[0] == 1);
    assert(il.tail->data == 3 && il.head->data == 1);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 3);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 1);
    assert(il.tail->data == 3);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(1) == 0 && il.find(3) == 1);
    cout << "3\n";
    il3 = il;
    assert(il3[1] == 3 && il3[0] == 1 && il3.head->data == 1 && il3.tail->data == 3);
    assert(il3.getSize() == 2);
    assert(il3.head->next->next == NULL);
    assert(il3.head->next->prev == il3.head);
    assert(il3.head->next = il3.tail);
    assert(il3.head->next->data == 3);
    assert(il3.head->next->prev == il3.head);
    assert(il3.head->next->prev->data == 1);
    assert(il3.tail->data == 3);
    assert(il3.tail->prev->data == 1);
    assert(il3.tail->next == NULL);
    assert(il3.tail->prev->prev == NULL);
    assert(il3.find(1) == 0 && il3.find(3) == 1);
    cout << "3.5\n";
    assert(!il.remove(0));
    assert(il.remove(1));  // 3
    assert(il[0] == 3 && il.head == il.tail && il.tail->data == 3 && il.head->data == 3 &&
           il.head->prev == NULL && il.find(3) == 0 && il.getSize() == 1 &&
           il.head->next == NULL && il.tail->prev == NULL);
    assert(il.head != NULL && il.tail != NULL);
    cout << "3.6\n";
    assert(il.remove(3));  // nothing
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);

    il.addFront(3);  // 3
    assert(il[0] == 3 && il.head == il.tail && il.tail->data == 3 && il.head->data == 3 &&
           il.head->prev == NULL && il.find(3) == 0 && il.getSize() == 1 &&
           il.head->next == NULL && il.tail->prev == NULL);
    assert(il.head != NULL && il.tail != NULL);
    cout << "4\n";
    il.remove(3);   //
    il.addBack(3);  // 3
    assert(il[0] == 3 && il.head == il.tail && il.tail->data == 3 && il.head->data == 3 &&
           il.head->prev == NULL && il.find(3) == 0 && il.getSize() == 1 &&
           il.head->next == NULL && il.tail->prev == NULL);
    assert(il.head != NULL && il.tail != NULL);
    il.remove(3);  //
    il.addFront(3);
    il.addBack(1);  // 3 1
    cout << "5\n";
    assert(il[1] == 1 && il[0] == 3);
    assert(il.tail->data == 1 && il.head->data == 3);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 1);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 3);
    assert(il.tail->data == 1);
    assert(il.tail->prev->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(1) == 1 && il.find(3) == 0);

    IntList il4(il);
    assert(il4[1] == 1 && il4[0] == 3);
    assert(il4.tail->data == 1 && il4.head->data == 3);
    assert(il4.getSize() == 2);
    assert(il4.head->next->next == NULL);
    assert(il4.head->next->prev == il4.head);
    assert(il4.head->next = il4.tail);
    assert(il4.head->next->data == 1);
    assert(il4.head->next->prev == il4.head);
    assert(il4.head->next->prev->data == 3);
    assert(il4.tail->data == 1);
    assert(il4.tail->prev->data == 3);
    assert(il4.tail->next == NULL);
    assert(il4.tail->prev->prev == NULL);
    assert(il4.find(1) == 1 && il4.find(3) == 0);
    cout << "5\n";
    assert(il.remove(3));
    il.addFront(3);  //3 1
    assert(il[1] == 1 && il[0] == 3);
    assert(il.tail->data == 1 && il.head->data == 3);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 1);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 3);
    assert(il.tail->data == 1);
    assert(il.tail->prev->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(1) == 1 && il.find(3) == 0);
    cout << "6\n";
    il.remove(3);
    il.addBack(2);
    il.addBack(3);  // 1 2 3
    il2 = il;
    IntList il5(il);
    assert(il2.head->next->next == il2.tail && il2.head->data == 1 &&
           il2.head->prev == NULL && il2.tail->data == 3 && il2.getSize() == 3 &&
           il2.tail->prev->data == 2 && il2.find(1) == 0 && il2.find(2) == 1 &&
           il2.find(3) == 2 && il2.head->next->data == 2 && il2[0] == 1 && il2[1] == 2 &&
           il2[2] == 3);

    assert(il5.head->next->next == il5.tail && il5.head->data == 1 &&
           il5.head->prev == NULL && il5.tail->data == 3 && il5.getSize() == 3 &&
           il5.tail->prev->data == 2 && il5.find(1) == 0 && il5.find(2) == 1 &&
           il5.find(3) == 2 && il5.head->next->data == 2 && il5[0] == 1 && il5[1] == 2 &&
           il5[2] == 3);
    cout << "7\n";
    assert(il.remove(2));  // 1 3
    assert(il[1] == 3 && il[0] == 1);
    assert(il.tail->data == 3 && il.head->data == 1);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 3);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 1);
    assert(il.tail->data == 3);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(1) == 0 && il.find(3) == 1);
    cout << "8\n";
    il.addFront(2);
    il.remove(1);  // 2 3
    assert(il[1] == 3 && il[0] == 2);
    assert(il.tail->data == 3 && il.head->data == 2);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 3);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 2);
    assert(il.tail->data == 3);
    assert(il.tail->prev->data == 2);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(2) == 0 && il.find(3) == 1);
    cout << "9\n";
    il.addFront(1);  // 1 2 3
    cout << "10\n";
    il.remove(3);  // 1 2
    cout << "11\n";
    assert(il[1] == 2 && il[0] == 1);
    assert(il.tail->data == 2 && il.head->data == 1);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.head->next = il.tail);
    assert(il.head->next->data == 2);
    assert(il.head->next->prev == il.head);
    assert(il.head->next->prev->data == 1);
    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.find(1) == 0 && il.find(2) == 1);
    cout << "passed\n";
  }

  // many more tester methods

  void testRule3() {
    //10-16 What member functions does the programmer need to write and what mistakes could they make regrading copying, allocating,a nd deallocating memory?
  }
  void testRemoving() {
    // 17-26 Work out several removals by hand, and write comprehendisve tests for thins that could go wrong when removing from different positions in the list. Think carefully about what a programmer could fail to update pointers around the node being removed.
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testRule3();
  t.testRemoving();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
