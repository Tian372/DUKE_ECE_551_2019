#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(NULL), next(NULL), prev(NULL) {}
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & item, Node * n, Node * p) : data(item), next(n), prev(p) {}

    ~Node(){};
  };
  Node * head;
  Node * tail;
  int size;

  class FFF : public std::exception {
    const char * what() const throw() { return "Item not exist"; }
  };

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      this->addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    std::swap(temp.head, head);
    std::swap(temp.tail, tail);
    std::swap(temp.size, size);
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);

    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    int pos = find(item);

    if (pos == -1) {
      return false;
    }
    else {
      Node * curr = head;
      for (int k = 0; k < pos; k++) {
        curr = curr->next;
      }

      if (curr->prev == NULL && curr->next == NULL) {
        head = NULL;
        tail = NULL;
        delete curr;
        size--;
        return true;
      }
      if (curr->next == NULL) {
        Node * currP = curr->prev;
        currP->next = NULL;
        tail = currP;
        delete curr;
        size--;
        return true;
      }

      else if (curr->prev == NULL) {
        Node * currN = curr->next;
        head = currN;
        currN->prev = NULL;
        delete curr;
        size--;
        return true;
      }
      else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
        return true;
      }
    }
  }
  T & operator[](int index) {
    assert(index >= 0 && index < size);
    if (head == NULL) {
      throw FFF();
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }
  const T & operator[](int index) const {
    assert(index >= 0 && index < getSize());

    if (head == NULL) {
      throw FFF();
    }
    const Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
};

#endif
