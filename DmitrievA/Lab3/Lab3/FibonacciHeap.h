#pragma once
#include <cmath>
#include <vector>

#include "QueueWithTracking.h"

using std::floor;
using std::log;
using std::runtime_error;
using std::sqrt;
using std::vector;

template <typename T>
class FibonacciHeap {
  struct Node {
    T data;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool mark;
    Node(T data)
        : data(data),
          degree(0),
          parent(nullptr),
          child(nullptr),
          left(this),
          right(this){}
  };
  typedef struct Node Node;
  Node* minNode;
  size_t size;
  // сливает два списка корней и возвращает новый корень
  Node* mergeLists(Node* a, Node* b) {
    if (!a)
      return b;
    if (!b)
      return a;

    Node* aRight = a->right;
    Node* bLeft = b->left;

    a->right = b;
    b->left = a;

    aRight->left = bLeft;
    bLeft->right = aRight;

    return (a->data < b->data) ? a : b;
  }
  Node* compress(Node* a, Node* b, vector<Node*>& tempNodes) {
    if (a->data < b->data) {
      // a становится родителем
      b->left->right = b->right;
      b->right->left = b->left;
      b->parent = a;
      if (a->child == nullptr) {
        a->child = b;
        b->left = b;
        b->right = b;
      } else {
        b->left = a->child;          // child<-b
        b->right = a->child->right;  // child<-b->(child->right)
        a->child->right->left = b;   // child<-b<->(child->right)
        a->child->right = b;         // child<->b<->(child->right)
        if (b->data < a->child->data) {
          a->child = b;
        }
      }
      a->degree++;
      if (tempNodes[a->degree] != nullptr) {
        Node* other = tempNodes[a->degree];
        tempNodes[a->degree] = nullptr;
        return compress(a, other, tempNodes);
      } else {
        tempNodes[a->degree] = a;
        return a;
      }
    } else {
      // b становится родителем
      a->left->right = a->right;
      a->right->left = a->left;
      a->parent = b;
      if (b->child == nullptr) {
        b->child = a;
        a->left = a;
        a->right = a;
      } else {
        a->left = b->child;
        a->right = b->child->right;
        b->child->right->left = a;
        b->child->right = a;
        if (a->data < b->child->data) {
          b->child = a;
        }
      }
      b->degree++;
      if (tempNodes[b->degree] != nullptr) {
        Node* other = tempNodes[b->degree];
        tempNodes[b->degree] = nullptr;
        return compress(b, other, tempNodes);
      } else {
        tempNodes[b->degree] = b;
        return b;
      }
    }
  }

 public:
  FibonacciHeap() : minNode(nullptr), size(0) {}
  void push(T data) {
    if (size == 0) {
      minNode = new Node(data);
      minNode->left = minNode;
      minNode->right = minNode;
      size++;
      return;
    }
    Node* newNode = new Node(data);
    newNode->right = minNode->right;
    newNode->left = minNode;
    minNode->right->left = newNode;
    minNode->right = newNode;
    if (data < minNode->data) {
      minNode = newNode;
    }
    size++;
  }
  T pop() {
    if (size == 0)
      throw std::runtime_error("Segmentation fault");
    if (size == 1) {
      T data = minNode->data;
      delete minNode;
      minNode = nullptr;
      size--;
      return data;
    }
    if (minNode->left == minNode) {
      // т.к. size > 1, то у minNode есть хотя бы один ребёнок
      Node* temp = minNode;
      Node* cStart = minNode->child;
      Node* cIter = cStart;
      do {
        cIter->parent = nullptr;
        cIter = cIter->right;
      } while (cIter != cStart);
      minNode = minNode->child;
      T data = temp->data;
      delete temp;
      size--;
      return data;
    }
    Node* temp = minNode;
    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;
    if (minNode->child == nullptr) {
      minNode = minNode->left;
    } else {
      Node* cStart = minNode->child;
      Node* cIter = cStart;
      do {
        cIter->parent = nullptr;
        cIter = cIter->right;
      } while (cIter != cStart);
      minNode = minNode->left;
      minNode = mergeLists(minNode, cStart);
    }
    T data = temp->data;
    delete temp;
    size--;

    // запускаем обход по списку корней, чтобы найти новый minNode
    // для хранения узлов по степени используем массив, размер которого равен
    // максимальной степени, которая может быть у корня (т.е. log(size))
    vector<Node*> tempNodes(64, nullptr);
    vector<Node*> roots;
    Node* start = minNode;
    T minData = minNode->data;
    Node* iter = minNode->right;
    roots.push_back(start);
    while (iter != start) {
      roots.push_back(iter);
      if ((iter->data) < minData) {
        minNode = iter;
        minData = iter->data;
      }
      iter = iter->right;
    }
    for (size_t i = 0; i < roots.size(); i++) {
      if (tempNodes[roots[i]->degree] == nullptr) {
        tempNodes[roots[i]->degree] = roots[i];
      } else {
        Node* other = tempNodes[roots[i]->degree];
        tempNodes[roots[i]->degree] = nullptr;
        if (roots[i] == minNode || other == minNode) {
          minNode = compress(roots[i], other, tempNodes);
        } else {
          compress(roots[i], other, tempNodes);
        }
      }
    }
    while (minNode->parent) {
      minNode = minNode->parent;
    }
    return data;
  }
  bool isEmpty() const {
    return size == 0;
  }
};

using std::floor;
using std::log;
using std::sqrt;
using std::vector;

template <typename T>
class FibonacciHeapWithTracking : public QueueWithTracking<T> {
  struct Node {
    T data;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool mark; //true - если однажды оторвали сына(значение degree при этом не меняется)
    size_t index;  // индекс в indexToNode для трекинга
    Node(T data, size_t index)
        : data(data),
          index(index),
          degree(0),
          parent(nullptr),
          child(nullptr),
          left(this),
          right(this),
          mark(false) {}
  };
  vector<Node*> indexToNode;  // указатель на узел по индексу (для decreaseKey)
  FibonacciHeap<size_t> freeIndexes;  // куча для хранения свободных индексов
  typedef struct Node Node;
  Node* minNode;
  size_t size;
  // сливает два списка корней и возвращает новый корень
  Node* mergeLists(Node* a, Node* b) {
    if (!a)
      return b;
    if (!b)
      return a;

    Node* aRight = a->right;
    Node* bLeft = b->left;

    a->right = b;
    b->left = a;

    aRight->left = bLeft;
    bLeft->right = aRight;

    return (a->data < b->data) ? a : b;
  }
  Node* compress(Node* a, Node* b, vector<Node*>& tempNodes) {
    if (a->data < b->data) {
      // a становится родителем
      b->left->right = b->right;
      b->right->left = b->left;
      b->parent = a;
      if (a->child == nullptr) {
        a->child = b;
        b->left = b;
        b->right = b;
      } else {
        b->left = a->child;          // child<-b
        b->right = a->child->right;  // child<-b->(child->right)
        a->child->right->left = b;   // child<-b<->(child->right)
        a->child->right = b;         // child<->b<->(child->right)
        if (b->data < a->child->data) {
          a->child = b;
        }
      }
      a->degree++;
      if (tempNodes[a->degree] != nullptr) {
        Node* other = tempNodes[a->degree];
        tempNodes[a->degree] = nullptr;
        return compress(a, other, tempNodes);
      } else {
        tempNodes[a->degree] = a;
        return a;
      }
    } else {
      // b становится родителем
      a->left->right = a->right;
      a->right->left = a->left;
      a->parent = b;
      if (b->child == nullptr) {
        b->child = a;
        a->left = a;
        a->right = a;
      } else {
        a->left = b->child;
        a->right = b->child->right;
        b->child->right->left = a;
        b->child->right = a;
        if (a->data < b->child->data) {
          b->child = a;
        }
      }
      b->degree++;
      if (tempNodes[b->degree] != nullptr) {
        Node* other = tempNodes[b->degree];
        tempNodes[b->degree] = nullptr;
        return compress(b, other, tempNodes);
      } else {
        tempNodes[b->degree] = b;
        return b;
      }
    }
  }

  void transplantation(Node* node) {
    if (!node->parent) {
      return;
    }
    if (node->right == node) {
      node->parent->child = nullptr;

    } else {  // есть братья
      if (node->parent->child ==
          node) {  // если node - первый ребёнок, то нужно найти нового
                   // минимального ребёнка
        Node* minChild = node->right;
        T minData = minChild->data;
        Node* iter = minChild->right;
        while (iter != node) {
          if (iter->data < minData) {
            minData = iter->data;
            minChild = iter;
          }
          iter = iter->right;
        }
        node->parent->child = minChild;
      }
      node->right->left = node->left;
      node->left->right = node->right;
    }
    // присадить к корням
    node->right = minNode->right;
    node->right->left = node;
    minNode->right = node;
    node->left = minNode;
    // обновить minNode, если нужно
    if (node->data < minNode->data) {
      minNode = node;
    }

    // если родитель был помечен, то нужно оторвать его от родителя и прикрепить
    // к корням
    node->parent->degree--;
    if (node->parent->mark && node->parent->parent != nullptr) {
      node->parent->mark = false;
      transplantation(node->parent);
    } else if (node->parent != nullptr){
      node->parent->mark = true;
    }
    node->parent = nullptr;
  }

 public:
  FibonacciHeapWithTracking() : minNode(nullptr), size(0) {}
  size_t push(T data) {
    size_t index;
    if (freeIndexes.isEmpty()) {
      index = indexToNode.size();
      indexToNode.push_back(nullptr);
    } else {
      index = freeIndexes.pop();
    }
    if (size == 0) {
      minNode = new Node(data, index);
      minNode->left = minNode;
      minNode->right = minNode;
      size++;
      indexToNode[index] = minNode;
      return index;
    }
    Node* newNode = new Node(data, index);
    newNode->right = minNode->right;
    newNode->left = minNode;
    minNode->right->left = newNode;
    minNode->right = newNode;
    if (data < minNode->data) {
      minNode = newNode;
    }
    indexToNode[index] = newNode;
    size++;
    return index;
  }
  T pop() {
    if (size == 0)
      throw std::runtime_error("Segmentation fault");
    freeIndexes.push(minNode->index);
    if (size == 1) {
      T data = minNode->data;
      delete minNode;
      minNode = nullptr;
      size--;
      return data;
    }
    if (minNode->left == minNode) {
      // т.к. size > 1, то у minNode есть хотя бы один ребёнок
      Node* temp = minNode;
      Node* cStart = minNode->child;
      Node* cIter = cStart;
      do  {
        cIter->parent = nullptr;
        cIter = cIter->right;
        if (cIter->mark) {
          cIter->mark = false;
        }
      } while (cIter != cStart);
      minNode = minNode->child;
      T data = temp->data;
      delete temp;
      size--;
      return data;
    }
    Node* temp = minNode;
    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;
    if (minNode->child == nullptr) {
      minNode = minNode->left;
    } else {
      Node* cStart = minNode->child;
      Node* cIter = cStart;
      do {
        cIter->parent = nullptr;
        cIter = cIter->right;
        if (cIter->mark) {
          cIter->mark = false;
        }
      } while (cIter != cStart);
      minNode = minNode->left;
      minNode = mergeLists(minNode, cStart);
    }
    T data = temp->data;
    delete temp;
    size--;

    // запускаем обход по списку корней, чтобы найти новый minNode
    // для хранения узлов по степени используем массив, размер которого равен
    // максимальной степени, которая может быть у корня (т.е. log(size))
    vector<Node*> tempNodes(64, nullptr);
    vector<Node*> roots;
    Node* start = minNode;
    T minData = minNode->data;
    Node* iter = minNode->right;
    roots.push_back(start);
    while (iter != start) {
      roots.push_back(iter);
      if ((iter->data) < minData) {
        minNode = iter;
        minData = iter->data;
      }
      iter = iter->right;
    }
    for (size_t i = 0; i < roots.size(); i++) {
      if (tempNodes[roots[i]->degree] == nullptr) {
        tempNodes[roots[i]->degree] = roots[i];
      } else {
        Node* other = tempNodes[roots[i]->degree];
        tempNodes[roots[i]->degree] = nullptr;
        if (roots[i] == minNode || other == minNode) {
          minNode = compress(roots[i], other, tempNodes);
        } else {
          compress(roots[i], other, tempNodes);
        }
      }
    }
    while (minNode->parent) {
      minNode = minNode->parent;
    }

    return data;
  }
  void decreaseKey(size_t index, T data) {
    if (index >= indexToNode.size() || indexToNode[index] == nullptr)
      throw std::runtime_error("Invalid index");
    Node* node = indexToNode[index];
    if (data > node->data)
      throw std::runtime_error("New key is greater than current key");
    node->data = data;
    if (node->parent) {
      if (node->data < node->parent->data) {
        transplantation(node);
        // если есть братья и node не минимален, то
        // смотрим, стал ли он минимальным среди братьев
      } else if (node->right != node &&
                 node->parent->child !=node &&  
                 data < node->parent->child->data) {
        node->parent->child = node;
      }
    } else if (data < minNode->data) {  // если в корне, то нужно проверить, не
                                        // стал ли он новым минимумом
      minNode = node;
    }
  }
  bool isEmpty() const {
    return size == 0;
  }
};