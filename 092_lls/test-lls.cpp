#include <assert.h>

#include <cstdlib>

#include "ll.h"

void testList(void) {
  LinkedList<int> L1;
  assert(L1.getSize() == 0 && L1.size == 0 && L1.head == NULL && L1.tail == NULL);
  L1.addBack(11);
  assert(L1.getSize() == 1 && L1.size == 1 && L1.head == L1.tail && L1.head != NULL);
  L1.addFront(1);
  assert(L1.getSize() == 2 && L1.size == 2);
  assert(L1[0] == 1);
  assert(L1[1] == 11);
  assert(L1.head->next->next == NULL);
  assert(L1.head == L1.head->next->prev);
  assert(L1.tail == L1.head->next);

  LinkedList<int> L2;
  L2 = L1;
  assert(L2.getSize() == 2 && L2.size == 2);
  assert(L2[0] == 1);
  assert(L2[1] == 11);
  assert(L2.head->next->next == NULL);
  assert(L2.head == L2.head->next->prev);
  assert(L2.tail == L2.head->next);

  LinkedList<int> L3(L1);
  assert(L3.getSize() == 2 && L3.size == 2);
  assert(L3[0] == 1);
  assert(L3[1] == 11);
  assert(L3.head->next->next == NULL);
  assert(L3.head == L3.head->next->prev);
  assert(L3.tail == L3.head->next);

  L2.remove(11);
  L2.remove(1);
  assert(L2.size == 0 && L2.getSize() == 0 && L2.head == NULL && L2.tail == NULL);

  L3.remove(11);
  assert(L3.getSize() == 1 && L3.size == 1 && L3.head == L3.tail && L3.head != NULL);
  assert(L3[0] == 1);
  assert(L3.head->next == NULL && L3.head->prev == NULL);

  L1.addFront(4);
  L1.addFront(3);
  L1.addFront(2);
  L1.addFront(1);
  assert(L1[0] == 1 && L1[1] == 2 && L1[2] == 3);
  assert(L1.size == 6 && L1.getSize() == 6);
  bool X = L1.remove(2);
  assert(L1.size == 5 && L1.getSize() == 5);
  assert(X == true);
  assert(L1[0] == 1 && L1[3] == 1);
  assert(L1.head->data == 1);
  assert(L1.head->next->data == 3);

  assert(!L1.remove(10));
  int F1 = L1.find(3);
  assert(F1 == 1);
  int F2 = L1.find(4);
  assert(F2 == 2);
  int F3 = L1.find(9);
  assert(F3 == -1);

  L1.addBack(7);
  L1.addBack(8);
  assert(L1.size == 7 && L1.getSize() == 7);
  assert(L1[5] == 7 && L1[6] == 8);

  LinkedList<int> L4;
  L4.addBack(1);
  L4.addBack(2);
  L4.addBack(3);
  L4.addBack(4);

  LinkedList<int> L5;
  L5.addBack(1);
  L5.addBack(2);

  LinkedList<int> L6;
  L6 = L4;
  L6 = L5;

  assert(L6.getSize() == L5.getSize() && L6.head->next->next == NULL);

  LinkedList<int> L7;
  assert(L7.getSize() == 0 && L7.head == NULL && L7.tail == NULL);
  for (int i = 0; i < 10; i++) {
    L7.addBack(i);

    L7.addFront(i);
  }
  LinkedList<int> L8(L7);
  assert(L8.getSize() == 20);
  for (int i = 0; i < 20; i++) {
    assert(L7[i] == L8[i]);
  }
  for (int i = 0; i < 10; i++) {
    L7.remove(i);
    assert((L7.find(i) != -1) && (L8.find(i) != -1));
    L7.remove(i);
    assert((L7.find(i) == -1) && (L8.find(i) != -1));
    assert(!L7.remove(i));
  }
  assert(L7.size == 0 && L7.getSize() == 0 && L7.head == NULL && L7.tail == NULL);
  L7.addBack(1);
  L7.addBack(2);
  L7.addBack(1);
  assert(L7.find(1) == 0);
  assert(L7.remove(1));
  assert(L7.find(1) == 1);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
