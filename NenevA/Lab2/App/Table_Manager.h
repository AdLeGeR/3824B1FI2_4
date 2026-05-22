#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <concepts>
#include "hash_table.h"
#include "unordered_table.h"
#include "avl_tree.h"
#include "Polinomial.h"

template <typename T>
std::string ToString(const T& value) {
  if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(value);
  } else {
    std::ostringstream ss;
    ss << value;
    return ss.str();
  }
}

template <typename ValType>
class TableManager {
 public:
  TableManager(int hashTSize = 10);
  ~TableManager();

  void Run();

 private:
  struct MethodStats {
    int emplace_count = 0;
    int erase_count = 0;
    int find_count = 0;
    int print_count = 0;
  };

  HashTable<ValType> hash_table_;
  UnorderedTable<ValType> unordered_table_;
  AvlTree<ValType> avl_tree_;

  std::ofstream log_file_;

  MethodStats hash_stats_;
  MethodStats unordered_stats_;
  MethodStats avl_stats_;

  // Log actions into the file
  void Log(const std::string& message, int operations = -1);

  // Basic operations' handlers
  void HandleEmplace();
  void HandleErase();
  void HandleFind();
  void HandlePrint();

  // For work with polinomials 
  void HandlePolynomialOperations();
  Polinomial ReadPolynomial(const std::string& prompt);
  Polinomial SelectPolynomial(const std::string& prompt);

  // Work with statistics
  void ShowStats();
  void ResetStats();
  void LogFinalStats();
};

template <typename ValType>
TableManager<ValType>::TableManager(int hashTSize)
    : hash_table_(hashTSize), log_file_("log.txt", std::ios::app) {
  if (!log_file_.is_open()) {
    std::cerr << "Failed to open the file log.txt" << std::endl;
  } else {
    Log(" Session started ");
  }
}

template <typename ValType>
TableManager<ValType>::~TableManager() {
  LogFinalStats();
  Log(" Session ended ");
  if (log_file_.is_open()) {
    log_file_.close();
  }
}

template <typename ValType>
void TableManager<ValType>::Log(const std::string& message, int operations) {
  if (log_file_.is_open()) {
    log_file_ << message;
    if (operations >= 0) {
      log_file_ << " [operations: " << operations << "]";
    }
    log_file_ << std::endl;
  }
}

template <typename ValType>
void TableManager<ValType>::HandleEmplace() {
  int opCounter;
  std::string key;
  ValType value;
  std::cout << "Enter the key and the value: ";
  std::cin >> key >> value;

  opCounter = hash_table_.GetOperationNumber();
  hash_table_.EmplaceBack(key, value);
  int hash_ops = hash_table_.GetOperationNumber();
  Log("HashTable: emplace(" + key + ", " + ToString(value) + ")", hash_ops - opCounter);
  hash_stats_.emplace_count++;

  opCounter = unordered_table_.GetOperationNumber();
  unordered_table_.EmplaceBack(key, value);
  int unordered_ops = unordered_table_.GetOperationNumber();
  Log("UnorderedTable: emplace(" + key + ", " + ToString(value) + ")", unordered_ops - opCounter);
  unordered_stats_.emplace_count++;

  opCounter = avl_tree_.GetOperationNumber();
  avl_tree_.EmplaceBack(key, value);
  int avl_ops = avl_tree_.GetOperationNumber();
  Log("AvlTree: emplace(" + key + ", " + ToString(value) + ")", avl_ops - opCounter);
  avl_stats_.emplace_count++;
}

template <typename ValType>
void TableManager<ValType>::HandleErase() {
  int opCounter;
  std::string key;
  std::cout << "Enter the key for removing: ";
  std::cin >> key;

  opCounter = hash_table_.GetOperationNumber();
  hash_table_.Erase(key);
  int hash_ops = hash_table_.GetOperationNumber();
  Log("HashTable: erase(" + key + ")", hash_ops - opCounter);
  hash_stats_.erase_count++;

  opCounter = unordered_table_.GetOperationNumber();
  unordered_table_.Erase(key);
  int unordered_ops = unordered_table_.GetOperationNumber();
  Log("UnorderedTable: erase(" + key + ")", unordered_ops - opCounter);
  unordered_stats_.erase_count++;

  opCounter = avl_tree_.GetOperationNumber();
  avl_tree_.Erase(key);
  int avl_ops = avl_tree_.GetOperationNumber();
  Log("AvlTree: erase(" + key + ")", avl_ops - opCounter);
  avl_stats_.erase_count++;
}

template <typename ValType>
void TableManager<ValType>::HandleFind() {
  int opCounter;
  std::string key;
  std::cout << "Enter the key for search: ";
  std::cin >> key;

  opCounter = hash_table_.GetOperationNumber();
  ValType* result = hash_table_.Find(key);
  int hash_ops = hash_table_.GetOperationNumber();
  if (result) {
    Log("HashTable: find(" + key + ") = " + ToString(*result), hash_ops - opCounter);
    std::cout << "Hash table : " << key << " " << *result << "\n";
  } else {
    Log("HashTable: find(" + key + ") = not found", hash_ops - opCounter);
    std::cout << "The record with such a key hasn't been found\n";
  }
  hash_stats_.find_count++;

  opCounter = unordered_table_.GetOperationNumber();
  result = unordered_table_.Find(key);
  int unordered_ops = unordered_table_.GetOperationNumber();
  if (result) {
    Log("UnorderedTable: find(" + key + ") = " + ToString(*result), unordered_ops - opCounter);
    std::cout << "Unordered table : " << key << " " << *result << "\n";
  } else {
    Log("UnorderedTable: find(" + key + ") = not found", unordered_ops - opCounter);
    std::cout << "The record with such a key hasn't been found\n";
  }
  unordered_stats_.find_count++;

  opCounter = avl_tree_.GetOperationNumber();
  result = avl_tree_.Find(key);
  int avl_ops = avl_tree_.GetOperationNumber();
  if (result) {
    Log("AvlTree: find(" + key + ") = " + ToString(*result), avl_ops - opCounter);
    std::cout << "AvlTree : " << key << " " << *result << "\n";
  } else {
    Log("AvlTree: find(" + key + ") = not found", avl_ops - opCounter);
    std::cout << "The record with such a key hasn't been found\n";
  }
  avl_stats_.find_count++;
}

template <typename ValType>
void TableManager<ValType>::HandlePrint() {
  int opCounter;
  std::cout << "\n HashTable \n";
  opCounter = hash_table_.GetOperationNumber();
  hash_table_.Print();
  int hash_ops = hash_table_.GetOperationNumber();
  Log("HashTable: print()", hash_ops - opCounter);
  hash_stats_.print_count++;

  opCounter = unordered_table_.GetOperationNumber();
  std::cout << "\n UnorderedTable \n";
  unordered_table_.Print();
  int unordered_ops = unordered_table_.GetOperationNumber();
  Log("UnorderedTable: print()", unordered_ops - opCounter);
  unordered_stats_.print_count++;

  opCounter = avl_tree_.GetOperationNumber();
  std::cout << "\n AvlTree \n";
  avl_tree_.Print();
  int avl_ops = avl_tree_.GetOperationNumber();
  Log("AvlTree: print()", avl_ops - opCounter);
  avl_stats_.print_count++;
}

template <typename ValType>
void TableManager<ValType>::HandlePolynomialOperations() {
  std::cout << "\n Polynomial Operations \n";
  std::cout << "1. Addition\n";
  std::cout << "2. Subtraction\n";
  std::cout << "3. Multiplication\n";
  std::cout << "4. Multiplication by scalar\n";
  std::cout << "5. Back to main menu\n";
  std::cout << "Enter choice: ";

  int choice;
  std::cin >> choice;

  if (choice == 5) return;

  Polinomial p1, p2, result;
  double scalar;
  std::string result_key;

  p1 = SelectPolynomial("Select or enter first polynomial");

  if (choice >= 1 && choice <= 3) {
    p2 = SelectPolynomial("Select or enter second polynomial");
  }

  int opCounter;
  switch (choice) {
    case 1:  // Addition
      result = p1 + p2;
      std::cout << "Result: " << result << "\n";
      std::cout << "Enter key for storing result: ";
      std::cin >> result_key;

      opCounter = hash_table_.GetOperationNumber();
      hash_table_.EmplaceBack(result_key, result);
      Log("HashTable: emplace(" + result_key + ", " + ToString(result) + ")",
          hash_table_.GetOperationNumber() - opCounter);
      hash_stats_.emplace_count++;

      opCounter = unordered_table_.GetOperationNumber();
      unordered_table_.EmplaceBack(result_key, result);
      Log("UnorderedTable: emplace(" + result_key + ", " + ToString(result) + ")",
          unordered_table_.GetOperationNumber() - opCounter);
      unordered_stats_.emplace_count++;

      opCounter = avl_tree_.GetOperationNumber();
      avl_tree_.EmplaceBack(result_key, result);
      Log("AvlTree: emplace(" + result_key + ", " + ToString(result) + ")",
          avl_tree_.GetOperationNumber() - opCounter);
      avl_stats_.emplace_count++;
      break;

    case 2:  // Subtraction
      result = p1 - p2;
      std::cout << "Result: " << result << "\n";
      std::cout << "Enter key for storing result: ";
      std::cin >> result_key;

      opCounter = hash_table_.GetOperationNumber();
      hash_table_.EmplaceBack(result_key, result);
      Log("HashTable: emplace(" + result_key + ", " + ToString(result) + ")",
          hash_table_.GetOperationNumber() - opCounter);
      hash_stats_.emplace_count++;

      opCounter = unordered_table_.GetOperationNumber();
      unordered_table_.EmplaceBack(result_key, result);
      Log("UnorderedTable: emplace(" + result_key + ", " + ToString(result) + ")",
          unordered_table_.GetOperationNumber() - opCounter);
      unordered_stats_.emplace_count++;

      opCounter = avl_tree_.GetOperationNumber();
      avl_tree_.EmplaceBack(result_key, result);
      Log("AvlTree: emplace(" + result_key + ", " + ToString(result) + ")",
          avl_tree_.GetOperationNumber() - opCounter);
      avl_stats_.emplace_count++;
      break;

    case 3:  // Multiplication
      result = p1 * p2;
      std::cout << "Result: " << result << "\n";
      std::cout << "Enter key for storing result: ";
      std::cin >> result_key;

      opCounter = hash_table_.GetOperationNumber();
      hash_table_.EmplaceBack(result_key, result);
      Log("HashTable: emplace(" + result_key + ", " + ToString(result) + ")",
          hash_table_.GetOperationNumber() - opCounter);
      hash_stats_.emplace_count++;

      opCounter = unordered_table_.GetOperationNumber();
      unordered_table_.EmplaceBack(result_key, result);
      Log("UnorderedTable: emplace(" + result_key + ", " + ToString(result) + ")",
          unordered_table_.GetOperationNumber() - opCounter);
      unordered_stats_.emplace_count++;

      opCounter = avl_tree_.GetOperationNumber();
      avl_tree_.EmplaceBack(result_key, result);
      Log("AvlTree: emplace(" + result_key + ", " + ToString(result) + ")",
          avl_tree_.GetOperationNumber() - opCounter);
      avl_stats_.emplace_count++;
      break;

    case 4:  // Multiplication by scalar
      std::cout << "Enter scalar: ";
      std::cin >> scalar;
      result = p1 * scalar;
      std::cout << "Result: " << result << "\n";
      std::cout << "Enter key for storing result: ";
      std::cin >> result_key;

      opCounter = hash_table_.GetOperationNumber();
      hash_table_.EmplaceBack(result_key, result);
      Log("HashTable: emplace(" + result_key + ", " + ToString(result) + ")",
          hash_table_.GetOperationNumber() - opCounter);
      hash_stats_.emplace_count++;

      opCounter = unordered_table_.GetOperationNumber();
      unordered_table_.EmplaceBack(result_key, result);
      Log("UnorderedTable: emplace(" + result_key + ", " + ToString(result) + ")",
          unordered_table_.GetOperationNumber() - opCounter);
      unordered_stats_.emplace_count++;

      opCounter = avl_tree_.GetOperationNumber();
      avl_tree_.EmplaceBack(result_key, result);
      Log("AvlTree: emplace(" + result_key + ", " + ToString(result) + ")",
          avl_tree_.GetOperationNumber() - opCounter);
      avl_stats_.emplace_count++;
      break;
  }
}

template <typename ValType>
Polinomial TableManager<ValType>::ReadPolynomial(const std::string& prompt) {
  std::cout << prompt << " (format: coeff degree, coeff degree...): ";
  std::string input;
  std::cin.ignore();
  std::getline(std::cin, input);
  return Polinomial(input);
}

template <typename ValType>
Polinomial TableManager<ValType>::SelectPolynomial(const std::string& prompt) {
  std::cout << "\n" << prompt << ":\n";
  std::cout << "1. Enter new polynomial from console\n";
  std::cout << "2. Select from table by key\n";
  std::cout << "Enter choice: ";

  int choice;
  std::cin >> choice;

  if (choice == 1) {
    return ReadPolynomial("Enter polynomial");
  } else if (choice == 2) {
    std::string key;
    std::cout << "Enter key: ";
    std::cin >> key;

    // Search in all the tables
    Polinomial* result_h = hash_table_.Find(key);
    Polinomial* result_un = unordered_table_.Find(key);
    Polinomial* result_avl = avl_tree_.Find(key);
    
    if (result_h && result_un && result_avl) {
      std::cout << "Found: " << *result_h << "\n";
      return *result_h;
    }

    std::cout << "Key isn't located in all the tables. Try to enter polynomial from console instead.\n";
    return ReadPolynomial("Enter polynomial");
  } else {
    std::cout << "Invalid choice. Entering from console.\n";
    return ReadPolynomial("Enter polynomial");
  }
}

template <typename ValType>
void TableManager<ValType>::ShowStats() {
  std::cout << "\n Operation statistics \n";
  std::cout << "HashTable: ";
  hash_table_.PrintOperations();
  std::cout << "UnorderedTable: ";
  unordered_table_.PrintOperations();
  std::cout << "AvlTree: ";
  avl_tree_.PrintOperations();

  Log(" Statistics ");
  Log("HashTable: total=" + std::to_string(hash_table_.GetOperationNumber()));
  Log("UnorderedTable: total=" + std::to_string(unordered_table_.GetOperationNumber()));
  Log("AvlTree: total=" + std::to_string(avl_tree_.GetOperationNumber()));
}

template <typename ValType>
void TableManager<ValType>::ResetStats() {
  hash_table_.Reset();
  unordered_table_.Reset();
  avl_tree_.Reset();
  hash_stats_ = MethodStats();
  unordered_stats_ = MethodStats();
  avl_stats_ = MethodStats();
  Log("Statistics reseted");
}

template <typename ValType>
void TableManager<ValType>::LogFinalStats() {
  Log(" Final Statistics ");

  // HashTable
  Log("HashTable:");
  Log("  emplace: " + std::to_string(hash_stats_.emplace_count) + " times");
  Log("  erase: " + std::to_string(hash_stats_.erase_count) + " times");
  Log("  find: " + std::to_string(hash_stats_.find_count) + " times");
  Log("  print: " + std::to_string(hash_stats_.print_count) + " times");
  Log("  Total operations: " + std::to_string(hash_table_.GetOperationNumber()));

  // UnorderedTable
  Log("UnorderedTable:");
  Log("  emplace: " + std::to_string(unordered_stats_.emplace_count) + " times");
  Log("  erase: " + std::to_string(unordered_stats_.erase_count) + " times");
  Log("  find: " + std::to_string(unordered_stats_.find_count) + " times");
  Log("  print: " + std::to_string(unordered_stats_.print_count) + " times");
  Log("  Total operations: " + std::to_string(unordered_table_.GetOperationNumber()));

  // AvlTree
  Log("AvlTree:");
  Log("  emplace: " + std::to_string(avl_stats_.emplace_count) + " times");
  Log("  erase: " + std::to_string(avl_stats_.erase_count) + " times");
  Log("  find: " + std::to_string(avl_stats_.find_count) + " times");
  Log("  print: " + std::to_string(avl_stats_.print_count) + " times");
  Log("  Total operations: " + std::to_string(avl_tree_.GetOperationNumber()));
}

template <typename ValType>
void TableManager<ValType>::Run() {
  while (true) {
    std::cout << "\nMenu:\n";
    std::cout << "1. Insertion\n";
    std::cout << "2. Deletion\n";
    std::cout << "3. Search\n";
    std::cout << "4. Print\n";
    std::cout << "5. Polynomial operations\n";
    std::cout << "6. Operation statistics\n";
    std::cout << "7. Statistics reset\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter the command: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
      case 1:
        HandleEmplace();
        break;
      case 2:
        HandleErase();
        break;
      case 3:
        HandleFind();
        break;
      case 4:
        HandlePrint();
        break;
      case 5:
        HandlePolynomialOperations();
        break;
      case 6:
        ShowStats();
        break;
      case 7:
        ResetStats();
        break;
      case 8:
        return;
      default:
        std::cout << "Incorrect choice, try again\n";
    }
  }
}
