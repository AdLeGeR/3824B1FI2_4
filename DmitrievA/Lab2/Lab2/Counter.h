"Copyright 2026 Alexey Dmitriev"

#pragma once
#include <iostream>

    using std::ostream;

class Counter {
  unsigned count;

public:
  Counter() : count{0} {}
  unsigned operator++(int c) {
    return ++count;
  }
  void reset() {
    count = 0;
  }
  void add(unsigned c) {
    count += c;
  }
  Counter& operator+=(unsigned c) {
    count += c;
    return *this;
  }
  Counter& operator=(unsigned c) {
    count = c;
    return *this;
  }
  unsigned getCount() const {
    return count;
  }
  friend ostream& operator<<(ostream& out, Counter c) {
    out << c.count;
    return out;
  }
};
