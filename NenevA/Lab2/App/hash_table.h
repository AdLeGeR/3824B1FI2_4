#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename ValType>
struct HashTableNode {
  std::string key;
  ValType value;
  HashTableNode<ValType>* next;  // chain method

  HashTableNode() : next(nullptr) {}
  HashTableNode(const std::string& key, const ValType& val)
      : key(key), value(val), next(nullptr) {}
};

template <typename ValType>
class HashTable {
 public:
  explicit HashTable(std::size_t size);
  HashTable(const HashTable& other);
  HashTable& operator=(const HashTable& other);
  ~HashTable();

  ValType* Find(const std::string& key);
  void EmplaceBack(const std::string& key, const ValType& value);
  void Erase(const std::string& key);
  void Print();
  void PrintOperations() const;
  int GetOperationNumber() const;
  void Reset();

 private:
  std::vector<HashTableNode<ValType>*> data_;
  std::size_t size_;
  int hash_counters_;

  int Hash(const std::string& key);
  void CopyChain(HashTableNode<ValType>* source, HashTableNode<ValType>*& dest);
};

template <typename ValType>
int HashTable<ValType>::Hash(const std::string& key) {
  int res = 5381;
  hash_counters_++;
  for (char c : key) {
    res = res * 33 + c;
	hash_counters_ += 3;
  }
  return res % size_;
}

template <typename ValType>
void HashTable<ValType>::CopyChain(HashTableNode<ValType>* source,
                                   HashTableNode<ValType>*& dest) {
  if (source == nullptr) {
	hash_counters_ += 2;
    dest = nullptr;
    return;
  }
  hash_counters_++;
  dest = new HashTableNode<ValType>(source->key, source->value);
  CopyChain(source->next, dest->next);
}

template <typename ValType>
HashTable<ValType>::HashTable(std::size_t size)
    : data_(size, nullptr), size_(size), hash_counters_(0) {}

template <typename ValType>
HashTable<ValType>::HashTable(const HashTable& other)
    : data_(other.size_, nullptr), size_(other.size_), hash_counters_(0) {
  for (std::size_t i = 0; i < size_; ++i) {
    CopyChain(other.data_[i], data_[i]);
  }
}

template <typename ValType>
HashTable<ValType>& HashTable<ValType>::operator=(const HashTable& other) {
  if (this != &other) {
	hash_counters_++;
    for (std::size_t i = 0; i < data_.size(); ++i) {
	  hash_counters_++;
      HashTableNode<ValType>* current = data_[i];
      while (current != nullptr) {
		hash_counters_ += 3;
        HashTableNode<ValType>* temp = current;
        current = current->next;
        delete temp;
      }
    }
	hash_counters_ += 2;
    size_ = other.size_;
    data_.resize(size_, nullptr);
    for (std::size_t i = 0; i < size_; ++i) {
      CopyChain(other.data_[i], data_[i]);
    }
  }
  return *this;
}

template <typename ValType>
HashTable<ValType>::~HashTable() {
  for (std::size_t i = 0; i < data_.size(); ++i) {
	hash_counters_++;
    HashTableNode<ValType>* current = data_[i];
    while (current != nullptr) {
	  hash_counters_ += 3;
      HashTableNode<ValType>* temp = current;
      current = current->next;
      delete temp;
    }
  }
}

template <typename ValType>
ValType* HashTable<ValType>::Find(const std::string& key) {
  hash_counters_ += 2;
  int index = Hash(key);
  HashTableNode<ValType>* current = data_[index];
  while (current != nullptr) {
    if (key == current->key) {
	  hash_counters_ += 2;
      return &(current->value);
    }
	hash_counters_ += 2;
    current = current->next;
  }
  return nullptr;
}

template <typename ValType>
void HashTable<ValType>::EmplaceBack(const std::string& key,
                                     const ValType& value) {
  hash_counters_ += 2;
  int index = Hash(key);
  HashTableNode<ValType>* current = data_[index];
  while (current != nullptr) {
    if (key == current->key) {
	  hash_counters_ += 2;
      current->value = value;
      return;
    }
	hash_counters_++;
    current = current->next;
  }
  hash_counters_ += 3;
  HashTableNode<ValType>* inserted = new HashTableNode<ValType>(key, value);
  inserted->next = data_[index];
  data_[index] = inserted;
}

template <typename ValType>
void HashTable<ValType>::Erase(const std::string& key) {
  hash_counters_ += 2;
  int index = Hash(key);
  HashTableNode<ValType>** current = &data_[index];
  while (*current != nullptr) {
	hash_counters_++;
    if ((*current)->key == key) {
	  hash_counters_ += 4;
      HashTableNode<ValType>* temp = *current;
      *current = (*current)->next;
      delete temp;
      return;
    }
	hash_counters_++;
    current = &(*current)->next;
  }
}

template <typename ValType>
void HashTable<ValType>::Print() {
  for (std::size_t i = 0; i < size_; ++i) {
    hash_counters_+=2;
    HashTableNode<ValType>* current = data_[i];
    while (current != nullptr) {
      hash_counters_ += 2;
      std::cout << i << " " << current->key << " " << current->value << "\n";
      current = current->next;
    }
  }
}

template <typename ValType>
void HashTable<ValType>::PrintOperations() const {
  std::cout << "Total number of operations: " << hash_counters_ << std::endl;
}

template <typename ValType>
int HashTable<ValType>::GetOperationNumber() const {
  return hash_counters_;
}

template <typename ValType>
void HashTable<ValType>::Reset() {
  hash_counters_++;
  hash_counters_ = 0;
}
