#pragma once
#include <iostream>
#include <string>
#include <utility>  

template <typename ValType>
struct AvlNode {
  std::string key;
  ValType value;
  int height;
  AvlNode* left;
  AvlNode* right;

  AvlNode(const std::string& k, const ValType& val)
      : key(k), value(val), height(1), left(nullptr), right(nullptr) {}
};

template <typename ValType>
class AvlTree {
 public:
  AvlTree();
  AvlTree(const AvlTree& other);
  AvlTree& operator=(const AvlTree& other);
  ~AvlTree();

  ValType* Find(const std::string& key);
  void EmplaceBack(const std::string& str, const ValType& val);
  void Erase(const std::string& str);
  void Print();
  void PrintOperations() const;
  int GetOperationNumber() const;
  void Reset();

 private:
  int avl_counters_;
  AvlNode<ValType>* root_;

  AvlNode<ValType>* CopyTree(AvlNode<ValType>* node);
  int GetHeight(AvlNode<ValType>* node);
  int HeightDiff(AvlNode<ValType>* node);
  void RecountHeight(AvlNode<ValType>* node);
  AvlNode<ValType>* RightRotation(AvlNode<ValType>* parent);
  AvlNode<ValType>* LeftRotation(AvlNode<ValType>* parent);
  AvlNode<ValType>* BigLeftRotation(AvlNode<ValType>* parent);
  AvlNode<ValType>* BigRightRotation(AvlNode<ValType>* parent);
  AvlNode<ValType>* Balance(AvlNode<ValType>* parent);
  AvlNode<ValType>* FindMin(AvlNode<ValType>* node); // Removal logics
  AvlNode<ValType>* DeleteMin(AvlNode<ValType>* node); // Removal logics
  AvlNode<ValType>* PrivateErase(AvlNode<ValType>* node, const std::string& str); // Removal logics
  AvlNode<ValType>* PrivateEmplaceBack(AvlNode<ValType>* node, 
                                       const std::string& str, 
                                       const ValType& val);
  void PrivatePrint(AvlNode<ValType>* node);
  AvlNode<ValType>* FindNode(const std::string& key, AvlNode<ValType>* node);
  void Clear(AvlNode<ValType>* node);
};

template <typename ValType>
AvlTree<ValType>::AvlTree() : avl_counters_(0), root_(nullptr) {}

template <typename ValType>
AvlTree<ValType>::AvlTree(const AvlTree& other) : avl_counters_(0), root_(nullptr) {
  avl_counters_++;
  root_ = CopyTree(other.root_);
}

template <typename ValType>
AvlTree<ValType>& AvlTree<ValType>::operator=(const AvlTree& other) {
  avl_counters_++;
  if (this != &other) {
    Clear(root_);
    root_ = CopyTree(other.root_);
  }
  return *this;
}

template <typename ValType>
AvlTree<ValType>::~AvlTree() {
  Clear(root_);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::CopyTree(AvlNode<ValType>* node) {
  avl_counters_++;
  if (node == nullptr) return nullptr;
  avl_counters_ += 2;
  AvlNode<ValType>* new_node = new AvlNode<ValType>(node->key, node->value);
  new_node->height = node->height;
  new_node->left = CopyTree(node->left);
  new_node->right = CopyTree(node->right);
  return new_node;
}

template <typename ValType>
int AvlTree<ValType>::GetHeight(AvlNode<ValType>* node) {
  avl_counters_++;
  return node ? node->height : 0;
}

template <typename ValType>
int AvlTree<ValType>::HeightDiff(AvlNode<ValType>* node) {
  avl_counters_++;
  return GetHeight(node->right) - GetHeight(node->left);
}

template <typename ValType>
void AvlTree<ValType>::RecountHeight(AvlNode<ValType>* node) {
  avl_counters_ += 3;
  int left_height = GetHeight(node->left);
  int right_height = GetHeight(node->right);
  node->height = (right_height < left_height ? left_height : right_height) + 1;
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::RightRotation(AvlNode<ValType>* parent) {
  avl_counters_ += 4;
  AvlNode<ValType>* child = parent->left;
  parent->left = child->right;
  child->right = parent;
  RecountHeight(parent);
  RecountHeight(child);
  return child;
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::LeftRotation(AvlNode<ValType>* parent) {
  avl_counters_ += 4;
  AvlNode<ValType>* child = parent->right;
  parent->right = child->left;
  child->left = parent;
  RecountHeight(parent);
  RecountHeight(child);
  return child;
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::BigLeftRotation(AvlNode<ValType>* parent) {
  avl_counters_++;
  if (HeightDiff(parent->right) < 0) {
	avl_counters_++;
    parent->right = RightRotation(parent->right);
  }
  avl_counters_++;
  return LeftRotation(parent);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::BigRightRotation(AvlNode<ValType>* parent) {
  avl_counters_++;
  if (HeightDiff(parent->left) > 0) {
	avl_counters_++;
    parent->left = LeftRotation(parent->left);
  }
  avl_counters_++;
  return RightRotation(parent);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::Balance(AvlNode<ValType>* parent) {
  avl_counters_++;
  RecountHeight(parent);
  if (HeightDiff(parent) == 2) return BigLeftRotation(parent);
  avl_counters_++;
  if (HeightDiff(parent) == -2) return BigRightRotation(parent);
  avl_counters_++;
  return parent;
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::FindMin(AvlNode<ValType>* node) {
  while (node && node->left != nullptr) {
	avl_counters_++;
    node = node->left;
  }
  avl_counters_++;
  return node;
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::DeleteMin(AvlNode<ValType>* node) {
  avl_counters_++;
  if (node->left == nullptr) return node->right;
  avl_counters_ += 2;
  node->left = DeleteMin(node->left);
  return Balance(node);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::PrivateErase(AvlNode<ValType>* node, 
                                                 const std::string& str) {
  avl_counters_++;
  if (node == nullptr) return nullptr;
  
  avl_counters_++;
  if (node->key > str) {
	avl_counters_++;
    node->left = PrivateErase(node->left, str);
  } else if (node->key < str) {
	avl_counters_ += 2;
    node->right = PrivateErase(node->right, str);
  } else {
	avl_counters_ += 3;
    AvlNode<ValType>* left_child = node->left;
    AvlNode<ValType>* right_child = node->right;
    
	avl_counters_++;
    if (right_child == nullptr) {
      avl_counters_ += 2;
      delete node;
      return left_child;
    }
    
	avl_counters_ += 4;
    AvlNode<ValType>* min_node = FindMin(right_child);
    node->key = min_node->key;
    node->value = min_node->value;
    node->right = DeleteMin(right_child);
    return Balance(node);
  }
  return Balance(node);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::PrivateEmplaceBack(AvlNode<ValType>* node, 
                                                       const std::string& str, 
                                                       const ValType& val) {
  avl_counters_++;
  if (node == nullptr) {
	avl_counters_++;
    return new AvlNode<ValType>(str, val);
  }
  avl_counters_ ++;
  if (str < node->key) {
	avl_counters_++;
    node->left = PrivateEmplaceBack(node->left, str, val);
  } else if (str == node->key) {
	avl_counters_ += 3;
    node->value = val;
    return Balance(node);
  } else {
	avl_counters_ += 1;
    node->right = PrivateEmplaceBack(node->right, str, val);
  }
  avl_counters_++;
  return Balance(node);
}

template <typename ValType>
void AvlTree<ValType>::PrivatePrint(AvlNode<ValType>* node) {
  avl_counters_+=2;
  if (node == nullptr) return;
  PrivatePrint(node->left);
  std::cout << node->key << " " << node->value << "\n";
  PrivatePrint(node->right);
}

template <typename ValType>
AvlNode<ValType>* AvlTree<ValType>::FindNode(const std::string& key, 
                                             AvlNode<ValType>* node) {
  avl_counters_++;
  if (node == nullptr) return nullptr;
  avl_counters_++;
  if (key < node->key) return FindNode(key, node->left);
  avl_counters_++;
  if (key > node->key) return FindNode(key, node->right);
  avl_counters_++;
  return node;
}

template <typename ValType>
void AvlTree<ValType>::Clear(AvlNode<ValType>* node) {
  avl_counters_ ++;
  if (node == nullptr) return;
  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename ValType>
ValType* AvlTree<ValType>::Find(const std::string& key) {
  avl_counters_++;
  AvlNode<ValType>* node = FindNode(key, root_);
  avl_counters_++;
  if (node == nullptr) return nullptr;
  avl_counters_++;
  return &node->value;
}

template <typename ValType>
void AvlTree<ValType>::EmplaceBack(const std::string& str, const ValType& val) {
  avl_counters_++;
  root_ = PrivateEmplaceBack(root_, str, val);
}

template <typename ValType>
void AvlTree<ValType>::Erase(const std::string& str) {
  avl_counters_++;
  root_ = PrivateErase(root_, str);
}

template <typename ValType>
void AvlTree<ValType>::Print() {
  PrivatePrint(root_);
}

template <typename ValType>
void AvlTree<ValType>::PrintOperations() const {
  std::cout << "Total number of operations: " << avl_counters_ << std::endl;
}

template <typename ValType>
int AvlTree<ValType>::GetOperationNumber() const {
  return avl_counters_;
}

template <typename ValType>
void AvlTree<ValType>::Reset() {
  avl_counters_ = 0;
}
