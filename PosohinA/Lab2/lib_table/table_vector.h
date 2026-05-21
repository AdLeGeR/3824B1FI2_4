#ifndef TABLE_TABLE_VECTOR_H
#define TABLE_TABLE_VECTOR_H
#include "../lib_table/table.h"
#include <vector>

template <class T> class TableVector : public Table<T> {
    std::vector<std::pair<std::string, T>> _data;
    int _countOper;

public:
    TableVector(size_t size = 0);
    ~TableVector() override;

    void insert(const std::string&, const T&) override;
    T* find(const std::string&) override;
    void remove(const std::string&) override;
    int getCountOper() const override;
};

template <class T> TableVector<T>::TableVector(size_t size) : _countOper(0) {
    _data.reserve(size);
}

template <class T> TableVector<T>::~TableVector() {}

template <class T>
void TableVector<T>::insert(const std::string& key, const T& val) {
    _countOper++;
    for (size_t i = 0; i < _data.size(); i++) {
        _countOper += 4;
        if (_data[i].first == key) {
            _data[i].second = val;
            _countOper += 2;
            return;
        }
    }
    _data.push_back({ key, val });
    _countOper++;
}

template <class T> T* TableVector<T>::find(const std::string& key) {
    _countOper++;
    for (size_t i = 0; i < _data.size(); i++) {
        _countOper += 4;
        if (_data[i].first == key)
            return &_data[i].second;
    }
    _countOper++;
    return nullptr;
}

template <class T> void TableVector<T>::remove(const std::string& key) {
    _countOper++;
    for (size_t i = 0; i < _data.size(); i++) {
        _countOper += 4;
        if (_data[i].first == key) {
            _countOper++;
            _data.erase(_data.begin() + i);
            _countOper++;
            return;
        }
    }
    _countOper++;
    std::cout << "Element not found" << std::endl;
}

template <class T> int TableVector<T>::getCountOper() const {
    return _countOper;
}
#endif // !TABLE_TABLE_VECTOR_H
