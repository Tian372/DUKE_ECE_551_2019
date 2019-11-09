#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}

  Node * copy(const Node * n) {
    if (n == NULL) {
      return NULL;
    }
    Node * newNode = new Node(n->key);
    if (n->left != NULL) {
      newNode->left = copy(n->left);
    }
    if (n->right != NULL) {
      newNode->right = copy(n->right);
    }
    return newNode;
  }
  BstSet(const BstSet<T> & rhs) : root(NULL) { root = copy(rhs.root); }
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  virtual void add(const T & key) {
    Node * location = root;
    Node * toAdd = new Node(key);
    while (location != NULL) {
      if (key < location->key) {
        if (location->left == NULL) {
          location->left = toAdd;
          return;
        }
        else {
          location = location->left;
        }
      }
      else if (key > location->key) {
        if (location->right == NULL) {
          location->right = toAdd;
          return;
        }
        else {
          location = location->right;
        }
      }
      else {
        location->key = key;
        delete toAdd;
        return;
      }
    }
    root = toAdd;
  }

  virtual bool contains(const T & key) const {
    Node * location = root;
    while (location != NULL) {
      if (key == location->key) {
        return true;
      }
      else if (key < location->key) {
        location = location->left;
      }
      else {
        location = location->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key) {
    Node * location = root;
    Node * parent = root;
    while (location != NULL) {
      if (location->key < key) {
        if (location->right == NULL) {
          exit(EXIT_FAILURE);
        }
        else {
          parent = location;
          location = location->right;
        }
      }
      else if (location->key > key) {
        if (location->left == NULL) {
          exit(EXIT_FAILURE);
        }
        else {
          parent = location;
          location = location->left;
        }
      }
      else {
        if (location->left == NULL && location->right == NULL) {
          if (parent->left == location) {
            parent->left = NULL;
          }
          else if (parent->right == location) {
            parent->right = NULL;
          }
          else {
            root = NULL;
          }
          delete location;
          return;
        }
        else if (location->left == NULL && location->right != NULL) {
          if (parent->left == location) {
            parent->left = location->right;
          }
          else if (parent->right == location) {
            parent->right = location->right;
          }
          else {
            root = location->right;
          }
          delete location;
          return;
        }
        else if (location->left != NULL && location->right == NULL) {
          if (parent->right == location) {
            parent->right = location->left;
          }
          else if (parent->left == location) {
            parent->left = location->left;
          }
          else {
            root = location->left;
          }
          delete location;
          return;
        }
        else {
          Node * temp = location->left;
          Node * temp_parent = temp;
          while (temp->right != NULL) {
            temp_parent = temp;
            temp = temp->right;
          }
          if (temp_parent == temp) {
            temp->right = location->right;
            if (parent->left == location) {
              parent->left = temp;
            }
            else if (parent->right == location) {
              parent->right = temp;
            }
            else {
              root = temp;
            }
          }
          else {
            temp_parent->right = temp->left;
            temp->left = location->left;
            temp->right = location->right;
            if (parent->left == location) {
              parent->left = temp;
            }
            else if (parent->right == location) {
              parent->right = temp;
            }
            else {
              root = temp;
            }
          }
          delete location;
          return;
        }
      }
    }
  }
  virtual ~BstSet<T>() { destroy(root); }
  void destroy(Node * n) {
    if (n != NULL) {
      destroy(n->left);
      destroy(n->right);
      delete n;
    }
  }
  void printInorder(Node * n) {
    if (n != NULL) {
      printInorder(n->left);
      std::cout << n->key << " " << std::endl;
      printInorder(n->right);
    }
  }
  Node * getRoot() { return root; }
};
