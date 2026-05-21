#ifndef TABLE_TABLE_AVL_H
#define TABLE_TABLE_AVL_H
#include "../lib_table/table.h"

template <class T> struct NodeAVL {
    NodeAVL(std::pair<std::string, T>& data, NodeAVL<T>* left = nullptr,
        NodeAVL<T>* right = nullptr);
    NodeAVL<T>* _left;
    NodeAVL<T>* _right;
    int _height;
    std::pair<std::string, T> _data;
};

template <class T>
NodeAVL<T>::NodeAVL(std::pair<std::string, T>& data, NodeAVL<T>* left,
    NodeAVL<T>* right)
    : _right(right), _left(left), _data(data), _height(1) {
}

template <class T> class TableAVL : public Table<T> {
    NodeAVL<T>* _head;
    int _countOper;

    NodeAVL<T>* big_right_turn(NodeAVL<T>*);
    NodeAVL<T>* small_right_turn(NodeAVL<T>*);
    NodeAVL<T>* big_left_turn(NodeAVL<T>*);
    NodeAVL<T>* small_left_turn(NodeAVL<T>*);
    NodeAVL<T>* balance(NodeAVL<T>*);
    int height(NodeAVL<T>*);
    int balanceRaz(NodeAVL<T>*);
    void updateHeight(NodeAVL<T>*);
    NodeAVL<T>* findMin(NodeAVL<T>*);
    void clear(NodeAVL<T>*);
    T* findRec(NodeAVL<T>*, const std::string&);
    NodeAVL<T>* removeRec(NodeAVL<T>* node, const std::string&);
    NodeAVL<T>* insertRec(NodeAVL<T>*, const std::string&, const T&);

public:
    TableAVL();
    ~TableAVL() override;

    TableAVL(const TableAVL&) = delete;
    TableAVL& operator=(const TableAVL&) = delete;

    void insert(const std::string&, const T&) override;
    T* find(const std::string&) override;
    void remove(const std::string&) override;
    int getCountOper() const override;

    NodeAVL<T>* getRoot() const { return _head; }
    NodeAVL<T>* getLeft(NodeAVL<T>*) const;
    NodeAVL<T>* getRight(NodeAVL<T>*) const;
    std::string getKey(NodeAVL<T>*) const;
};

template <class T> NodeAVL<T>* TableAVL<T>::getRight(NodeAVL<T>* node) const {
    if (node != nullptr) {
        return node->_right;
    }
    return nullptr;
}

template <class T> NodeAVL<T>* TableAVL<T>::getLeft(NodeAVL<T>* node) const {
    if (node != nullptr) {
        return node->_left;
    }
    return nullptr;
}

template <class T> std::string TableAVL<T>::getKey(NodeAVL<T>* node) const {
    if (node != nullptr) {
        return node->_data.first;
    }
    return "";
}

template <class T> int TableAVL<T>::height(NodeAVL<T>* node) {
    _countOper++;
    if (node != nullptr)
        return node->_height;
    else
        return 0;
}

template <class T> int TableAVL<T>::balanceRaz(NodeAVL<T>* node) {
    _countOper++;
    return height(node->_left) - height(node->_right);
}

template <class T> void TableAVL<T>::updateHeight(NodeAVL<T>* node) {
    if (node) {
        node->_height = 1 + std::max(height(node->_left), height(node->_right));
        _countOper += 2;
    }
}

template <class T> NodeAVL<T>* TableAVL<T>::small_right_turn(NodeAVL<T>* node) {
    _countOper += 3;
    if (!node || !node->_left) 
        return node;

    _countOper += 3;

    NodeAVL<T>* leftChild = node->_left;
    node->_left = leftChild->_right;
    leftChild->_right = node;

    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

template <class T> NodeAVL<T>* TableAVL<T>::small_left_turn(NodeAVL<T>* node) {
    _countOper += 3;
    if (!node || !node->_right) 
        return node;

    _countOper += 3;

    NodeAVL<T>* rightChild = node->_right;
    node->_right = rightChild->_left;
    rightChild->_left = node;

    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

template <class T> NodeAVL<T>* TableAVL<T>::big_right_turn(NodeAVL<T>* node) {
    _countOper++;
    node->_left = small_left_turn(node->_left);
    return small_right_turn(node);
}

template <class T> NodeAVL<T>* TableAVL<T>::big_left_turn(NodeAVL<T>* node) {
    _countOper++;
    node->_right = small_right_turn(node->_right);
    return small_left_turn(node);
}

template <class T> NodeAVL<T>* TableAVL<T>::balance(NodeAVL<T>* node) {
    _countOper++;
    if (!node)
        return nullptr;

    updateHeight(node);
    int raz = balanceRaz(node);
    _countOper++;

    _countOper++;
    if (raz > 1) {
        if (balanceRaz(node->_left) < 0) {
            _countOper++;
            return big_right_turn(node);
        }
        return small_right_turn(node);
    }

    _countOper++;
    if (raz < -1) {
        if (balanceRaz(node->_right) > 0) {
            _countOper++;
            return big_left_turn(node);
        }
        return small_left_turn(node);
    }
    return node;
}

template <class T> TableAVL<T>::TableAVL() : _countOper(0), _head(nullptr) {};
template <class T> TableAVL<T>::~TableAVL() { clear(_head); }

template <class T>
NodeAVL<T>* TableAVL<T>::insertRec(NodeAVL<T>* node, const std::string& key,
    const T& val) {
    _countOper++;
    if (node == nullptr) {
        NodeAVL<T>* newNode = new NodeAVL<T>(std::pair<std::string, T>(key, val));
        return newNode;
    }

    _countOper++;
    if (key < node->_data.first) {
        node->_left = insertRec(node->_left, key, val);
        _countOper++;
    }
    else if (key > node->_data.first) {
        _countOper++;
        node->_right = insertRec(node->_right, key, val);
        _countOper++;
    }

    else {
        _countOper++;
        node->_data.second = val;
        _countOper++;
        return node;
    }
    return balance(node);
}

template <class T>
void TableAVL<T>::insert(const std::string& key, const T& val) {
    _head = insertRec(_head, key, val);
}

template <class T> NodeAVL<T>* TableAVL<T>::findMin(NodeAVL<T>* node) {
    _countOper++;
    if (!node)
        return nullptr;

    while (node->_left != nullptr) {
        _countOper++;
        node = node->_left;
    }
    return node;
}

template <class T>
NodeAVL<T>* TableAVL<T>::removeRec(NodeAVL<T>* node, const std::string& key) {
    _countOper++;

    if (!node) {
        std::cout << "Element not found" << std::endl;
        return nullptr;
    }

    _countOper++;
    if (key < node->_data.first) {
        _countOper += 2;
        node->_left = removeRec(node->_left, key);
    }
    else if (key > node->_data.first) {
        _countOper += 2;
        node->_right = removeRec(node->_right, key);
    }
    else {

        if (node->_left == nullptr) {
            NodeAVL<T>* right = node->_right;
            delete node;
            return right;
        }

        if (node->_right == nullptr) {
            NodeAVL<T>* left = node->_left;
            delete node;
            return left;
        }

        NodeAVL<T>* minRight = findMin(node->_right);
        node->_data = minRight->_data;
        node->_right = removeRec(node->_right, minRight->_data.first);
        _countOper += 3;
    }

    return balance(node);
}

template <class T> void TableAVL<T>::remove(const std::string& key) {
    _head = removeRec(_head, key);
}

template <class T> void TableAVL<T>::clear(NodeAVL<T>* node) {
    if (node != nullptr) {
        clear(node->_left);
        clear(node->_right);
        delete node;
    }
}

template <class T>
T* TableAVL<T>::findRec(NodeAVL<T>* node, const std::string& key) {
    _countOper++;
    if (node == nullptr)
        return nullptr;

    _countOper++;
    if (key == node->_data.first)
        return &(node->_data.second);

    _countOper++;
    if (key < node->_data.first)
        return findRec(node->_left, key);

    else
        return findRec(node->_right, key);
}

template <class T> T* TableAVL<T>::find(const std::string& key) {
    return findRec(_head, key);
}

template <class T> int TableAVL<T>::getCountOper() const { return _countOper; }
#endif // !TABLE_TABLE_AVL_H
