#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> tree;
  tree.add(10);
  tree.add(20);
  tree.add(0);
  tree.add(15);
  tree.add(25);
  tree.add(5);
  tree.add(-5);
  bool a = tree.contains(5);
  tree.remove(0);
  std::cout << "1 = " << a << "\n";
  BstSet<int> tree2(tree);
  tree2.remove(5);
  BstSet<int> tree3;
  tree3 = tree2;
  tree3.remove(-5);
  std::cout << tree2.contains(-5) << "\n";
  std::cout << tree3.contains(-5) << "\n";
}
