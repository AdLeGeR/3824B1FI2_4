#ifndef TABLE_TABLE_HASH_H
#define TABLE_TABLE_HASH_H
#include "../lib_table/table.h"
#include <vector>

enum class State { EMPTY, OCCUPIED, DELETED };

template <class T> struct NodeHash {
    NodeHash();
    NodeHash(const std::string&, const T&);
    std::string _key;
    T _data;
    State _now;
};

template <class T> NodeHash<T>::NodeHash() : _now(State::EMPTY) {}

template <class T>
NodeHash<T>::NodeHash(const std::string& key, const T& data)
    : _key(key), _data(data), _now(State::OCCUPIED) {
}

template <class T> class TableHash : public Table<T> {
    std::vector<NodeHash<T>> _table;
    size_t _size;
    int _countOper;
    size_t hash(const std::string&);
    void realloc();

public:
    TableHash(size_t raz = 16);
    ~TableHash() override;

    void insert(const std::string&, const T&) override;
    T* find(const std::string&) override;
    void remove(const std::string&) override;
    int getCountOper() const override;
};

template <class T> size_t TableHash<T>::hash(const std::string& str) {
    _countOper++;
    size_t sum = 0;
    _countOper++;
    for (size_t i = 0; i < str.size(); i++) {
        sum += str[i] * (i + 1);
        _countOper += 5;
    }
    _countOper += 2;
    return sum % _table.size();
}

template <class T> void TableHash<T>::realloc() {

    _countOper += 2;
    if (_size <= _table.size() * 0.7)
        return;

    std::vector<NodeHash<T>> oldTable;
    oldTable.swap(_table);
    _table.resize(oldTable.size() * 2);
    _size = 0;
    _countOper += 2;

    _countOper++;
    for (size_t i = 0; i < oldTable.size(); i++) {
        _countOper += 4;
        if (oldTable[i]._now == State::OCCUPIED) {
            _countOper += 2;
            insert(oldTable[i]._key, oldTable[i]._data);
        }
    }
    _countOper++;
}

template <class T>
TableHash<T>::TableHash(size_t raz) : _table(raz), _size(0), _countOper(0) {}

template <class T> TableHash<T>::~TableHash() { _table.clear(); }

template <class T>
void TableHash<T>::insert(const std::string& key, const T& data) {
    realloc();
    size_t index = hash(key);
    bool flage = false;
    _countOper += 3;
    if (_table[index]._now == State::OCCUPIED) {
        size_t temp = index;
        _countOper += 2;
        while (_table[temp]._now == State::OCCUPIED) {
            _countOper += 2;
            if (_table[temp]._key == key) {
                _table[temp]._data = data;
                flage = true;
                _countOper += 2;
                break;
            }
            temp = (temp + 1) % _table.size();
            _countOper += 3;

            _countOper++;
            if (temp == index)
                break;
        }
        index = temp;
        _countOper++;
    }
    _countOper++;
    if (!flage) {
        _countOper++;
        if (_table[index]._now != State::OCCUPIED) {
            _table[index]._key = key;
            _table[index]._data = data;
            _table[index]._now = State::OCCUPIED;
            _size++;
            _countOper += 7;
        }
    }
}

template <class T> T* TableHash<T>::find(const std::string& key) {
    size_t index = hash(key);
    _countOper++;

    _countOper += 2;
    if (_table[index]._now == State::OCCUPIED) {
        _countOper += 2;
        if (_table[index]._key == key) {
            _countOper++;
            return &(_table[index]._data);
        }
    }
    _countOper += 2;
    if (_table[index]._now == State::EMPTY)
        return nullptr;

    _countOper += 3;
    for (size_t i = (index + 1) % _table.size(); i != index;
        i = (i + 1) % _table.size()) {
        _countOper += 5;
        if (_table[i]._now != State::OCCUPIED)
            continue;

        _countOper += 2;
        if (_table[i]._key == key) {
            _countOper++;
            return &(_table[i]._data);
        }

        if (_table[i]._now == State::EMPTY)
            break;
    }

    return nullptr;
}

template <class T> void TableHash<T>::remove(const std::string& key) {
    size_t index = hash(key);
    _countOper += 3;
    if (_table[index]._now == State::OCCUPIED) {
        _countOper += 2;
        if (_table[index]._key == key) {
            _table[index]._now = State::DELETED;
            _size--;
            _countOper += 3;
            return;
        }
    }
    _countOper += 2;
    if (_table[index]._now == State::EMPTY) {
        std::cout << "Element not found" << std::endl;
        return;
    }

    _countOper += 3;
    for (int i = (index + 1) % _table.size(); i != index;
        i = (i + 1) % _table.size()) {
        _countOper += 5;
        if (_table[i]._now != State::OCCUPIED)
        {
            if (_table[i]._now == State::EMPTY)
                break;
            continue;
        }

        _countOper++;
        if (_table[i]._key == key) {
            _table[i]._now = State::DELETED;
            _size--;
            _countOper += 2;
            return;
        }
    }
    std::cout << "Element not found" << std::endl;
    return;
}

template <class T> int TableHash<T>::getCountOper() const { return _countOper; }
#endif // !TABLE_TABLE_HASH_H