#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

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
    Node() : key(NULL), value(NULL), left(NULL), right(NULL) {}
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = copy(rhs.root); }
  Node * copy(const Node * n) {
    if (n == NULL) {
      return NULL;
    }
    Node * nextNode = new Node(n->key, n->value);
    if (n->left != NULL) {
      nextNode->left = copy(n->left);
    }
    if (n->right != NULL) {
      nextNode->right = copy(n->right);
    }
    return nextNode;
  }

  virtual void add(const K & key, const V & value) {
    Node * newNode = new Node(key, value);
    Node * location = root;

    while (location != NULL) {
      if (location->key > key) {
        if (location->left == NULL) {
          location->left = newNode;
          return;
        }
        else {
          location = location->left;
        }
      }
      else if (location->key < key) {
        if (location->right == NULL) {
          location->right = newNode;
          return;
        }
        else {
          location = location->right;
        }
      }
      else {
        location->value = value;
        delete (newNode);
        return;
      }
    }
    location = newNode;
  }
  Node ** whereis(const K & key) {
    Node ** location = &root;
    /* while (*location != NULL) {
      if ((*location)->key > key) {
        if ((*location)->left == NULL) {
          return location;
        }
        else {
          location = &((*location)->left);
        }
      }
      else if ((*location)->key < key) {
        if ((*location)->right == NULL) {
          return location;
        }
        else {
          location = &((*location)->right);
        }
      }
      else {
        return location;
      }
      }*/
    return location;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node ** location = whereis(key);
    if (*location == NULL) {
      throw std::invalid_argument("The Key is not included");
    }
    else {
      return (*location)->value;
    }
    throw std::invalid_argument("The Key is not included");
  }

  virtual void remove(const K & key) {
    Node ** location = whereis(key);
    if (*location == NULL) {
      exit(EXIT_FAILURE);
    }
    if ((*location)->left == NULL && (*location)->right == NULL) {
      delete (*location);
      *location = NULL;
    }
    if ((*location)->left != NULL && (*location)->right == NULL) {
      Node * temp = *location;
      *location = (*location)->left;
      delete temp;
    }

    if ((*location)->left == NULL && (*location)->right != NULL) {
      Node * temp = *location;
      *location = (*location)->right;
      delete temp;
    }
    if ((*location)->left != NULL && (*location)->right != NULL) {
      Node * temp = (*location)->left;
      Node * temp_parent = temp;
      if (temp->right == NULL) {
        delete *location;
        *location = temp;
        return;
      }
      while (temp->right != NULL) {
        temp_parent = temp;
        temp = temp->right;
      }
      temp_parent->right = temp->left;
      temp->left = (*location)->left;
      temp->right = (*location)->right;

      delete (*location);
      *location = temp;
    }
  }
  //tbc
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  virtual ~BstMap<K, V>() { destroy(root); }

  void printInorder(Node * current) {
    if (current != NULL) {
      printInorder(current->left);
      std::cout << current->key << " " << std::endl;
      printInorder(current->right);
    }
  }
  Node * getRoot() { return root; }
};
