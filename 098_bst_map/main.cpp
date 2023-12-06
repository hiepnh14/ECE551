#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> tree;
  tree.add(10, 1);
  tree.add(20, 2);
  tree.add(0, 3);
  tree.add(15, 4);
  tree.add(25, 5);
  tree.add(5, 6);
  tree.add(-5, 7);
  int a = tree.lookup(5);
  tree.remove(0);
  std::cout << "6= " << a << "\n";
  std::cout << tree.lookup(0) << "\n";
}
