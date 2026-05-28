#pragma once
#include <algorithm>
#include <string>
#include <vector>

#include "Counter.h"

using std::max;
using std::string;
using std::vector;

template <typename T>
class AVLOrderedTable {
 private:
  Counter counter;
  struct Node {
    string key;
    T value;
    Node* left;
    Node* right;
    int height;
    Node(string k, T v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
  };
  typedef struct Node Node;
  Node* root;  // Ensure the root member is declared in the private section of the class

 private:
  int height(Node* node) {
    if (node) {
      counter += 3;
      return node->height;
    }
    counter += 2;
    return 0;
  }
  int balanceFactor(Node* node) {
    if (node) {
      counter += 5;
      return height(node->left) - height(node->right);
    }
    counter += 2;
    return 0;
  }
  Node* rotateRight(Node* y) {
    counter += 14;
    AVLOrderedTable<T>::Node* x = y->left;                   // 2
    AVLOrderedTable<T>::Node* T2 = x->right;                 // 2
    x->right = y;                                            // 2
    y->left = T2;                                            // 2
    y->height = 1 + max(height(y->left), height(y->right));  // 5
    x->height = 1 + max(height(x->left), height(x->right));  // 5
    return x;                                                // 1
  }
  Node* rotateLeft(Node* x) {
    counter += 14;
    AVLOrderedTable<T>::Node* y = x->right;
    AVLOrderedTable<T>::Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
  }
  Node* insert(Node* node, string key, T value) {
    counter += 2;
    if (!node) {
      counter++;
      return new Node(key, value);
    }
    counter += 3;
    if (key < node->key) {
      node->left = insert(node->left, key, value);
      counter += 2;
    } else if (key > node->key) {
      node->right = insert(node->right, key, value);
      counter += 5;
    } else {
      node->value = value;
      counter += 5;
      return node;
    }
    counter += 7;  // считаем max за 3 операции:
    // if (a > b) return a;
    // else return b
    node->height = 1 + max(height(node->left), height(node->right));
    counter++;
    int balance = balanceFactor(node);
    counter += 5;
    if (balance > 1 && key < node->left->key) {
      counter++;
      return rotateRight(node);
    }
    counter += 5;
    if (balance < -1 && key > node->right->key) {
      counter++;
      return rotateLeft(node);
    }
    counter += 5;
    if (balance > 1 && key > node->left->key) {
      counter += 4;
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    counter += 5;
    if (balance < -1 && key < node->right->key) {
      counter += 4;
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    counter++;
    return node;
  }
  Node* remove(Node* node, string key) {
    counter += 2;
    if (!node) {
      counter++;
      return node;
    }
    counter += 3;
    if (key < node->key) {  // 3
      counter += 3;
      node->left = remove(node->left, key);  // 3
    } else if (key > node->key) {
      counter += 6;
      node->right = remove(node->right, key);  // 3
    } else {
      counter += 8;
      if (!node->left || !node->right) {  // 5
        counter += 4;
        Node* temp = node->left ? node->left : node->right;
        counter += 2;
        if (!temp) {
          temp = node;
          node = nullptr;
          counter += 2;
        } else {
          counter += 3;
          *node = *temp;
        }
        counter++;
        delete temp;
      } else {
        counter += 2;
        Node* temp = minValueNode(node->right);
        counter += 10;
        node->key = temp->key;                         // 3
        node->value = temp->value;                     // 3
        node->right = remove(node->right, temp->key);  // 4
      }
    }
    counter += 2;
    if (!node) {
      counter++;
      return node;
    }
    counter += 7;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);
    counter += 5;
    if (balance > 1 && balanceFactor(node->left) >= 0) {
      counter++;
      return rotateRight(node);
    }
    counter += 5;
    if (balance > 1 && balanceFactor(node->left) < 0) {
      counter += 4;
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    counter += 5;
    if (balance < -1 && balanceFactor(node->right) <= 0) {
      counter++;
      return rotateLeft(node);
    }
    counter += 5;
    if (balance < -1 && balanceFactor(node->right) > 0) {
      counter += 4;
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    counter++;
    return node;
  }
  Node* minValueNode(Node* node) {
    counter++;
    AVLOrderedTable<T>::Node* current = node;
    counter += 2;
    while (current->left) {
      current = current->left;
      counter += 4;
    }
    counter++;
    return current;
  }
  void freeSubTree(Node* node) {
    if (node) {
      freeSubTree(node->left);
      freeSubTree(node->right);
      delete node;
    }
  }

 public:
  AVLOrderedTable() {
    this->root = nullptr;
  }
  ~AVLOrderedTable() {
    freeSubTree(root);
  }
  void insert(string key, T value) {
    counter = 0;
    root = insert(root, key, value);
  }
  void remove(string key) {
    counter = 0;
    root = remove(root, key);
  }
  T* find(string key) {
    counter = 0;
    counter++;
    Node* current = root;
    counter++;
    while (current) {
      counter += 3;
      if (key < current->key) {
        counter += 2;
        current = current->left;
      } else if (key > current->key) {
        counter += 5;
        current = current->right;
      } else {
        counter += 5;
        return &current->value;
      }
    }
    counter += 2;
    return nullptr;
  }
  unsigned getCount() {
    return counter.getCount();
  }
  void clear() {
    freeSubTree(root);
    root = nullptr;
  }
};

template <typename T>
class HashOrderedTable {
 public:
  HashOrderedTable(size_t capacity = 16) {
    this->capacity = capacity;
    table.resize(capacity, nullptr);
  }
  ~HashOrderedTable() {
    for (size_t i = 0; i < capacity; ++i) {
      freeSubTree(table[i]);
    }
  }
  void insert(string key, T value) {
    counter++;
    size_t index = hash(key);

    counter += 2;
    Node* current = table[index];

    counter += 2;
    while (current != nullptr) {
      counter += 3;
      if (current->key == key) {
        counter += 2;
        current->value = value;
        return;
      }
      counter += 2;
      current = current->next;
    }
    counter++;
    Node* newNode = new Node(key, value);
    counter += 2;
    newNode->next = table[index];
    counter += 2;
    table[index] = newNode;
  }

  void remove(string key) {
    counter += 4;
    size_t index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;
    counter += 2;
    while (current != nullptr) {
      counter += 3;
      if (current->key == key) {
        counter += 2;
        if (prev == nullptr) {
          counter += 3;
          table[index] = current->next;
        } else {
          counter += 3;
          prev->next = current->next;
        }
        counter += 2;
        delete current;
        return;
      }
      counter += 3;
      prev = current;
      current = current->next;
    }
  }
  T* find(string key) {
    counter = 0;
    counter += 1;
    size_t index = hash(key);
    counter += 2;
    Node* current = table[index];
    counter += 1;

    counter += 2;
    while (current != nullptr) {
      counter += 3;
      if (current->key == key) {
        counter++;
        return &current->value;
      }
      counter += 2;
      current = current->next;
    }
    counter++;

    return nullptr;
  }
  unsigned getCount() {
    return counter.getCount();
  }
  void clear() {
    for (size_t i = 0; i < capacity; ++i) {
      freeSubTree(table[i]);
      table[i] = nullptr;
    }
  }

 private:
  struct Node {
    string key;
    T value;
    Node* next;
    Node(string k, T v) : key(k), value(v), next(nullptr) {}
  };
  typedef struct Node Node;
  Counter counter;
  std::vector<Node*> table;
  size_t capacity;
  size_t hash(string key) {
    counter++;
    size_t hashValue = 5381;
    for (char ch : key) {
      counter += 3;
      hashValue = hashValue * 31 + ch;
    }
    counter += 2;
    return hashValue % capacity;
  }
  void freeSubTree(Node* node) {
    counter += 2;
    if (node != nullptr) {
      counter += 1;
      freeSubTree(node->next);
      delete node;
    }
  }
};