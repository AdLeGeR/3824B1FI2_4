#include "pch.h"
#include <string>
#include <vector>
#include <random>
#include "../Lab2/UnorderedTable.h"
#include "../Lab2/OrderedTable.h"
#include "../Lab2/AVLTreeTable.h"
#include "../Lab2/HashTable.h"
#include "../Lab2/polynomial.h"


Polynom CreateRandomPolynom(int termsCount = 3) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> coeff_dist(1, 100);
    std::uniform_int_distribution<> power_dist(0, 9);

    Polynom p;
    for (int i = 0; i < termsCount; ++i) {
        p.push_back(coeff_dist(gen), power_dist(gen));
    }
    return p;
}

std::string CreateRandomKey(int length = 5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<> dist(0, charset.length() - 1);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += charset[dist(gen)];
    }
    return result;
}

// ====================== Unordered Table =================================

TEST(UnorderedTableTest, CanInsertAndFind) {
    UnorderedTable<Polynom> table;
    Polynom p = CreateRandomPolynom();
    std::string key = "TestKey";

    table.Insert(key, p);
    Polynom* found = table.Find(key);

    ASSERT_NE(found, nullptr);
    ASSERT_NE(found->poly.head, nullptr);
}

TEST(UnorderedTableTest, ReturnsNullIfNotFound) {
    UnorderedTable<Polynom> table;
    ASSERT_EQ(table.Find("NonExistent"), nullptr);
}

TEST(UnorderedTableTest, CanRemoveElement) {
    UnorderedTable<Polynom> table;
    table.Insert("Key1", CreateRandomPolynom());
    table.Insert("Key2", CreateRandomPolynom());

    ASSERT_TRUE(table.Remove("Key1"));
    ASSERT_EQ(table.Find("Key1"), nullptr);
    ASSERT_NE(table.Find("Key2"), nullptr);
}

TEST(UnorderedTableTest, RandomDataTest) {
    UnorderedTable<Polynom> table;
    std::vector<std::string> keys;
    int count = 100;

    for (int i = 0; i < count; ++i) {
        std::string k = CreateRandomKey() + std::to_string(i);
        keys.push_back(k);
        table.Insert(k, CreateRandomPolynom());
    }

    for (auto& k : keys) {
        ASSERT_NE(table.Find(k), nullptr);
    }
}

TEST(UnorderedTableTest, UnordStatsCounting) {
    UnorderedTable<Polynom> table;

    table.ResetStats();
    table.Insert("Key1", CreateRandomPolynom());
    OpStats s_ins1 = table.GetStats();

    EXPECT_GT(s_ins1.total, 0);

    table.ResetStats();
    table.Insert("Key2", CreateRandomPolynom());
    OpStats s_ins2 = table.GetStats();

    EXPECT_GT(s_ins2.total, s_ins1.total);

    table.Insert("Key3", CreateRandomPolynom());
    table.ResetStats();
    table.Find("Key3");

    OpStats s_find = table.GetStats();
    // Key1, Key2, Key3
    // 1 + 3*4 + 2
    EXPECT_EQ(s_find.total, 15);

    table.ResetStats();
    table.Remove("Key1");

    OpStats s_rem = table.GetStats();
    EXPECT_EQ(s_rem.total, 10); //2 + 4 + 3 + 1
}

// ====================== Ordered Table =================================

TEST(OrderedTableTest, MaintainsOrderAndFinds) {
    OrderedTable<Polynom> table;
    table.Insert("C", CreateRandomPolynom());
    table.Insert("A", CreateRandomPolynom());
    table.Insert("B", CreateRandomPolynom());

    ASSERT_NE(table.Find("A"), nullptr);
    ASSERT_NE(table.Find("B"), nullptr);
    ASSERT_NE(table.Find("C"), nullptr);
}

TEST(OrderedTableTest, UpdateExistingKey) {
    OrderedTable<Polynom> table;
    Polynom p1, p2;
    p1.push_back(10, 1);
    p2.push_back(20, 2);

    table.Insert("Key", p1);
    table.Insert("Key", p2);

    Polynom* found = table.Find("Key");
    ASSERT_NE(found, nullptr);
    ASSERT_EQ(found->poly.head->power, 2);
}

TEST(OrderedTableTest, StressTestRandomData) {
    OrderedTable<Polynom> table;
    std::vector<std::string> keys;

    for (int i = 0; i < 50; ++i) {
        std::string k = CreateRandomKey();
        keys.push_back(k);
        table.Insert(k, CreateRandomPolynom());
    }

    for (auto& k : keys) {
        EXPECT_NE(table.Find(k), nullptr);
    }
}

TEST(OrderedTableTest, OrdStatsCounting) {
    OrderedTable<Polynom> table;
    std::vector<std::string> keys;

    for (int i = 0; i < 50; ++i) {
        std::string k = CreateRandomKey(10);
        keys.push_back(k);
        table.Insert(k, CreateRandomPolynom());
    }

    table.ResetStats();
    std::string searchKey = keys[10];
    table.Find(searchKey);

    OpStats s = table.GetStats();
    EXPECT_GT(s.total, 10);
    EXPECT_LT(s.total, 150);
}

TEST(OrderedTableTest, OrdStatsCounting2) {
    OrderedTable<Polynom> table;

    table.Insert("A", CreateRandomPolynom());
    table.Insert("B", CreateRandomPolynom());
    table.Insert("C", CreateRandomPolynom());

    table.ResetStats();
    table.Find("A");

    OpStats s = table.GetStats();
    EXPECT_GT(s.total, 10);
}

TEST(OrderedTableTest, OrdStatsCountingRandom) {
    OrderedTable<Polynom> table;
    std::vector<std::string> keys;

    for (int i = 0; i < 50; ++i) {
        std::string k = CreateRandomKey(10);
        keys.push_back(k);
        table.Insert(k, CreateRandomPolynom());
    }

    table.ResetStats();
    std::string searchKey = keys[10];
    table.Find(searchKey);

    OpStats s = table.GetStats();
    EXPECT_GT(s.total, 10);
    EXPECT_LT(s.total, 120);
}

// ====================== AVL Table =================================

TEST(AVLTreeTest, BasicOperations) {
    AVLTreeTable<Polynom> table;
    table.Insert("B", CreateRandomPolynom());
    table.Insert("A", CreateRandomPolynom());
    table.Insert("C", CreateRandomPolynom());

    ASSERT_NE(table.Find("A"), nullptr);
    ASSERT_NE(table.Find("B"), nullptr);
    ASSERT_NE(table.Find("C"), nullptr);
    ASSERT_EQ(table.Find("D"), nullptr);
}

TEST(AVLTreeTest, BalancingAfterSequentialInsert) {
    AVLTreeTable<Polynom> table;

    table.Insert("1", CreateRandomPolynom());
    table.Insert("2", CreateRandomPolynom());
    table.Insert("3", CreateRandomPolynom());
    table.Insert("4", CreateRandomPolynom());
    table.Insert("5", CreateRandomPolynom());
    table.Insert("6", CreateRandomPolynom());
    table.Insert("7", CreateRandomPolynom());

    int height = table.GetTotalHeight();
    EXPECT_EQ(height, 3);
}

TEST(AVLTreeTest, BalancingAfterRemove) {
    AVLTreeTable<Polynom> table;


    table.Insert("10", CreateRandomPolynom());
    table.Insert("05", CreateRandomPolynom());
    table.Insert("15", CreateRandomPolynom());
    table.Insert("03", CreateRandomPolynom()); // левая ветка длиннее

    // создаем перекос влево
    table.Remove("15");

    int height = table.GetTotalHeight();
    // дерево из 3 элементов должно иметь высоту 2
    EXPECT_EQ(height, 2);
}


TEST(AVLTreeTest, UpdateValue) {
    AVLTreeTable<Polynom> table;
    Polynom p1; p1.push_back(1, 1);
    Polynom p2; p2.push_back(2, 2);

    table.Insert("Key", p1);
    table.Insert("Key", p2); 

    Polynom* found = table.Find("Key");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->poly.head->power, 2);
}

TEST(AVLTreeTest, RandomBalancingTest) {
    AVLTreeTable<Polynom> table;
    const int n = 500;

    for (int i = 0; i < n; ++i) {
        table.Insert(CreateRandomKey(10), CreateRandomPolynom());
    }

    // log2(502) ~ 9. 9*1.144 = 13
    EXPECT_LE(table.GetTotalHeight(), 13);
}

TEST(AVLTreeTest, RightLeftRotation) {
    AVLTreeTable<Polynom> table;

    table.Insert("10", CreateRandomPolynom());
    table.Insert("20", CreateRandomPolynom());
    table.Insert("15", CreateRandomPolynom()); 

    EXPECT_EQ(table.GetTotalHeight(), 2);
    EXPECT_EQ(table.GetRootKey(), "15");
}

TEST(AVLTreeTest, RemoveRoot) {
    AVLTreeTable<Polynom> table;
    table.Insert("20", CreateRandomPolynom()); // корень
    table.Insert("10", CreateRandomPolynom());
    table.Insert("30", CreateRandomPolynom());

    ASSERT_TRUE(table.Remove("20"));

    EXPECT_EQ(table.GetTotalHeight(), 2);
    ASSERT_NE(table.Find("10"), nullptr);
    ASSERT_NE(table.Find("30"), nullptr);
    EXPECT_EQ(table.Find("20"), nullptr);
}

TEST(AVLTreeTest, AVLOrdStatsCountingRandom) {
    AVLTreeTable<Polynom> table;

    for (int i = 0; i < 100; ++i) {
        table.Insert("Key" + std::to_string(i), CreateRandomPolynom());
    }

    table.ResetStats();
    table.Find("Key50");

    OpStats s = table.GetStats();

    EXPECT_GT(s.total, 10);
    EXPECT_LT(s.total, 120);
}

// ====================== Hash Table =================================

TEST(HashTableTest, BasicInsertAndFind) {
    HashTable<Polynom> table;
    Polynom p1; p1.push_back(1., 1);

    table.Insert("A", p1);
    Polynom* found = table.Find("A");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->poly.head->coeff, 1.);

    Polynom p2; p2.push_back(2., 2);
    table.Insert("A", p2);
    found = table.Find("A");
    EXPECT_EQ(found->poly.head->coeff, 2.);
}

TEST(HashTableTest, CollisionTest) {

    HashTable<Polynom> table(2);

    std::vector<std::string> keys = { "A", "B", "C", "D", "E" };
    for (auto& k : keys) {
        table.Insert(k, CreateRandomPolynom());
    }

    for (auto& k : keys) {
        EXPECT_NE(table.Find(k), nullptr) << "Failed for key: " << k;
    }
}

TEST(HashTableTest, RandomCollisionTest) {
    HashTable<Polynom> table(50);
    std::vector<std::string> keys;

    for (int i = 0; i < 200; ++i) {
        std::string k = CreateRandomKey(6);
        keys.push_back(k);
        table.Insert(k, CreateRandomPolynom());
    }

    for (auto& k : keys) {
        EXPECT_NE(table.Find(k), nullptr);
    }
}

TEST(HashTableTest, DeleteFromChain) {
    HashTable<Polynom> table(1);

    table.Insert("Key1", CreateRandomPolynom());
    table.Insert("Key2", CreateRandomPolynom());
    table.Insert("Key3", CreateRandomPolynom());

    EXPECT_TRUE(table.Remove("Key2"));

    EXPECT_NE(table.Find("Key1"), nullptr);
    EXPECT_EQ(table.Find("Key2"), nullptr);
    EXPECT_NE(table.Find("Key3"), nullptr);
}


TEST(HashTableTest, SearchNonExistent) {
    HashTable<Polynom> table(101);
    EXPECT_EQ(table.Find("NoName"), nullptr);
    EXPECT_FALSE(table.Remove("NoName"));
}


TEST(HashTableTest, DetailedStats) {
    HashTable<Polynom> table(101);
    table.ResetStats();

    table.Insert("A", CreateRandomPolynom());
    OpStats s1 = table.GetStats();

    EXPECT_GT(s1.total, 20);

    table.ResetStats();

    table.Find("A");
    OpStats s2 = table.GetStats();
    EXPECT_GT(s2.total, 20);
}

TEST(HashTableTest, LargeDataTest) {
    HashTable<Polynom> table(50);
    const int count = 200;

    for (int i = 0; i < count; ++i) {
        table.Insert("Key" + std::to_string(i), CreateRandomPolynom());
    }

    for (int i = 0; i < count; ++i) {
        ASSERT_NE(table.Find("Key" + std::to_string(i)), nullptr);
    }
}