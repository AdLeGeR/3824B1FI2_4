#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <stdexcept>

struct Monomial {
  double coefficient;
  int degrees;
  Monomial() : coefficient(0), degrees(0) {}
  Monomial(double c, int d) : coefficient(c), degrees(d) {}
  bool operator<(const Monomial& other) const {
    return degrees > other.degrees;
  }
  bool operator==(const Monomial& other) const {
    return degrees == other.degrees &&
           std::fabs(coefficient - other.coefficient) < 0.000001;
  }
  bool operator!=(const Monomial& other) const { return !(*this == other); }
};

struct Node {
  Monomial elem;
  Node* next;
  explicit Node(const Monomial& m) : elem(m), next(nullptr) {}
  ~Node() = default;
};

class MyList {
 public:
  class Iterator {
   public:
    explicit Iterator(Node* ptr = nullptr) : current_node_(ptr) {}
    Monomial& operator*() const { return current_node_->elem; }
    Monomial* operator->() const { return &(current_node_->elem); }
    Iterator& operator++() {
      if (current_node_) current_node_ = current_node_->next;
      return *this;
    }
    bool operator==(const Iterator& other) const {
      return current_node_ == other.current_node_;
    }
    bool operator!=(const Iterator& other) const {
      return current_node_ != other.current_node_;
    }

   private:
    Node* current_node_;
    friend class MyList;
  };

  class ConstIterator {
   public:
    explicit ConstIterator(const Node* ptr = nullptr) : current_node_(ptr) {}
    const Monomial& operator*() const { return current_node_->elem; }
    const Monomial* operator->() const { return &(current_node_->elem); }
    ConstIterator& operator++() {
      if (current_node_) current_node_ = current_node_->next;
      return *this;
    }
    bool operator==(const ConstIterator& other) const {
      return current_node_ == other.current_node_;
    }
    bool operator!=(const ConstIterator& other) const {
      return current_node_ != other.current_node_;
    }

   private:
    const Node* current_node_;
    friend class MyList;
  };

  MyList();
  ~MyList();
  MyList(const MyList& other);
  MyList& operator=(MyList other);
  bool empty() const;
  size_t size() const;
  void clear();
  void EmplaceBack(const Monomial& m);
  void EmplaceBack(double c, int d);
  void Sort();

  Iterator begin() { return Iterator(head_); }
  Iterator end() { return Iterator(nullptr); }
  ConstIterator begin() const { return ConstIterator(head_); }
  ConstIterator end() const { return ConstIterator(nullptr); }

 private:
  Node* head_;
  Node* tail_;
  size_t size_;
};

class Polinomial {
 public:
  Polinomial() = default;
  Polinomial(const Polinomial& other);
  explicit Polinomial(const std::string& s);
  bool operator==(const Polinomial& other) const;
  bool operator!=(const Polinomial& other) const;
  Polinomial& operator=(const Polinomial& other);
  Polinomial operator+(const Polinomial& other) const;
  Polinomial operator-(const Polinomial& other) const;
  Polinomial operator*(const Polinomial& other) const;
  Polinomial operator*(double mult) const;

  friend std::ostream& operator<<(std::ostream& out, const Polinomial& p);
  friend std::istream& operator>>(std::istream& in, Polinomial& p);

 private:
  MyList data_;
  void Simplify();
};