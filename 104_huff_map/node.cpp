#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert(this->left == NULL);
    assert(this->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(this->sym, b));
  }
  else {
    assert(this->left != NULL);
    assert(this->right != NULL);
    BitString left = b.plusZero();
    this->left->buildMap(left, theMap);
    BitString right = b.plusOne();
    this->right->buildMap(right, theMap);
  }
}
