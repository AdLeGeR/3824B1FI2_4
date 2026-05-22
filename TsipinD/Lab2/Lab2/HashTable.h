
#pragma once
#include <vector>
#include <list>
#include <string>
#include "OpStats.h"

template <typename T>
class HashTable {
	std::vector<std::list<std::pair<std::string, T>>> buckets;
	size_t bucketCount;
	OpStats stats;

	size_t getHash(const std::string & key) {
		size_t hash = 5381;
		stats.add(2);

		stats.add(1);
		for (char c : key) {
			stats.add(3);

			hash = ((hash << 5) + hash) + static_cast<size_t>(c);
			stats.add(5);
		}
		stats.add(3);
		return hash % bucketCount;
	}
public:
	OpStats GetStats() const { return stats; }
	void ResetStats() { stats.Reset(); }

	HashTable(size_t size = 101) : bucketCount(size) {
		buckets.resize(bucketCount);
	}

	void Insert(const std::string& key, const T& value) {
		size_t index = getHash(key);
		stats.add(3);

		stats.add(2); // инициализация, индекс
		for (auto& pair : buckets[index]) {
			stats.add(2); // инкремент, проверка !=0

			stats.add(2);
			if (pair.first == key) {
				
				stats.add(3);
				pair.second = value;
				return;
			}
		}
		stats.add(1); // последняя проверка цикла

		stats.add(4); // индекс, метод, создание пары
		buckets[index].push_back({ key, value });
	}

	T* Find(const std::string& key) {
		size_t index = getHash(key);
		stats.add(2); // присваивание, метод

		stats.add(2); // инициализация, индекс
		for (auto& pair : buckets[index]) {
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
		size_t index = getHash(key);
		stats.add(2);

		auto& node = buckets[index];
		stats.add(2);

		stats.add(2); 
		for (auto it = node.begin(); it != node.end(); ++it) {
			stats.add(2);
			
			stats.add(2);
			if (it->first == key) {
				node.erase(it);
				stats.add(2);
				return true;
			}
		}
		stats.add(2);
		return false;
	}
};