#include <iostream>
#include <string>
#include <limits>
#include "polynomial.h"
#include "UnorderedTable.h"
#include "OrderedTable.h"
#include "AVLTreeTable.h"
#include "HashTable.h"
#include "Logs.h"

using namespace std;

UnorderedTable<Polynom> unordTab;
OrderedTable<Polynom> ordTab;
AVLTreeTable<Polynom> avlTab;
HashTable<Polynom> hashTab(101);
Logger logger("lab_log.txt");

void ResetAllStats() {
    unordTab.ResetStats();
    ordTab.ResetStats();
    avlTab.ResetStats();
    hashTab.ResetStats();
}

void SyncInsert(const string& key, const Polynom& p) {
    ResetAllStats();

    unordTab.Insert(key, p);
    ordTab.Insert(key, p);
    avlTab.Insert(key, p);
    hashTab.Insert(key, p);

    logger.LogOperation("INSERT", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());
}

Polynom* SyncFind(const string& key) {
    ResetAllStats();

    Polynom* res = unordTab.Find(key);
    ordTab.Find(key);
    avlTab.Find(key);
    hashTab.Find(key);

    logger.LogOperation("FIND", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());

    return res;
}

void SyncRemove(const string& key) {
    ResetAllStats();

    bool r1 = unordTab.Remove(key);
    bool r2 = ordTab.Remove(key);
    bool r3 = avlTab.Remove(key);
    bool r4 = hashTab.Remove(key);

    if (r1) {
        logger.LogOperation("REMOVE", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());
        cout << "[System] Key '" << key << "' removed from all tables.\n";
    }
    else {
        cout << "[Error] Key not found.\n";
    }
}

void PolynomialArithmetic() {
    string key1, key2, keyRes;
    cout << "Enter key of the first polynomial: "; cin >> key1;
    cout << "Enter key of the second polynomial: "; cin >> key2;

    Polynom* p1 = unordTab.Find(key1);
    Polynom* p2 = unordTab.Find(key2);

    if (!p1 || !p2) {
        cout << "[Error] One or both polynomials not found!\n";
        return;
    }

    cout << "First: "; p1->print(); cout << endl;
    cout << "Second: "; p2->print(); cout << endl;
    cout << "Choose operation: 1.Add  2.Sub  3.Mul: ";
    int op;
    while (!(std::cin >> op)) {
        std::cout << "[Error] Input error. Enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    Polynom result;
    if (op == 1) result = *p1 + *p2;
    else if (op == 2) result = *p1 - *p2;
    else if (op == 3) result = (*p1) * (*p2);

    cout << "Result: "; result.print(); cout << endl;
    cout << "Enter key to save the result: "; cin >> keyRes;

    SyncInsert(keyRes, result);
    cout << "[Success] Result saved in all tables.\n";
}

int main() {
    int choice;
    string key;

    while (true) {
        cout << "\n========= TABLE CONTROLLER =========\n";
        cout << "1. Insert Polynomial\n";
        cout << "2. Find Polynomial\n";
        cout << "3. Remove Polynomial\n";
        cout << "4. Polynomial Arithmetic\n";
        cout << "5. Exit and Save Log\n";
        cout << "====================================\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5) break;

        switch (choice) {
        case 1: {
            cout << "Enter unique key (for example 'A' or 'Poly1'): ";
            cin >> key;

            Polynom p;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            p.read();

            SyncInsert(key, p);
            cout << "[System] Inserted successfully.\n";
            break;
        }
        case 2: {
            cout << "Enter key to find: ";
            cin >> key;

            Polynom* result = SyncFind(key);
            if (result) {
                cout << "[Found] " << key << " = ";
                result->print();
                cout << endl;
            }
            else {
                cout << "[Error] Key '" << key << "' not found.\n";
            }
            break;
        }
        case 3: {
            cout << "Enter key to remove: ";
            cin >> key;
            SyncRemove(key);
            break;
        }
        case 4: {
            PolynomialArithmetic();
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    cout << "Exiting. Stats saved to 'lab_log.txt'\n";
    return 0;
}