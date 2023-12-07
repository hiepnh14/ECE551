#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t priority_queue;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0)
      priority_queue.push(new Node(i, counts[i]));
  }
  while (priority_queue.size() != 1) {
    Node * firstNode = priority_queue.top();
    priority_queue.pop();
    Node * secondNode = priority_queue.top();
    priority_queue.pop();
    Node * combineNodes = new Node(firstNode, secondNode);
    priority_queue.push(combineNodes);
  }
  Node * root = priority_queue.top();
  priority_queue.pop();
  return root;
}
