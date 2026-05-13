#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
//#include <iomanip>
#include "polinomial.h"
#include "hash_table.h"
#include "unordered_table.h"
#include "avl_tree.h"


std::string GenerateRandomPolynomial() {
    std::string poly_str = "";
    for (int j = 0; j < 3; ++j) {
        int coeff = rand() % 100 + 1;
        int degree = rand() % 10;
        poly_str += std::to_string(coeff) + " " + std::to_string(degree) + " ";
    }
    return poly_str;
} 

// Polinomial creation
Polinomial CreatePolynomial1() {
    return Polinomial("2 0 3 1 4 2"); 
}

Polinomial CreatePolynomial2() {
    return Polinomial("1 0 2 1 3 2");
}

Polinomial CreatePolynomial3() {
    return Polinomial("5 0 5 1 5 2");
}

// HashTable<Polinomial>
TEST(HashTablePolinomialTest, EmplaceAndFind) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);

    Polinomial* result1 = table.Find("key1");
    Polinomial* result2 = table.Find("key2");
    Polinomial* result3 = table.Find("key3");  // non-existing key

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(HashTablePolinomialTest, EmplaceReplace) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key1", p2);

    Polinomial* result = table.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(HashTablePolinomialTest, Erase) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);

    ASSERT_NE(table.Find("key1"), nullptr);

    table.Erase("key1");

    EXPECT_EQ(table.Find("key1"), nullptr);
}

TEST(HashTablePolinomialTest, MultipleOperations) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);
    table.EmplaceBack("key3", p3);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key2"), p2);
    EXPECT_EQ(*table.Find("key3"), p3);

    table.Erase("key2");
    EXPECT_EQ(table.Find("key2"), nullptr);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key3"), p3);
}

TEST(HashTablePolinomialTest, Statistics) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);
    table.Find("key1");
    table.Erase("key1");

    int operations = table.GetOperationNumber();
    EXPECT_GT(operations, 0);

    table.Reset();
    EXPECT_EQ(table.GetOperationNumber(), 0);
}

// UnorderedTable<Polinomial>
TEST(UnorderedTablePolinomialTest, EmplaceAndFind) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);

    Polinomial* result1 = table.Find("key1");
    Polinomial* result2 = table.Find("key2");
    Polinomial* result3 = table.Find("key3");

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(UnorderedTablePolinomialTest, EmplaceReplace) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key1", p2);

    Polinomial* result = table.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(UnorderedTablePolinomialTest, Erase) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);

    ASSERT_NE(table.Find("key1"), nullptr);

    table.Erase("key1");

    EXPECT_EQ(table.Find("key1"), nullptr);
}

TEST(UnorderedTablePolinomialTest, MultipleOperations) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);
    table.EmplaceBack("key3", p3);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key2"), p2);
    EXPECT_EQ(*table.Find("key3"), p3);

    table.Erase("key2");
    EXPECT_EQ(table.Find("key2"), nullptr);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key3"), p3);
}

TEST(UnorderedTablePolinomialTest, Statistics) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);
    table.Find("key1");
    table.Erase("key1");

    int operations = table.GetOperationNumber();
    EXPECT_GT(operations, 0);

    table.Reset();
    EXPECT_EQ(table.GetOperationNumber(), 0);
}

// AvlTree<Polinomial>
TEST(AvlTreePolinomialTest, EmplaceAndFind) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key2", p2);

    Polinomial* result1 = tree.Find("key1");
    Polinomial* result2 = tree.Find("key2");
    Polinomial* result3 = tree.Find("key3");

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(AvlTreePolinomialTest, EmplaceReplace) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key1", p2);

    Polinomial* result = tree.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(AvlTreePolinomialTest, Erase) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    tree.EmplaceBack("key1", p1);

    ASSERT_NE(tree.Find("key1"), nullptr);

    tree.Erase("key1");

    EXPECT_EQ(tree.Find("key1"), nullptr);
}

TEST(AvlTreePolinomialTest, MultipleOperations) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key2", p2);
    tree.EmplaceBack("key3", p3);

    EXPECT_EQ(*tree.Find("key1"), p1);
    EXPECT_EQ(*tree.Find("key2"), p2);
    EXPECT_EQ(*tree.Find("key3"), p3);

    tree.Erase("key2");
    EXPECT_EQ(tree.Find("key2"), nullptr);

    EXPECT_EQ(*tree.Find("key1"), p1);
    EXPECT_EQ(*tree.Find("key3"), p3);
}

TEST(AvlTreePolinomialTest, Statistics) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    tree.EmplaceBack("key1", p1);
    tree.Find("key1");
    tree.Erase("key1");

    int operations = tree.GetOperationNumber();
    EXPECT_GT(operations, 0);

    tree.Reset();
    EXPECT_EQ(tree.GetOperationNumber(), 0);
}

TEST(AvlTreePolinomialTest, BalanceCheck) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    tree.EmplaceBack("key5", p1);
    tree.EmplaceBack("key3", p2);
    tree.EmplaceBack("key7", p3);
    tree.EmplaceBack("key2", p1);
    tree.EmplaceBack("key4", p2);
    tree.EmplaceBack("key6", p3);
    tree.EmplaceBack("key8", p1);

    EXPECT_NE(tree.Find("key5"), nullptr);
    EXPECT_NE(tree.Find("key3"), nullptr);
    EXPECT_NE(tree.Find("key7"), nullptr);
    EXPECT_NE(tree.Find("key2"), nullptr);
    EXPECT_NE(tree.Find("key4"), nullptr);
    EXPECT_NE(tree.Find("key6"), nullptr);
    EXPECT_NE(tree.Find("key8"), nullptr);
}

// Specific tests
TEST(HashTablePolinomialTest, EmptyTable) {
    HashTable<Polinomial> table(10);

    EXPECT_EQ(table.Find("any_key"), nullptr);
    EXPECT_NO_THROW(table.Erase("any_key"));
}

TEST(UnorderedTablePolinomialTest, EmptyTable) {
    UnorderedTable<Polinomial> table;

    EXPECT_EQ(table.Find("any_key"), nullptr);
    EXPECT_NO_THROW(table.Erase("any_key"));
}

TEST(AvlTreePolinomialTest, EmptyTree) {
    AvlTree<Polinomial> tree;

    EXPECT_EQ(tree.Find("any_key"), nullptr);
    EXPECT_NO_THROW(tree.Erase("any_key"));
}

TEST(HashTablePolinomialTest, CopyConstructor) {
    HashTable<Polinomial> table1(10);
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    HashTable<Polinomial> table2(table1);

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, CopyConstructor) {
    UnorderedTable<Polinomial> table1;
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    UnorderedTable<Polinomial> table2(table1);

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AvlTreePolinomialTest, CopyConstructor) {
    AvlTree<Polinomial> tree1;
    Polinomial p1 = CreatePolynomial1();
    tree1.EmplaceBack("key1", p1);

    AvlTree<Polinomial> tree2(tree1);

    Polinomial* result = tree2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(HashTablePolinomialTest, AssignmentOperator) {
    HashTable<Polinomial> table1(10);
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    HashTable<Polinomial> table2(10);
    table2 = table1;

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, AssignmentOperator) {
    UnorderedTable<Polinomial> table1;
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    UnorderedTable<Polinomial> table2;
    table2 = table1;

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AvlTreePolinomialTest, AssignmentOperator) {
    AvlTree<Polinomial> tree1;
    Polinomial p1 = CreatePolynomial1();
    tree1.EmplaceBack("key1", p1);

    AvlTree<Polinomial> tree2;
    tree2 = tree1;

    Polinomial* result = tree2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

//Experiments
//  HashTable: 100, 1000, 10000 elements
TEST(HashTableFullTest, 100Elements) {

    HashTable<Polinomial> table(10000);
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nHashTable (100 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms" << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 100);
}

TEST(HashTableFullTest, 1000Elements) {
    HashTable<Polinomial> table(10000);
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nHashTable (1000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms "<< Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms" <<Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 1000);
}

TEST(HashTableFullTest, 10000Elements) {
    HashTable<Polinomial> table(10000);
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nHashTable (10000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations " << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 10000);
}

// UnorderedTable: 100, 1000, 10000 elements

TEST(UnorderedTableFullTest, 100Elements) {
    UnorderedTable<Polinomial> table;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2; 
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nUnorderedTable (100 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms "<< Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms "<< Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 100);
}

TEST(UnorderedTableFullTest, 1000Elements) {
    UnorderedTable<Polinomial> table;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nUnorderedTable (1000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 <<  " Opearations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 1000);
}

TEST(UnorderedTableFullTest, 10000Elements) {
    UnorderedTable<Polinomial> table;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        table.EmplaceBack(key, p);
    }
    int Op1 = table.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (table.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = table.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.Erase(key);
    }
    int Op3 = table.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nUnorderedTable (10000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations"<< std::endl;

    EXPECT_EQ(found, 10000);
}

// AvlTree: 100, 1000, 10000 elements

TEST(AvlTreeFullTest, 100Elements) {
    AvlTree<Polinomial> tree;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        tree.EmplaceBack(key, p);
    }
    int Op1 = tree.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (tree.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = tree.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        tree.Erase(key);
    }
    int Op3 = tree.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nAvlTree (100 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 100);
}

TEST(AvlTreeFullTest, 1000Elements) {
    AvlTree<Polinomial> tree;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        tree.EmplaceBack(key, p);
    }
    int Op1 = tree.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (tree.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = tree.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string key = "poly" + std::to_string(i);
        tree.Erase(key);
    }
    int Op3 = tree.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nAvlTree (1000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms "<< Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 1000);
}

TEST(AvlTreeFullTest, 10000Elements) {
    AvlTree<Polinomial> tree;
    srand(time(nullptr));

    auto start_insert = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        std::string poly_str = GenerateRandomPolynomial();
        Polinomial p(poly_str);
        tree.EmplaceBack(key, p);
    }
    int Op1 = tree.GetOperationNumber();
    auto end_insert = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_insert - start_insert);

    auto start_search = std::chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        if (tree.Find(key) != nullptr) {
            found++;
        }
    }
    int Op2 = tree.GetOperationNumber() - Op1;
    auto end_search = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_search - start_search);

    auto start_erase = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        std::string key = "poly" + std::to_string(i);
        tree.Erase(key);
    }
    int Op3 = tree.GetOperationNumber() - Op1 - Op2;
    auto end_erase = std::chrono::high_resolution_clock::now();
    auto erase_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_erase - start_erase);

    std::cout << "\nAvlTree (10000 elements):" << std::endl;
    std::cout << "  Insert: " << insert_time.count() << " ms " << Op1 << " Operations" << std::endl;
    std::cout << "  Search: " << search_time.count() << " ms " << Op2 << " Operations" << std::endl;
    std::cout << "  Erase:  " << erase_time.count() << " ms " << Op3 << " Operations" << std::endl;

    EXPECT_EQ(found, 10000);
}