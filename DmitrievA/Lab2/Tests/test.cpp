#include "../Lab2/OrderedTable.h"
#include "../Lab2/Polinom.h"
#include "../Lab2/UnorderedTable.h"
#include "pch.h"

// Фикстура для тестов (общая настройка для разных типов таблиц)
class TableTest : public ::testing::Test {
 protected:
  Polinom p1, p2, p3;

  void SetUp() override {
    p1 = Polinom();
    p1.parseMode = Simple;
    p1 = Polinom(1.0);
    p2 = Polinom(2.0);
    p3 = Polinom(3.0);
  }
};

// --- Тесты для UnorderedTable ---

TEST_F(TableTest, UnorderedTable_InsertAndFind) {
  UnorderedTable<Polinom> table;
  table.insert("poly1", p1);
  table.insert("poly2", p2);

  ASSERT_NE(table.find("poly1"), nullptr);
  EXPECT_EQ(table.find("poly1")->evaluate(1, 1, 1), p1.evaluate(1, 1, 1));
  EXPECT_EQ(table.getSize(), 2);
}

TEST_F(TableTest, UnorderedTable_UpdateExisting) {
  UnorderedTable<Polinom> table;
  table.insert("poly1", p1);
  table.insert("poly1", p2);  // Обновление значения

  EXPECT_EQ(table.getSize(), 1);
  EXPECT_EQ(table.find("poly1")->evaluate(1, 1, 1), p2.evaluate(1, 1, 1));
}

TEST_F(TableTest, UnorderedTable_Remove) {
  UnorderedTable<Polinom> table;
  table.insert("poly1", p1);
  table.remove("poly1");

  EXPECT_EQ(table.find("poly1"), nullptr);
  EXPECT_EQ(table.getSize(), 0);
}

// --- Тесты для AVLOrderedTable ---

TEST_F(TableTest, AVLTable_InsertAndFind) {
  AVLOrderedTable<Polinom> table;
  table.insert("b", p2);
  table.insert("a", p1);
  table.insert("c", p3);

  ASSERT_NE(table.find("a"), nullptr);
  ASSERT_NE(table.find("b"), nullptr);
  ASSERT_NE(table.find("c"), nullptr);
  EXPECT_EQ(table.find("b")->evaluate(1, 1, 1), p2.evaluate(1, 1, 1));
}

TEST_F(TableTest, AVLTable_RotationLogic) {
  AVLOrderedTable<Polinom> table;
  // Вставка в порядке, вызывающем вращения (a < b < c)
  table.insert("a", p1);
  table.insert("b", p2);
  table.insert("c", p3);

  EXPECT_NE(table.find("a"), nullptr);
  EXPECT_NE(table.find("c"), nullptr);
  EXPECT_EQ(table.find("b")->evaluate(1, 1, 1), p2.evaluate(1, 1, 1));
}

TEST_F(TableTest, AVLTable_RemoveLeaf) {
  AVLOrderedTable<Polinom> table;
  table.insert("key1", p1);
  table.remove("key1");
  EXPECT_EQ(table.find("key1"), nullptr);
}

TEST_F(TableTest, AVLTable_RemoveWithChildren) {
  AVLOrderedTable<Polinom> table;
  table.insert("2", p2);
  table.insert("1", p1);
  table.insert("3", p3);

  table.remove("2");  // Удаление узла с двумя потомками
  EXPECT_EQ(table.find("2"), nullptr);
  EXPECT_NE(table.find("1"), nullptr);
  EXPECT_NE(table.find("3"), nullptr);
}

// --- Тесты для HashOrderedTable ---

TEST_F(TableTest, HashTable_InsertAndFind) {
  HashOrderedTable<Polinom> table(10);
  table.insert("my_poly", p1);

  ASSERT_NE(table.find("my_poly"), nullptr);
  EXPECT_EQ(table.find("my_poly")->evaluate(1, 1, 1), p1.evaluate(1, 1, 1));
}

TEST_F(TableTest, HashTable_CollisionHandling) {
  // Создаем таблицу малого размера, чтобы спровоцировать коллизии
  HashOrderedTable<Polinom> table(1);
  table.insert("key1", p1);
  table.insert("key2", p2);

  ASSERT_NE(table.find("key1"), nullptr);
  ASSERT_NE(table.find("key2"), nullptr);
  EXPECT_EQ(table.find("key1")->evaluate(1, 1, 1), p1.evaluate(1, 1, 1));
  EXPECT_EQ(table.find("key2")->evaluate(1, 1, 1), p2.evaluate(1, 1, 1));
}

TEST_F(TableTest, HashTable_Remove) {
  HashOrderedTable<Polinom> table(5);
  table.insert("to_delete", p1);
  table.remove("to_delete");
  EXPECT_EQ(table.find("to_delete"), nullptr);
}

// --- Интеграционный тест (сравнение результатов) ---

TEST_F(TableTest, AllTables_Consistency) {
  UnorderedTable<Polinom> ut;
  AVLOrderedTable<Polinom> at;
  HashOrderedTable<Polinom> ht;

  string key = "test_key";

  ut.insert(key, p1);
  at.insert(key, p1);
  ht.insert(key, p1);

  EXPECT_EQ(ut.find(key)->evaluate(0, 0, 0), at.find(key)->evaluate(0, 0, 0));
  EXPECT_EQ(at.find(key)->evaluate(0, 0, 0), ht.find(key)->evaluate(0, 0, 0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
