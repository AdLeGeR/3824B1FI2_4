#include "../lib_table/table_vector.h"
#include <gtest/gtest.h>

TEST(TableVectorTest, InsertFind) {
  TableVector<int> table;
  table.insert("1", 100);
  table.insert("2", 200);
  table.insert("3", 300);

  int *val = table.find("2");
  EXPECT_EQ(*val, 200);

  val = table.find("1");
  EXPECT_EQ(*val, 100);
}

TEST(TableVectorTest, UpdateKey) {
  TableVector<int> table;

  table.insert("1", 100);
  table.insert("1", 200);

  int *val = table.find("1");
  EXPECT_EQ(*val, 200);
}

TEST(TableVectorTest, FindExistent) {
  TableVector<int> table;

  table.insert("1", 100);

  int *val = table.find("2");
  EXPECT_EQ(val, nullptr);
}

TEST(TableVectorTest, RemoveElement) {
  TableVector<int> table;
  table.insert("1", 100);
  table.insert("2", 200);
  table.remove("1");

  int *val = table.find("1");
  EXPECT_EQ(val, nullptr);

  val = table.find("2");
  EXPECT_EQ(*val, 200);
}

TEST(TableVectorTest, RemoveExistent) {
  TableVector<int> table;

  table.insert("key1", 100);
  table.remove("key2");

  int *val = table.find("key1");
  EXPECT_EQ(*val, 100);
}

TEST(TableVectorTest, EmptyTable) {
  TableVector<int> table;
  table.remove("anything");
  EXPECT_EQ(table.find("anything"), nullptr);
}

TEST(TableVectorTest, Elements) {
  TableVector<int> table;
  const int count = 50;

  for (int i = 0; i < count; i++) {
    table.insert("key_" + std::to_string(i), i);
  }

  for (int i = 0; i < count; i++) {
    int *val = table.find("key_" + std::to_string(i));
    EXPECT_EQ(*val, i);
  }
}

TEST(TableVectorTest, ConstructorWithReserve) {
  TableVector<int> table(100);

  for (int i = 0; i < 50; i++) {
    table.insert("key_" + std::to_string(i), i);
  }

  EXPECT_NE(table.find("key_0"), nullptr);
  EXPECT_NE(table.find("key_49"), nullptr);
}


TEST(TableVectorTest, UpdateSameKeyMultipleTimes) {
    TableVector<int> table;

    table.insert("key", 1);
    table.insert("key", 2);
    table.insert("key", 3);

    int* val = table.find("key");
    EXPECT_EQ(*val, 3);
    EXPECT_NE(val, nullptr);
}

TEST(TableVectorTest, EmptyStringKey) {
    TableVector<int> table;

    table.insert("", 1);
    int* val = table.find("");
    EXPECT_EQ(*val, 1);

    table.insert("", 2);
    val = table.find("");
    EXPECT_EQ(*val, 2);

    table.remove("");
    val = table.find("");
    EXPECT_EQ(val, nullptr);
}

TEST(TableVectorTest, RemoveSameKeyMultipleTimes) {
    TableVector<int> table;

    table.insert("key", 100);
    table.remove("key");

    EXPECT_NO_THROW(table.remove("key"));
    EXPECT_EQ(table.find("key"), nullptr);
}

TEST(TableVectorTest, RemoveNonExistentFromFilledTable) {
    TableVector<int> table;
    EXPECT_NO_THROW(table.remove("nonexistent"));
}
