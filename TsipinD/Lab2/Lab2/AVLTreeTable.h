#pragma once
#include <string>
#include <algorithm>
#include "OpStats.h"

template <typename T>
class AVLTreeTable {

private:
    struct Node {
        std::string key;
        T value;
        int height;
        Node* left;
        Node* right;

        Node(std::string k, T v) : key(std::move(k)), value(std::move(v)), height(1), left(nullptr), right(nullptr) {}
    };
    
    OpStats stats;
    Node* root = nullptr;

    int getHeight(Node* node) {
        
        stats.add(1);
        if (node == nullptr) {
            stats.add(1);
            return 0;
        }

        stats.add(2);
        return node->height;
    }

    void updateHeight(Node* node) {
        stats.add(1);
        if (node) {
            stats.add(6);
            node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    int getBalance(Node* node) {
        stats.add(1);
        if (node == nullptr) return 0;

        stats.add(6);
        return getHeight(node->right) - getHeight(node->left);
    }


    Node* rightRotate(Node* y) {
        stats.add(4);
        Node* x = y->left;
        Node* T2 = x->right;

        stats.add(4);
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        stats.add(1);
        return x;
    }

   
    Node* leftRotate(Node* x) {
        stats.add(4);
        Node* y = x->right;
        Node* T2 = y->left;

        stats.add(4);
        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        stats.add(1);
        return y;
    }


    Node* balance(Node* node) {
        updateHeight(node);
        stats.add(1);

        int bal = getBalance(node);
        stats.add(2);

        // перекос влево
        stats.add(1);
        if (bal == -2) {
            
            stats.add(3);
            if (getBalance(node->left) == 1) {
                stats.add(4);
                node->left = leftRotate(node->left); // левый-правый поворот
            }
            stats.add(2);
            return rightRotate(node);
        }

        // вправо
        
        else if (bal == 2) {
            
            stats.add(3);
            if (getBalance(node->right) == -1) {
                stats.add(4);
                node->right = rightRotate(node->right); // правый-левый поворот
            }
            stats.add(2);
            return leftRotate(node);
        }
        
        stats.add(1);
        return node;
    }

    Node* insertImpl(Node* node, const std::string& key, const T& value) {
        stats.add(1);
        if (node == nullptr) {
            stats.add(2);
            return new Node(key, value);
        }

        stats.add(2);
        if (key == node->key) {
            stats.add(2);
            node->value = value;
            stats.add(1);
            return node;
        }

        stats.add(2);
        if (key < node->key) {
            stats.add(4);
            node->left = insertImpl(node->left, key, value);
        }
        else {
            stats.add(4);
            node->right = insertImpl(node->right, key, value);
        }

        // возвращаем сбалансированный корень
        stats.add(2);
        return balance(node);
    }


    Node* findMin(Node* node) {

        while (node->left) {
            stats.add(2);

            stats.add(2);
            node = node->left;
        }
        stats.add(2);
        return node;
    }

    Node* removeMin(Node* node) {
        stats.add(2);
        if (node->left == nullptr) {
            stats.add(2);
            return node->right;
        }

        stats.add(4);
        node->left = removeMin(node->left);
        stats.add(2);
        return balance(node);
    }


    Node* removeImpl(Node* node, const std::string& key, bool& removed) {
        stats.add(2);
        if (node == nullptr) return nullptr;

        stats.add(1);
        if (key == node->key) {
            stats.add(1);
            removed = true; // флаг, что узел найден

            // нет одного из детей
            stats.add(5);
            if (node->left == nullptr || node->right == nullptr) {
                // ternary ? : (check: 1, ->: 1, =: 1) -> 3
                stats.add(3);
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            // есть оба ребенка
            else {
                Node* minNode = findMin(node->right);
                node->key = minNode->key;
                node->value = minNode->value;
                node->right = removeMin(node->right);
                stats.add(12);
            }
        }
        else {
            stats.add(2);
            if (key < node->key) {

                stats.add(4);
                node->left = removeImpl(node->left, key, removed);
            }
            else {
                stats.add(4);
                node->right = removeImpl(node->right, key, removed);
            }
        }
        stats.add(2);
        return balance(node);
    }

    void destroyTree(Node* node) {
        stats.add(1);
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
            stats.add(5);
        }
    }

public:
    std::string GetRootKey() const {
        if (root == nullptr) return "";
        return root->key;
    }

    ~AVLTreeTable() { destroyTree(root); }

    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        stats.add(2);
        root = insertImpl(root, key, value);
    }

    T* Find(const std::string& key) {
        stats.add(2);
        Node* current = root;

        while (current != nullptr) {
            stats.add(1);

            stats.add(5);
            if (key == current->key) return &current->value;

            stats.add(4);
            if (key < current->key) current = current->left;
            else current = current->right;
            stats.add(2);
        }
        stats.add(2);
        return nullptr;
    }

    bool Remove(const std::string& key) {
        bool removed = false;
        stats.add(1);

        root = removeImpl(root, key, removed);
        stats.add(3);
        return removed; // true если удалили, false если ключа в дереве не было
    }

    int GetTotalHeight() {
        stats.add(3);
        return getHeight(this->root);
    }
};