#pragma once

#include <vector>
#include <string>
#include "OpStats.h"

template <typename T>
class UnorderedTable {
private:
    std::vector<std::pair<std::string, T>> data;
    OpStats stats;

public:
    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        stats.add(1);
        for (auto& pair : data) {
            stats.add(2);

            stats.add(2);
            if (pair.first == key) {
                
                stats.add(2);
                pair.second = value; // обновляем значение, если ключ уже есть

                stats.add(1);
                return;
            }
        }
        stats.add(1); // выход из цикла


        stats.add(2);
        data.push_back({ key, value });
    }

    T* Find(const std::string& key) {
        for (auto& pair : data) {
            stats.add(2);

            stats.add(2);
            if (pair.first == key) {
                stats.add(3);
                return &pair.second;
            }
        }
        stats.add(2);
        return nullptr;
    }

    bool Remove(const std::string& key) {
        stats.add(1);
        for (size_t i = 0; i < data.size(); ++i) {
            stats.add(3);

            stats.add(3);
            if (data[i].first == key) {
                stats.add(3);
                data[i] = data.back();
                data.pop_back();
                return true;
            }
        }
        stats.add(2); // выход из цикла и return
        return false;
    }
};