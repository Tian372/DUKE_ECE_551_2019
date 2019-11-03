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
    Node() : next(NULL), prev(NULL) {}
    Node(T d) : data(d), next(NULL), prev(NULL){};
    ~Node(){};
  };
  Node * head;
  Node * tail;
  int size;

  class Error : public std::exception {
    const char * what() { return "Item not exist"; }
  };

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) {
    head = new Node(rhs.head->data);
    tail = head;
    size = rhs.getSize();
    Node * curr = rhs.head->next;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
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
    if (size >= 1) {
      while (head != tail) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      delete head;
      size = 0;
    }
  }
  int getSize() const { return size; }

  void addFront(const T & item) {
    if (head == NULL) {
      head = new Node(item);
      tail = head;
      size++;
    }

    else {
      Node * temp = new Node(item);
      temp->next = head;
      head->prev = temp;
      head = temp;

      size++;
    }
  }

  void addBack(const T & item) {
    if (tail == NULL) {
      tail = new Node(item);
      head = tail;
      size++;
    }
    else {
      Node * temp = new Node(item);
      tail->next = temp;
      temp->prev = tail;
      tail = temp;

      size++;
    }
  }

  bool remove(const T & item) {
    int pos = find(item);

    if (pos == -1) {
      return false;
    }
    else {
      Node * curr = head + pos;
      if (curr->prev == NULL && curr->next == NULL) {
        head = NULL;
        tail = NULL;
        delete curr;
        size--;
        return true;
      }
      if (curr->next == NULL) {
        Node * currP = curr - 1;
        currP->next = NULL;
        delete curr;
        size--;
        return true;
      }

      else if (curr->prev == NULL) {
        Node * currN = curr + 1;
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
      throw Error();
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
      throw Error();
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) {
    if (size != 0) {
      Node * pos = head;
      for (int i = 0; i <= size; i++) {
        if (pos->data == item) {
          return i;
        }
        pos++;
      }
      return -1;
    }
    return -1;
  }
};

#endif
