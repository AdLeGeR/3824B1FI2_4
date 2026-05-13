#pragma once

#include <vector>
#include <string>
#include "OpStats.h"

template <typename T>
class OrderedTable {
private:
    std::vector<std::pair<std::string, T>> data;
    OpStats stats;

    int BinarySearch(const std::string& key, bool& found) {
        stats.add(4);
        int left = 0, right = data.size() - 1;
        while (left <= right) {
            stats.add(1);

            int mid = left + (right - left) / 2;
            stats.add(4);

            stats.add(3);
            if (data[mid].first == key) {
                found = true;
                stats.add(2);
                return mid;
            }

            stats.add(3);
            if (data[mid].first < key) {
                left = mid + 1;
                stats.add(2);
            }
            else {
                right = mid - 1;
                stats.add(2);
            }
        }
        stats.add(2);
        found = false;
        return left;
    }

public:
    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        bool found = false;
        stats.add(1);

        int pos = BinarySearch(key, found);

        stats.add(1);
        if (found) {
            stats.add(3);
            data[pos].second = value;
        }
        else {
            stats.add(data.size() - pos);
            data.insert(data.begin() + pos, { key, value });
        }
    }

    T* Find(const std::string& key) {
        bool found = false;
        stats.add(2);

        stats.add(2);
        int pos = BinarySearch(key, found);
        
        stats.add(1);
        if (found) {
            stats.add(4);
            return &data[pos].second;
        }

        stats.add(1);
        return nullptr;
    }

    bool Remove(const std::string& key) {
        bool found = false;
        stats.add(1);

        stats.add(2);
        int pos = BinarySearch(key, found);

        stats.add(1);
        if (found) {
            stats.add(data.size() - pos - 1);
            data.erase(data.begin() + pos);

            stats.add(1);
            return true;
        }

        stats.add(1);
        return false;
    }
};