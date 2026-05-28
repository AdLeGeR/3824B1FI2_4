"Copyright 2026 Alexey Dmitriev"
#pragma once
#include <string>
#include <vector>

#include "Counter.h"

    using std::string;
using std::vector;

template <typename T>
class UnorderedTable {
  size_t size;
  struct record {
    string key;
    T data;
  };
  vector<record> table;
  Counter counter;

 public:
  UnorderedTable() : size(0) {}

  void insert(const string& key, const T& data) {
    counter = 0;
    for (size_t i = 0; i < size; ++i) {
      counter += 2;
      if (table[i].key == key) {
        counter += 2;
        table[i].data = data;
        return;
      }
    }
    counter += 2;
    table.push_back({key, data});
    ++size;
    counter++;
  }

  T* find(const string& key) {
    counter = 0;
    for (size_t i = 0; i < size; ++i) {
      counter += 2;
      if (table[i].key == key) {
        counter++;
        return &table[i].data;
      }
    }
    counter++;
    return nullptr;
  }

  void remove(const string& key) {
    counter = 0;
    for (size_t i = 0; i < size; ++i) {
      counter += 2;
      if (table[i].key == key) {
        counter += 3;
        table.erase(table.begin() + i);
        --size;
        return;
      }
    }
  }

  unsigned getCount() {
    return counter.getCount();
  }

  void clear() {
    table.clear();
    size = 0;
  }

  size_t getSize() const {
    return size;
  }
};
