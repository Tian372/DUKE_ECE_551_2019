#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  Node * copy(const Node * n) {
    if (n == NULL) {
      return NULL;
    }
    Node * newNode = new Node(n->key, n->value);
    if (n->left != NULL) {
      newNode->left = copy(n->left);
    }
    if (n->right != NULL) {
      newNode->right = copy(n->right);
    }
    return newNode;
  }
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = copy(rhs.root); }
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    Node * location = root;
    Node * toAdd = new Node(key, value);
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
        location->value = value;
        delete toAdd;
        return;
      }
    }
    root = toAdd;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * location = root;
    while (location != NULL) {
      if (key == location->key) {
        return location->value;
      }
      else if (key < location->key) {
        location = location->left;
      }
      else {
        location = location->right;
      }
    }
    throw std::invalid_argument("Not found.");
  }

  virtual void remove(const K & key) {
    Node * location = root;
    Node * P = root;
    while (location != NULL) {
      if (location->key < key) {
        if (location->right == NULL) {
          exit(EXIT_FAILURE);
        }
        else {
          P = location;
          location = location->right;
        }
      }
      else if (location->key > key) {
        if (location->left == NULL) {
          exit(EXIT_FAILURE);
        }
        else {
          P = location;
          location = location->left;
        }
      }
      else {
        if (location->left == NULL && location->right == NULL) {
          if (P->left == location) {
            P->left = NULL;
          }
          else if (P->right == location) {
            P->right = NULL;
          }
          else {
            root = NULL;
          }
          delete location;
          return;
        }
        else if (location->left == NULL && location->right != NULL) {
          if (P->left == location) {
            P->left = location->right;
          }
          else if (P->right == location) {
            P->right = location->right;
          }
          else {
            root = location->right;
          }
          delete location;
          return;
        }
        else if (location->left != NULL && location->right == NULL) {
          if (P->right == location) {
            P->right = location->left;
          }
          else if (P->left == location) {
            P->left = location->left;
          }
          else {
            root = location->left;
          }
          delete location;
          return;
        }
        else {
          Node * temp = location->left;
          Node * temp_P = temp;
          while (temp->right != NULL) {
            temp_P = temp;
            temp = temp->right;
          }
          if (temp_P == temp) {
            temp->right = location->right;
            if (P->left == location) {
              P->left = temp;
            }
            else if (P->right == location) {
              P->right = temp;
            }
            else {
              root = temp;
            }
          }
          else {
            temp_P->right = temp->left;
            temp->left = location->left;
            temp->right = location->right;
            if (P->left == location) {
              P->left = temp;
            }
            else if (P->right == location) {
              P->right = temp;
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
  virtual ~BstMap<K, V>() { destroy(root); }
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
