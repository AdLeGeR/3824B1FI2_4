#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H
#include <algorithm>
#include <iostream>
#include <string>

template <class T> class Table {
public:
  virtual void insert(const std::string &, const T &) = 0;
  virtual T *find(const std::string &) = 0;
  virtual void remove(const std::string &) = 0;
  virtual int getCountOper() const = 0;
  virtual ~Table() = default;
};

#endif // !TABLE_TABLE_H
