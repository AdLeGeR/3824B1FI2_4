"Copyright 2026 Alexey Dmitriev"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../Lab2/OrderedTable.h"
#include "../Lab2/Polinom.h"
#include "../Lab2/UnorderedTable.h"

    using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

struct BenchResult {
  int64_t totalOps = 0;
  double durationMs = 0;
};

string generateRandomKey(size_t length) {
  static const char alphabet[] =
      "abcdefg"
      "hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  static mt19937 gen(42);
  uniform_int_distribution<> dis(0, sizeof(alphabet) - 2);
  string s;
  for (size_t i = 0; i < length; ++i)
    s += alphabet[dis(gen)];
  return s;
}

Polinom generateRandomPolinom() {
  static mt19937 gen(43);
  uniform_real_distribution<> dis(-100.0, 100.0);
  return Polinom(dis(gen));
}

template <typename TTable>
void runExperiment(const string& tableName, const vector<string>& keys,
                   const vector<Polinom>& values) {
  TTable table;
  size_t n = keys.size();
  BenchResult insertRes, findRes, removeRes;

  auto start = chrono::high_resolution_clock::now();
  for (size_t i = 0; i < n; ++i) {
    table.insert(keys[i], values[i]);
    insertRes.totalOps += table.getCount();
  }
  auto end = chrono::high_resolution_clock::now();
  insertRes.durationMs = chrono::duration<double, milli>(end - start).count();

  start = chrono::high_resolution_clock::now();
  for (size_t i = 0; i < n; ++i) {
    table.find(keys[i]);
    findRes.totalOps += table.getCount();
  }
  end = chrono::high_resolution_clock::now();
  findRes.durationMs = chrono::duration<double, milli>(end - start).count();

  start = chrono::high_resolution_clock::now();
  for (size_t i = 0; i < n; ++i) {
    table.remove(keys[i]);
    removeRes.totalOps += table.getCount();
  }
  end = chrono::high_resolution_clock::now();
  removeRes.durationMs = chrono::duration<double, milli>(end - start).count();

  cout << left << setw(20) << tableName << " | Insert: " << setw(10)
       << insertRes.totalOps << " ops / " << setw(8) << fixed << setprecision(2)
       << insertRes.durationMs << " ms"
       << " | Find: " << setw(10) << findRes.totalOps << " ops / " << setw(8)
       << findRes.durationMs << " ms"
       << " | Remove: " << setw(10) << removeRes.totalOps << " ops / "
       << setw(8) << removeRes.durationMs << " ms" << endl;
}

int main() {
  vector<int> testSizes = {100, 500, 1000, 2500, 5000};

  cout << "Starting Experiments..." << endl;
  cout << string(110, '-') << endl;

  for (int size : testSizes) {
    cout << "\n>>> DATA VOLUME: " << size << " elements" << endl;

    vector<string> keys;
    vector<Polinom> values;
    for (int i = 0; i < size; ++i) {
      keys.push_back(generateRandomKey(10) + to_string(i));
      values.push_back(generateRandomPolinom());
    }

    runExperiment<UnorderedTable<Polinom>>("UnorderedTable", keys, values);
    runExperiment<AVLOrderedTable<Polinom>>("AVLTable", keys, values);

    struct HashWrapper : public HashOrderedTable<Polinom> {
      HashWrapper() : HashOrderedTable<Polinom>(1000) {}
    };
    runExperiment<HashWrapper>("HashTable (1000)", keys, values);

    cout << string(110, '-') << endl;
  }

  return 0;
}
