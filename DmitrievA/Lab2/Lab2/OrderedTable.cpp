#include "OrderedTable.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::max;

template<typename T>
AVLOrderedTable<T>::AVLOrderedTable() {
	this->root = nullptr;
}
template<typename T>
void AVLOrderedTable<T>::freeSubTree(AVLOrderedTable::Node* node) {
	if (node) {
		freeSubTree(node->left);
		freeSubTree(node->right);
		delete node;
	}
}

template<typename T>
AVLOrderedTable<T>::~AVLOrderedTable<T>() {
	freeSubTree(root);
}

template<typename T>
void AVLOrderedTable<T>::insert(string key, T value) {
	counter = 0;
	root = insert(root, key, value);
}

template<typename T>
int AVLOrderedTable<T>::height(AVLOrderedTable<T>::Node* node) {
	if (node) {
		counter += 3;
		return node->height;
	}
	counter += 2;
	return 0;
}

template<typename T>
int AVLOrderedTable<T>::balanceFactor(AVLOrderedTable<T>::Node* node) {
	if (node) {
		counter += 5;
		return height(node->left) - height(node->right);
	}
	counter += 2;
	return 0;
}

template<typename T>
AVLOrderedTable<T>::Node* AVLOrderedTable<T>::rotateRight(AVLOrderedTable<T>::Node* y) {
	counter += 14;
	AVLOrderedTable<T>::Node* x = y->left;//2
	AVLOrderedTable<T>::Node* T2 = x->right;//2
	x->right = y;//2
	y->left = T2;//2
	y->height = 1 + max(height(y->left), height(y->right));//5
	x->height = 1 + max(height(x->left), height(x->right));//5
	return x;//1
}

template<typename T>
AVLOrderedTable<T>::Node* AVLOrderedTable<T>::rotateLeft(AVLOrderedTable<T>::Node* x) {
	counter += 14;
	AVLOrderedTable<T>::Node* y = x->right;
	AVLOrderedTable<T>::Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return y;
}



template<typename T>
AVLOrderedTable<T>::Node* AVLOrderedTable<T>::insert(AVLOrderedTable<T>::Node* node, string key, T value) {
	counter+=2;
	if (!node) {
		counter++;
		return new Node(key, value);
	}
	counter += 3;
	if (key < node->key) {
		node->left = insert(node->left, key, value);
		counter += 2;
	}
	else if (key > node->key) {
		node->right = insert(node->right, key, value);
		counter += 5;
	}
	else {
		node->value = value;
		counter += 5;
		return node;
	}
	counter += 7;//считаем max за 3 операции:
				//if (a > b) return a;
				//else return b
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

template<typename T>
AVLOrderedTable<T>::Node* AVLOrderedTable<T>::minValueNode(AVLOrderedTable<T>::Node* node) {
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
template<typename T>
AVLOrderedTable<T>::Node* AVLOrderedTable<T>::remove(AVLOrderedTable<T>::Node* node, string key) {
	counter += 2;
	if (!node) {
		counter++;
		return node;
	}
	counter += 3;
	if (key < node->key) {//3
		counter += 3;
		node->left = remove(node->left, key);//3
	}
	else if (key > node->key) {
		counter += 6;
		node->right = remove(node->right, key);//3
	}
	else {
		counter += 8;
		if (!node->left || !node->right) {//5
			counter += 4;
			Node* temp = node->left ? node->left : node->right;
			counter += 2;
			if (!temp) {
				temp = node;
				node = nullptr;
				counter += 2;
			}
			else {
				counter += 3;
				*node = *temp;
			}
			counter++;
			delete temp;
		}
		else {
			counter += 2;
			Node* temp = minValueNode(node->right);
			counter += 10;
			node->key = temp->key;//3
			node->value = temp->value;//3
			node->right = remove(node->right, temp->key);//4
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
template<typename T>
void AVLOrderedTable<T>::remove(string key) {
	counter = 0;
	root = remove(root, key);
}

template<typename T>
T* AVLOrderedTable<T>::find(string key) {
	counter = 0;
	counter++;
	Node* current = root;
	counter++;
	while (current) {
		counter += 3;
		if (key < current->key) {
			counter += 2;
			current = current->left;
		}
		else if (key > current->key) {
			counter += 5;
			current = current->right;
		}
		else {
			counter += 5;
			return &current->value;
		}
	}
	counter += 2;
	return nullptr;
}

template<typename T>
unsigned AVLOrderedTable<T>::getCounter() {
	return counter.getCount();
}

template<typename T>
void AVLOrderedTable<T>::clear() {
	freeSubTree(root);
	root = nullptr;
}




//template<typename T>
//HashOrderedTable<T>::HashOrderedTable(size_t capacity) : table{vector<HashOrderedTable<T>::Node*>(capacity, nullptr)} {}
//
//template<typename T>
//HashOrderedTable<T>::~HashOrderedTable() {
//	for (int i = 0; i < capacity; i++) {
//		Node* node = table[i];
//		while (node) {
//			Node* next = node->next;
//			delete node;
//			node = next;
//		}
//	}
//}
//
//
//template<typename T>
//size_t HashOrderedTable<T>::hash(string key) {
//	size_t hash = 5381;
//	stats.add(2);
//
//	stats.add(1);
//	for (char c : key) {
//		stats.add(3);
//
//		hash = ((hash << 5) + hash) + static_cast<size_t>(c);
//		stats.add(5);
//	}
//	stats.add(3);
//	return hash % bucketCount;
//}
//
//template<typename T>
//void HashOrderedTable<T>::insert(string key, T value) {
//	size_t i = hash();
//	
//}



template<typename T>
HashOrderedTable<T>::HashOrderedTable(size_t capacity) {
	this->capacity = capacity;
	table.resize(capacity, nullptr);
}

// Деструктор
template<typename T>
HashOrderedTable<T>::~HashOrderedTable() {
	for (size_t i = 0; i < capacity; ++i) {
		freeSubTree(table[i]);
	}
}

template<typename T>
void HashOrderedTable<T>::freeSubTree(Node* node) {
	counter += 2;
	if (node != nullptr) {
		counter += 1;
		freeSubTree(node->next);
		delete node;
	}
}

template<typename T>
size_t HashOrderedTable<T>::hash(std::string key) {
	counter++;
	size_t hashValue = 5381;
	for (char ch : key) {
		counter+=3;
		hashValue = hashValue * 31 + ch;
	}
	counter += 2;
	return hashValue % capacity;
}

template<typename T>
void HashOrderedTable<T>::insert(std::string key, T value) {
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


template<typename T>
T* HashOrderedTable<T>::find(std::string key) {
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


template<typename T>
void HashOrderedTable<T>::remove(std::string key) {
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
			}
			else {
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

template<typename T>
unsigned HashOrderedTable<T>::getCounter() {
	return counter.getCount();
}

template<typename T>
void HashOrderedTable<T>::clear() {
	for (size_t i = 0; i < capacity; ++i) {
		freeSubTree(table[i]);
		table[i] = nullptr;
	}
}