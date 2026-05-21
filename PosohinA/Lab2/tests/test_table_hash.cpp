#include "../lib_table/table_hash.h"
#include <gtest/gtest.h>

TEST(TableHashTest, InsertFind1) {
  TableHash<int> table;

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

TEST(TableHashTest, UpdateKey1) {
  TableHash<int> table;

  table.insert("key1", 100);
  table.insert("key1", 999);

  int *val = table.find("key1");
  EXPECT_EQ(*val, 999);
}

TEST(TableHashTest, FindNonExis1) {
  TableHash<int> table;

  table.insert("key1", 100);
  table.insert("key2", 200);

  int *val = table.find("key3");
  EXPECT_EQ(val, nullptr);
}

TEST(TableHashTest, Remove1) {
  TableHash<int> table;
  table.insert("key1", 100);
  table.insert("key2", 200);
  table.insert("key3", 300);

  table.remove("key2");

  EXPECT_EQ(table.find("key2"), nullptr);
}

TEST(TableHashTest, Remove2) {
  TableHash<int> table;
  table.insert("key1", 100);
  table.remove("key1");

  EXPECT_EQ(table.find("key1"), nullptr);

  table.insert("key1", 200);
  int *val = table.find("key1");

  EXPECT_EQ(*val, 200);
}

TEST(TableHashTest, Remove3) {
  TableHash<int> table;
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

TEST(TableHashTest, Empty1) {
  TableHash<int> table;

  EXPECT_EQ(table.find("anything"), nullptr);
  table.remove("anything");
}

TEST(TableHashTest, Rehash1) {
  TableHash<int> table(4);

  for (int i = 0; i < 500; i++) {
    table.insert("key_" + std::to_string(i), i);
  }

  for (int i = 0; i < 500; i++) {
    int *val = table.find("key_" + std::to_string(i));
    EXPECT_EQ(*val, i);
  }
}

TEST(TableHashTest, KeyLengths1) {
  TableHash<int> table;

  table.insert("a", 1);
  table.insert("aa", 2);
  table.insert("aaa", 3);
  table.insert("aaaa", 4);

  EXPECT_EQ(*table.find("a"), 1);
  EXPECT_EQ(*table.find("aa"), 2);
  EXPECT_EQ(*table.find("aaa"), 3);
  EXPECT_EQ(*table.find("aaaa"), 4);
}

TEST(TableHashTest, EmptyKey1) {
  TableHash<int> table;

  table.insert("", 100);
  table.insert("", 200);

  int *val = table.find("");
  EXPECT_EQ(*val, 200);
}

