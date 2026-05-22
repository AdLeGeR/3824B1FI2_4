#include "../lib_table/table_AVL.h"
#include <gtest/gtest.h>

TEST(TableAVLTest, InsertAndFind) {
  TableAVL<int> table;

  table.insert("key1", 100);
  table.insert("key2", 200);
  table.insert("key3", 300);

  int *val = table.find("key2");
  EXPECT_EQ(*val, 200);

  val = table.find("key1");
  EXPECT_EQ(*val, 100);

  val = table.find("key3");
  EXPECT_EQ(*val, 300);
}

TEST(TableAVLTest, insert0) {
  TableAVL<int> table;

  table.insert("key1", 100);
  table.insert("key1", 999);

  int *val = table.find("key1");
  EXPECT_EQ(*val, 999);
}

TEST(TableAVLTest, Find1) {
  TableAVL<int> table;

  table.insert("key1", 100);
  table.insert("key2", 200);

  int *val = table.find("key3");
  EXPECT_EQ(val, nullptr);
}

TEST(TableAVLTest, Remove1) {
  TableAVL<int> table;

  table.insert("key3", 300);
  table.insert("key2", 200);
  table.insert("key4", 400);
  table.insert("key1", 100);

  table.remove("key3");

  EXPECT_EQ(table.find("key3"), nullptr);
}

TEST(TableAVLTest, Remove2) {
  TableAVL<int> table;

  table.insert("key2", 200);
  table.insert("key1", 100);
  table.insert("key3", 300);

  table.remove("key2");

  EXPECT_EQ(table.find("key2"), nullptr);
}

TEST(TableAVLTest, Remove3) {
  TableAVL<int> table;

  table.insert("key1", 100);
  table.remove("key2");

  int *val = table.find("key1");
  EXPECT_EQ(*val, 100);
}

TEST(TableAVLTest, EmptyTable) {
  TableAVL<int> table;

  EXPECT_EQ(table.find("anything"), nullptr);
}

TEST(TableAVLTest, SortedInsert) {
  TableAVL<int> table;

  for (int i = 0; i < 100; i++) {
    table.insert(std::to_string(i), i);
  }

  for (int i = 0; i < 100; i++) {
    int *val = table.find(std::to_string(i));
    EXPECT_EQ(*val, i);
  }
}

TEST(TableAVLTest, ReverseSorted) {
  TableAVL<int> table;

  for (int i = 50; i >= 0; i--) {
    table.insert(std::to_string(i), i);
  }

  for (int i = 0; i <= 50; i++) {
    int *val = table.find(std::to_string(i));
    EXPECT_EQ(*val, i);
  }
}

TEST(TableAVLTest, InsertSameKeyMultipleTimes) {
  TableAVL<int> table;

  table.insert("key1", 10);
  table.insert("key1", 20);

  int *val = table.find("key1");
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 20);
}

TEST(TableAVLTest, RemoveAll) {
  TableAVL<int> table;
  const int count = 20;

  for (int i = 0; i < count; i++) {
    table.insert("key_" + std::to_string(i), i);
  }

  for (int i = 0; i < count; i++) {
    table.remove("key_" + std::to_string(i));
    EXPECT_EQ(table.find("key_" + std::to_string(i)), nullptr);
  }

  EXPECT_EQ(table.find("key_0"), nullptr);
  EXPECT_EQ(table.find("key_19"), nullptr);
}

TEST(TableAVLTest, LexicoOrder) {
  TableAVL<int> table;

  table.insert("apple", 10);

  EXPECT_NE(table.find("apple"), nullptr);
}

TEST(TableAVLTest, KeyLengths) {
  TableAVL<int> table;

  table.insert("a", 1);
  table.insert("aa", 2);

  EXPECT_EQ(*table.find("a"), 1);
  EXPECT_EQ(*table.find("aa"), 2);
}

TEST(TableAVLRotationTest, SmallRightTurn) {
  TableAVL<int> tree;

  tree.insert("30", 30);
  tree.insert("20", 20);
  tree.insert("10", 10);

  auto *root = tree.getRoot();
  EXPECT_EQ(tree.getKey(root), "20");

  auto *left = tree.getLeft(root);
  EXPECT_EQ(tree.getKey(left), "10");
}

TEST(TableAVLRotationTest, SmallLeftTurn) {
  TableAVL<int> tree;

  tree.insert("10", 10);
  tree.insert("20", 20);
  tree.insert("30", 30);

  auto *root = tree.getRoot();
  EXPECT_EQ(tree.getKey(root), "20");

  auto *left = tree.getLeft(root);
  EXPECT_EQ(tree.getKey(left), "10");

  auto *right = tree.getRight(root);
  EXPECT_EQ(tree.getKey(right), "30");
}

TEST(TableAVLRotationTest, BigRightTurn) {
  TableAVL<int> tree;

  tree.insert("30", 30);
  tree.insert("10", 10);
  tree.insert("20", 20);

  auto *root = tree.getRoot();
  EXPECT_EQ(tree.getKey(root), "20");

  auto *left = tree.getLeft(root);
  EXPECT_EQ(tree.getKey(left), "10");

  auto *right = tree.getRight(root);
  EXPECT_EQ(tree.getKey(right), "30");
}

TEST(TableAVLRotationTest, BigLeftTurn) {
  TableAVL<int> tree;

  tree.insert("10", 10);
  tree.insert("30", 30);
  tree.insert("20", 20);

  auto *root = tree.getRoot();
  EXPECT_EQ(tree.getKey(root), "20");

  auto *left = tree.getLeft(root);
  EXPECT_EQ(tree.getKey(left), "10");

  auto *right = tree.getRight(root);
  EXPECT_EQ(tree.getKey(right), "30");
}

TEST(TableAVLTest, RemoveFromEmptyTree) {
    TableAVL<int> table;

    testing::internal::CaptureStdout();
    table.remove("anything");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Element not found"), std::string::npos);

    table.insert("new_key", 42);
    EXPECT_EQ(*table.find("new_key"), 42);
}
