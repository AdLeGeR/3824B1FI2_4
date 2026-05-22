#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename ValType>
struct TableNode {
  std::string key;
  ValType value;
  TableNode(const std::string& key, const ValType& val) : key(key), value(val) {}
};

template <typename ValType>
class UnorderedTable {
 public:
  UnorderedTable();
  ~UnorderedTable() = default;
  UnorderedTable(const UnorderedTable& other);
  UnorderedTable& operator=(const UnorderedTable& other);

  void EmplaceBack(const std::string& key, const ValType& value);
  void Erase(const std::string& key);
  ValType* Find(const std::string& key);
  void Print();
  void PrintOperations() const;
  int GetOperationNumber() const;
  void Reset();

 private:
  std::vector<TableNode<ValType>> data_;
  int unordered_counters_;
};

template <typename ValType>
UnorderedTable<ValType>::UnorderedTable() : unordered_counters_(0) {}

template <typename ValType>
UnorderedTable<ValType>::UnorderedTable(const UnorderedTable& other)
    : data_(other.data_), unordered_counters_(0) {}

template <typename ValType>
UnorderedTable<ValType>& UnorderedTable<ValType>::operator=(
    const UnorderedTable& other) {
  unordered_counters_++;
  if (this != &other) {
	unordered_counters_++;
    data_ = other.data_;
  }
  return *this;
}

template <typename ValType>
void UnorderedTable<ValType>::EmplaceBack(const std::string& key,
                                          const ValType& value) {
  for (auto& element : data_) {
	unordered_counters_++;
    if (element.key == key) {
	  unordered_counters_++;
      element.value = value;
      return;
    }
  }
  unordered_counters_++;
  data_.emplace_back(key, value);
}

template <typename ValType>
void UnorderedTable<ValType>::Erase(const std::string& key) {
    for (auto it = data_.begin(); it != data_.end(); ++it) {
        unordered_counters_++;
        if (it->key == key) { // Deleted element gets replaced by the last as order isn't important
            *it = std::move(data_.back());
            data_.pop_back();
            unordered_counters_+=3;
            return;
        }
    }
}

template <typename ValType>
ValType* UnorderedTable<ValType>::Find(const std::string& key) {
  for (auto& element : data_) {
	unordered_counters_++;
    if (element.key == key) {
	  unordered_counters_++;
      return &(element.value);
    }
  }
  unordered_counters_++;
  return nullptr;
}

template <typename ValType>
void UnorderedTable<ValType>::Print() {
  for (std::size_t i = 0; i < data_.size(); ++i) {
    unordered_counters_++;
    std::cout << i << " " << data_[i].key << " " << data_[i].value << "\n";
  }
}

template <typename ValType>
void UnorderedTable<ValType>::PrintOperations() const {
  std::cout << "Total number of operations: " << unordered_counters_
            << std::endl;
}

template <typename ValType>
int UnorderedTable<ValType>::GetOperationNumber() const {
  return unordered_counters_;
}

template <typename ValType>
void UnorderedTable<ValType>::Reset() {
  unordered_counters_++;
  unordered_counters_ = 0;
}
