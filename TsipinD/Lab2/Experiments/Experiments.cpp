#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <random>

#include "../Lab2/UnorderedTable.h"
#include "../Lab2/OrderedTable.h"
#include "../Lab2/AVLTreeTable.h"
#include "../Lab2/HashTable.h"
#include "../Lab2/polynomial.h"

using namespace std;

Polynom GenerateRandomPolynom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<> coeff_dist(1, 100);
    uniform_int_distribution<> power_dist(0, 999);
    Polynom p;
    for (int i = 0; i < 3; ++i) p.push_back(coeff_dist(gen), power_dist(gen));
    return p;
}

string GenerateRandomKey(int length = 10) {
    std::random_device rd;
    std::mt19937 gen(rd());
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    uniform_int_distribution<> dist(0, (int)charset.length() - 1);
    string res;
    for (int i = 0; i < length; ++i) res += charset[dist(gen)];
    return res;
}

void PrintHeader() {
    cout << setfill('-') << setw(63) << "-" << setfill(' ') << endl;
    cout << left << setw(20) << "| Table Type"
        << " | " << setw(20) << "Total Operations"
        << " | " << setw(15) << "Time (ms)" << " |" << endl;
    cout << setfill('-') << setw(63) << "-" << setfill(' ') << endl;
}

void PrintResult(string name, OpStats s, double time) {
    cout << "| " << left << setw(18) << name
        << " | " << setw(20) << s.total
        << " | " << setw(15) << fixed << setprecision(3) << time << " |" << endl;
}


void RunExperiment(int N) {
    cout << "\n>>>>>>>>> STARTING EXPERIMENT FOR N = " << N << " ELEMENTS <<<<<<<<<\n" << endl;

    vector<string> keys;
    vector<Polynom> values;
    for (int i = 0; i < N; ++i) {
        keys.push_back(GenerateRandomKey() + "_" + to_string(i));
        values.push_back(GenerateRandomPolynom());
    }

    UnorderedTable<Polynom> unord;
    OrderedTable<Polynom> ord;
    AVLTreeTable<Polynom> avl;
    HashTable<Polynom> hash(N * 2);

    // ================= INSERT =====================
    cout << "STAGE: INSERT" << endl;
    PrintHeader();

    // unord
    auto start = chrono::high_resolution_clock::now();
    unord.ResetStats(); for (int i = 0; i < N; ++i) unord.Insert(keys[i], values[i]);
    auto end = chrono::high_resolution_clock::now();
    PrintResult("Unordered", unord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // ord
    start = chrono::high_resolution_clock::now();
    ord.ResetStats(); for (int i = 0; i < N; ++i) ord.Insert(keys[i], values[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Ordered", ord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // avl
    start = chrono::high_resolution_clock::now();
    avl.ResetStats(); for (int i = 0; i < N; ++i) avl.Insert(keys[i], values[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("AVL Tree", avl.GetStats(), chrono::duration<double, milli>(end - start).count());

    //hash
    start = chrono::high_resolution_clock::now();
    hash.ResetStats(); for (int i = 0; i < N; ++i) hash.Insert(keys[i], values[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Hash Table", hash.GetStats(), chrono::duration<double, milli>(end - start).count());


    cout << setfill('=') << setw(63) << "=" << setfill(' ') << endl;

    // ================= FIND =====================
    cout << "\nSTAGE: FIND" << endl;
    PrintHeader();

    // unord
    unord.ResetStats(); start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) unord.Find(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Unordered", unord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // ord
    ord.ResetStats(); start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) ord.Find(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Ordered", ord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // avl
    avl.ResetStats(); start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) avl.Find(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("AVL Tree", avl.GetStats(), chrono::duration<double, milli>(end - start).count());

    // hash
    hash.ResetStats(); start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) hash.Find(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Hash Table", hash.GetStats(), chrono::duration<double, milli>(end - start).count());

    cout << setfill('=') << setw(63) << "=" << setfill(' ') << endl;

    // ================= REMOVE =====================
    cout << "\nSTAGE: REMOVE" << endl;
    PrintHeader();

    // unord
    unord.ResetStats();
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) unord.Remove(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Unordered", unord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // ord
    ord.ResetStats();
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) ord.Remove(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Ordered", ord.GetStats(), chrono::duration<double, milli>(end - start).count());

    // avl
    avl.ResetStats();
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) avl.Remove(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("AVL Tree", avl.GetStats(), chrono::duration<double, milli>(end - start).count());

    // hash
    hash.ResetStats();
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) hash.Remove(keys[i]);
    end = chrono::high_resolution_clock::now();
    PrintResult("Hash Table", hash.GetStats(), chrono::duration<double, milli>(end - start).count());

    cout << setfill('=') << setw(63) << "=" << setfill(' ') << endl;
}

int main() {
    RunExperiment(10);
    RunExperiment(100);
    RunExperiment(1000);
    return 0;
}