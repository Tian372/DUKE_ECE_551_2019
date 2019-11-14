#include <assert.h>

#include "node.h"
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  assert(counts != NULL);
  priority_queue_t qt;
  int num = 0;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      num++;
      qt.push(new Node(i, counts[i]));
    }
  }
  if (num == 0) {
    return NULL;
  }
  Node * l = NULL;
  Node * r = NULL;
  while (qt.size() > 1) {
    l = qt.top();
    qt.pop();

    r = qt.top();
    qt.pop();

    qt.push(new Node(l, r));
    l = NULL;
    r = NULL;
  }
  return qt.top();
}
