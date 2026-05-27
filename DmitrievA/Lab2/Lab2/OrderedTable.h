#pragma once
#include <string>
#include <vector>
#include "Counter.h"
using std::string;
using std::vector;

template<typename T>
class AVLOrderedTable
{
public:
	AVLOrderedTable();
	~AVLOrderedTable();
	void insert(string key, T value);
	void remove(string key);
	T* find(string key);
	unsigned getCounter();
	void clear();
private:
	Counter counter;
	struct Node {
		string key;
		T value;
		Node* left;
		Node* right;
		int height;
		Node(string k, T v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
	};
	Node* root; // Ensure the root member is declared in the private section of the class
	int height(Node* node);
	int balanceFactor(Node* node);
	Node* rotateRight(Node* y);
	Node* rotateLeft(Node* x);
	Node* insert(Node* node, string key, T value);
	Node* remove(Node* node, string key);
	Node* minValueNode(Node* node);
	void freeSubTree(Node* node);
};


template<typename T>
class HashOrderedTable
{
	public:
	HashOrderedTable(size_t capacity = 16);
	~HashOrderedTable();
	void insert(string key, T value);
	void remove(string key);
	T* find(string key);
	unsigned getCounter();
	void clear();
private:
	struct Node {
		string key;
		T value;
		Node* next;
		Node(string k, T v) : key(k), value(v), next(nullptr) {}
	};
	Counter counter;
	std::vector<Node*> table;
	size_t capacity;
	size_t hash(string key);
	void freeSubTree(Node* node);
};