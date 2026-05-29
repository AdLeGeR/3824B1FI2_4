
#include "pch.h"
#include <random>
#include <vector>
#include <algorithm>

#include "../Lab3/QueueWithTracking.h"
#include "../Lab3/BinaryHeap.h"
#include "../Lab3/FibonacciHeap.h"

using std::mt19937;
using std::cout;


// Тесты для базовой кучи
class BinaryHeapTest : public ::testing::Test {
 protected:
  BinaryHeap<int>* heap;
  void SetUp() override {
    heap = new BinaryHeap<int>(10);
  }
  void TearDown() override {
    delete heap;
  }
};

// 1. Пограничный случай: пустая куча
TEST_F(BinaryHeapTest, EmptyHeapBehavior) {
  EXPECT_TRUE(heap->isEmpty());
  EXPECT_THROW(heap->pop(), std::runtime_error);
}

// 2. Пограничный случай: один элемент
TEST_F(BinaryHeapTest, SingleElement) {
  heap->push(42);
  EXPECT_FALSE(heap->isEmpty());
  EXPECT_EQ(heap->pop(), 42);
  EXPECT_TRUE(heap->isEmpty());
}

// 3. Проверка порядка (Min-Heap)
TEST_F(BinaryHeapTest, ExtractMinOrder) {
  heap->push(10);
  heap->push(5);
  heap->push(20);
  heap->push(1);

  EXPECT_EQ(heap->pop(), 1);
  EXPECT_EQ(heap->pop(), 5);
  EXPECT_EQ(heap->pop(), 10);
  EXPECT_EQ(heap->pop(), 20);
  EXPECT_TRUE(heap->isEmpty());
}

// 4. Пограничный случай: дубликаты
TEST_F(BinaryHeapTest, DuplicateElements) {
  heap->push(5);
  heap->push(5);
  heap->push(5);

  EXPECT_EQ(heap->pop(), 5);
  EXPECT_EQ(heap->pop(), 5);
  EXPECT_EQ(heap->pop(), 5);
  EXPECT_TRUE(heap->isEmpty());
}

// 5. Пограничный случай: вставка по возрастанию и убыванию
TEST_F(BinaryHeapTest, SortedInsertion) {
  for (int i = 0; i < 5; ++i)
    heap->push(i);  // 0 1 2 3 4
  for (int i = 0; i < 5; ++i)
    EXPECT_EQ(heap->pop(), i);

  for (int i = 5; i > 0; --i)
    heap->push(i);  // 5 4 3 2 1
  for (int i = 1; i <= 5; ++i)
    EXPECT_EQ(heap->pop(), i);
}

TEST(BinaryHeapTestRandom, RandomizedStress) {
  const int N = 2000;
  BinaryHeap<int> bh(N);
  std::vector<int> data;

  std::mt19937 gen(42);
  std::uniform_int_distribution<> dis(1, 100000);

  for (int i = 0; i < N; ++i) {
    int val = dis(gen);
    data.push_back(val);
    bh.push(val);
  }

  std::sort(data.begin(), data.end());

  for (int i = 0; i < N; ++i) {
    EXPECT_EQ(bh.pop(), data[i]);
  }
  EXPECT_TRUE(bh.isEmpty());
}

class TrackingHeapTest : public ::testing::Test {
 protected:
  BinaryHeapWithTracking<int> heap{10};
};

// 1. Тест базовой логики и порядка (Min-Heap)
TEST_F(TrackingHeapTest, MaintainsMinHeapOrder) {
  heap.push(50);
  heap.push(10);
  heap.push(30);
  heap.push(20);

  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 20);
  EXPECT_EQ(heap.pop(), 30);
  EXPECT_EQ(heap.pop(), 50);
  EXPECT_TRUE(heap.isEmpty());
}

// 2. Тест DecreaseKey: Всплытие из самого низа в самый верх
TEST_F(TrackingHeapTest, DecreaseKeyToRoot) {
  size_t id1 = heap.push(100);
  size_t id2 = heap.push(200);
  size_t id3 = heap.push(300);
  size_t id4 = heap.push(400);

  // В начале корень - 100.
  // Уменьшаем 400 (id4) до 10.
  heap.decreaseKey(id4, 10);

  // Теперь 10 должен быть корнем
  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 100);
}

// 3. Тест DecreaseKey: Элемент в середине кучи
TEST_F(TrackingHeapTest, DecreaseKeyInMiddle) {
  heap.push(10);  // Корень
  size_t id2 = heap.push(50);
  size_t id3 = heap.push(100);
  size_t id4 = heap.push(60);

  // Уменьшаем 60 (id4) до 15. Он должен стать выше 50, но ниже 10.
  heap.decreaseKey(id4, 15);

  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 15);  // id4 всплыл сюда
  EXPECT_EQ(heap.pop(), 50);
  EXPECT_EQ(heap.pop(), 100);
}

// 4. Тест переиспользования индексов (freeIndexes)
TEST_F(TrackingHeapTest, FreeIndexesReuse) {
  size_t id0 = heap.push(10);
  size_t id1 = heap.push(20);

  EXPECT_EQ(id0, 0);
  EXPECT_EQ(id1, 1);

  heap.pop();  // Удаляем 10. ID 0 освобождается.

  size_t id2 = heap.push(30);
  // Проверяем, что новый элемент занял освободившийся индекс 0
  EXPECT_EQ(id2, 0);

  heap.decreaseKey(id2, 5);
  EXPECT_EQ(heap.pop(), 5);
}

// 5. Пограничный случай: Работа с дубликатами значений
TEST_F(TrackingHeapTest, HandleDuplicates) {
  size_t id1 = heap.push(10);
  size_t id2 = heap.push(10);
  size_t id3 = heap.push(10);

  heap.decreaseKey(id3, 5);  // Только один из них станет меньше
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 10);
}

// 6. Пограничный случай: Pop до пуста и повторное заполнение
TEST_F(TrackingHeapTest, StressEmptyAndRefill) {
  for (int i = 0; i < 5; ++i)
    heap.push(i * 10);
  for (int i = 0; i < 5; ++i)
    heap.pop();

  EXPECT_TRUE(heap.isEmpty());

  // Проверяем, что после полной очистки куча работает
  size_t newId = heap.push(100);
  EXPECT_FALSE(heap.isEmpty());
  EXPECT_EQ(heap.pop(), 100);
}

// 7. Проверка целостности трекинга при перемещениях (siftDown + siftUp)
TEST_F(TrackingHeapTest, TrackingIntegrityAfterHeavyShuffling) {
  // Создаем "забор" из элементов
  std::vector<size_t> ids;
  ids.push_back(heap.push(100));  // 0
  ids.push_back(heap.push(200));  // 1
  ids.push_back(heap.push(300));  // 2
  ids.push_back(heap.push(400));  // 3
  ids.push_back(heap.push(500));  // 4

  // Резко уменьшаем последний элемент (500 -> 50)
  heap.decreaseKey(ids[4], 50);  // Теперь 50 в корне

  // Удаляем корень (50)
  // При удалении последний элемент (400) пойдет в корень и спустится (siftDown)
  EXPECT_EQ(heap.pop(), 50);

  // Теперь уменьшаем 300 (ids[2]) до 10
  heap.decreaseKey(ids[2], 10);

  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 100);
  EXPECT_EQ(heap.pop(), 200);
  EXPECT_EQ(heap.pop(), 400);
}

// 8. Пограничный случай: один элемент
TEST_F(TrackingHeapTest, SingleElementDecreaseKey) {
  size_t id = heap.push(100);
  heap.decreaseKey(id, 10);
  EXPECT_EQ(heap.pop(), 10);
  EXPECT_TRUE(heap.isEmpty());
}

// рандомизированный тест: вставляет много элементов, случайно уменьшает ключи и
// проверяет порядок извлечения
TEST(BinaryHeapTrackingTestRandom, RandomizedDecreaseKey) {
  const int N = 1000;
  BinaryHeapWithTracking<int> bh(N);
  struct Element {
    size_t id;
    int val;
  };
  std::vector<Element> elements;

  for (int i = 0; i < N; ++i) {
    int v = 10000 + i;  // высокие значения
    elements.push_back({bh.push(v), v});
  }

  // Случайно уменьшает половину элементов
  std::mt19937 gen(1337);
  for (int i = 0; i < N / 2; ++i) {
    int idx = gen() % elements.size();
    elements[idx].val -= 5000;
    bh.decreaseKey(elements[idx].id, elements[idx].val);
  }
  sort(elements.begin(), elements.end(),
       [](const Element& a, const Element& b) { return a.val < b.val; });

  // Проверяет, что извлекаются в правильном порядке
  int last = -1;
  for (int i = 0; i < N; ++i) {
    EXPECT_EQ(elements[i].val, bh.pop());
  }
}

// Тестовый класс для фибоначчиевой кучи
class FibonacciHeapTest : public ::testing::Test {
 protected:
  FibonacciHeap<int> heap;
};

// 1. Тест пустой кучи
TEST_F(FibonacciHeapTest, IsEmptyInitially) {
  EXPECT_TRUE(heap.isEmpty());
}

// 2. Тест исключения при pop из пустой кучи
TEST_F(FibonacciHeapTest, ThrowsOnPopEmpty) {
  EXPECT_THROW(heap.pop(), std::runtime_error);
}

// 3. Пограничный случай: один элемент
TEST_F(FibonacciHeapTest, SingleElementPushPop) {
  heap.push(42);
  EXPECT_FALSE(heap.isEmpty());
  EXPECT_EQ(heap.pop(), 42);
  EXPECT_TRUE(heap.isEmpty());
}

// 4. Пограничный случай: два элемента (проверка корректности minNode)
TEST_F(FibonacciHeapTest, TwoElementsMinFirst) {
  heap.push(10);
  heap.push(20);
  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 20);
}

TEST_F(FibonacciHeapTest, TwoElementsMinLast) {
  heap.push(20);
  heap.push(10);
  EXPECT_EQ(heap.pop(), 10);
  EXPECT_EQ(heap.pop(), 20);
}

// 5. Тест на дубликаты
TEST_F(FibonacciHeapTest, DuplicateValues) {
  heap.push(5);
  heap.push(5);
  heap.push(5);
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_TRUE(heap.isEmpty());
}

// 6. Сложный случай: Консолидация (вызывает compress)
// В фибоначчиевой куче консолидация происходит при pop.
// Нужно добавить достаточно элементов, чтобы сформировались деревья разных
// степеней.
TEST_F(FibonacciHeapTest, ConsolidationTest) {
  std::vector<int> values = {10, 2, 15, 3, 100, 45, 1, 70};
  for (int v : values) {
    heap.push(v);
  }

  // 1 — абсолютный минимум
  EXPECT_EQ(heap.pop(), 1);
  // После pop(1) должна произойти консолидация.
  // Проверяем, что оставшиеся элементы извлекаются в правильном порядке.
  std::sort(values.begin(), values.end());
  for (size_t i = 1; i < values.size(); ++i) {
    EXPECT_EQ(heap.pop(), values[i]);
  }
}

// 7. Пограничный случай: отрицательные числа
TEST_F(FibonacciHeapTest, NegativeNumbers) {
  heap.push(-10);
  heap.push(-5);
  heap.push(-100);
  EXPECT_EQ(heap.pop(), -100);
  EXPECT_EQ(heap.pop(), -10);
}

/*
#include <fstream>
using std::ofstream;
#include <ios>
using std::ios;*/

 //8. Стресс-тест: большое количество случайных данных
TEST_F(FibonacciHeapTest, LargeRandomData) {
  std::vector<int> data;
  std::mt19937 gen(42);
  std::uniform_int_distribution<> dis(0, 100000);

  for (int i = 0; i < 100000; ++i) {
    int val = dis(gen);
    data.push_back(val);
    heap.push(val);
  }

  std::sort(data.begin(), data.end());
  for (int expected : data) {
    EXPECT_EQ(heap.pop(), expected);
  }
  EXPECT_TRUE(heap.isEmpty());
}

// 9. Пограничный случай: последовательность push/pop
TEST_F(FibonacciHeapTest, InterleavedPushPop) {
  heap.push(10);
  heap.push(20);
  EXPECT_EQ(heap.pop(), 10);
  heap.push(5);
  heap.push(15);
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_EQ(heap.pop(), 15);
  EXPECT_EQ(heap.pop(), 20);
}

class FibonacciStressTest : public ::testing::Test {
 protected:
  FibonacciHeap<int> heap;
};

TEST_F(FibonacciStressTest, ChildrenParentPointersReset) {
  // Вставляем элементы так, чтобы после первого pop сформировалось дерево
  for (int i = 0; i < 10; ++i) {
    heap.push(i);
  }
  // Первый pop запустит консолидацию.
  EXPECT_EQ(heap.pop(), 0);

  // Теперь проверим, что мы можем извлечь все остальное.
  // Если указатели parent не обнулены или списки детей повреждены, тут будет
  // крэш.
  for (int i = 1; i < 10; ++i) {
    EXPECT_NO_THROW(heap.pop());
  }
}

// 2. Тест на корректность консолидации (то, где ломается итератор)
TEST_F(FibonacciStressTest, ConsolidationLargeScale) {
  std::vector<int> data;
  for (int i = 100; i > 0; --i) {
    data.push_back(i);
    heap.push(i);
  }

  // При каждом pop происходит перестройка.
  // Если итератор в консолидации "теряется", мы либо пропустим элементы, либо
  // зациклимся.
  std::sort(data.begin(), data.end());
  for (int val : data) {
    EXPECT_EQ(heap.pop(), val);
  }
}

// 3. Тест на вставку и удаление вперемешку (динамика)
TEST_F(FibonacciStressTest, InterleavedOperations) {
  std::multiset<int> reference;
  std::mt19937 gen(123);
  std::uniform_int_distribution<> dis(1, 1000);

  for (int i = 0; i < 200; ++i) {
    int val = dis(gen);
    heap.push(val);
    reference.insert(val);

    if (i % 3 == 0) {
      int h_min = heap.pop();
      int r_min = *reference.begin();
      EXPECT_EQ(h_min, r_min);
      reference.erase(reference.begin());
    }
  }
}

// 4. Пограничный случай: очень много элементов (настоящий стресс-тест)
TEST_F(FibonacciStressTest, HeavyStress) {
  const int N = 5000;
  for (int i = 0; i < N; ++i) {
    heap.push(i);
  }
  for (int i = 0; i < N; ++i) {
    ASSERT_EQ(heap.pop(), i) << "Failed at index " << i;
  }
  EXPECT_TRUE(heap.isEmpty());
}

// 5. Тест на специфическую ошибку mergeLists:
// Проверяет, не теряются ли узлы при слиянии списка детей с корнями
TEST_F(FibonacciStressTest, MergeListsIntegrity) {
  heap.push(10);
  heap.push(20);
  heap.pop();  // Теперь 20 - единственный корень

  heap.push(5);
  heap.push(15);
  heap.push(25);
  // Теперь в куче сложная структура. Еще один pop заставит списки сливаться.
  EXPECT_EQ(heap.pop(), 5);
  EXPECT_EQ(heap.pop(), 15);
  EXPECT_EQ(heap.pop(), 20);
  EXPECT_EQ(heap.pop(), 25);
}


// Тест на корректность DecreaseKey (простой случай)
TEST(FibonacciTrackingTest, DecreaseKeySimple) {
  FibonacciHeapWithTracking<int> heap;
  size_t id1 = heap.push(100);
  size_t id2 = heap.push(200);
  size_t id3 = heap.push(300);

  // Уменьшаем 300 до 50. 50 должно стать новым минимумом.
  heap.decreaseKey(id3, 50);

  EXPECT_EQ(heap.pop(), 50);
  EXPECT_EQ(heap.pop(), 100);
  EXPECT_EQ(heap.pop(), 200);
}

// Тест на каскадное вырезание (Cascading Cut)
// Чтобы спровоцировать каскад, нужно пометить родителя (удалить одного
// ребенка), а затем удалить второго ребенка.
TEST(FibonacciTrackingTest, CascadingCutTest) {
  FibonacciHeapWithTracking<int> heap;

  // Создаем структуру дерева через серию push и один pop
  size_t root_id = heap.push(10);
  size_t child1_id = heap.push(100);
  size_t child2_id = heap.push(200);
  size_t child3_id = heap.push(300);

  // Вызываем консолидацию
  heap.pop();  // удалили 10, остальные объединились в дерево с корнем 100

  // Теперь уменьшаем ключи так, чтобы спровоцировать отрывание узлов
  // Это сложный сценарий, зависящий от внутренней структуры,
  // но при корректной реализации он не должен вызывать крэш.
  EXPECT_NO_THROW({
    heap.decreaseKey(child3_id, 50);
    heap.decreaseKey(child2_id, 40);
  });

  EXPECT_EQ(heap.pop(), 40);
  EXPECT_EQ(heap.pop(), 50);
}

// Тест на переиспользование индексов
TEST(FibonacciTrackingTest, IndexReuse) {
  FibonacciHeapWithTracking<int> heap;
  size_t id1 = heap.push(10);
  heap.pop();

  size_t id2 = heap.push(20);
  // Индекс id1 должен быть переиспользован, если freeIndexes работает
  EXPECT_EQ(id1, id2);
}

// БОЛЬШОЙ РАНДОМИЗИРОВАННЫЙ ТЕСТ
// Сравнение Фибоначчиевой кучи с Двоичной (с трекингом)
TEST(FibonacciTrackingTestRandom, CrossCheckWithBinaryHeap) {
  FibonacciHeapWithTracking<int> fHeap;
  BinaryHeapWithTracking<int> bHeap(10000);

  // Вектор для хранения ID для обеих куч (индексы будут совпадать,
  // так как обе используют freeIndexes логику одинаково)
  struct TrackingIds {
    size_t fId;
    size_t bId;
    int currentVal;
    bool active;
  };
  std::vector<TrackingIds> tracker;

  std::mt19937 gen(777);

  const int OPERATIONS = 5000;

  for (int i = 0; i < OPERATIONS; ++i) {
    //cout << "Operation " << i << "\n";
    int action = gen() % 100;

    if (action < 50) {  // 50% шанс PUSH
      int val = gen() % 100000;
      size_t fId = fHeap.push(val);
      size_t bId = bHeap.push(val);
      tracker.push_back({fId, bId, val, true});
    } else if (action < 80) {  // 30% шанс POP
      if (!fHeap.isEmpty()) {
        int fMin = fHeap.pop();
        int bMin = bHeap.pop();
        EXPECT_EQ(fMin, bMin) << "Value mismatch at operation " << i;
        for (int i = 0; i < tracker.size(); ++i) {
          if (tracker[i].currentVal == fMin) {
            tracker.erase(tracker.begin() + i); 
            break;
          }
        }
      }
    } else {  // 20% шанс DECREASE KEY
      // Ищем случайный активный элемент
      if (!tracker.empty()) {
        size_t tIdx = gen() % tracker.size();
        int newVal = tracker[tIdx].currentVal - (gen() % 100);

        // Чтобы избежать ошибок "New key is greater", только если реально
        // меньше
        if (newVal < tracker[tIdx].currentVal) {
            fHeap.decreaseKey(tracker[tIdx].fId, newVal);
            bHeap.decreaseKey(tracker[tIdx].bId, newVal);
            tracker[tIdx].currentVal = newVal;
        }
      }
    }
  }

  // Финальная очистка обеих куч
  while (!fHeap.isEmpty() && !bHeap.isEmpty()) {
    EXPECT_EQ(fHeap.pop(), bHeap.pop());
  }
  EXPECT_EQ(fHeap.isEmpty(), bHeap.isEmpty());
}

// Тест на правильный порядок после массовых decreaseKey
TEST(FibonacciTrackingTestRandom, OrderAfterMassiveDecrease) {
  FibonacciHeapWithTracking<int> heap;
  std::vector<size_t> ids;
  for (int i = 100; i < 200; ++i) {
    ids.push_back(heap.push(i));
  }

  // Уменьшаем все элементы в обратном порядке
  for (size_t i = 0; i < ids.size(); ++i) {
    heap.decreaseKey(ids[i], (int)(i-200));
  }

  int last = -1e9;
  while (!heap.isEmpty()) {
    int current = heap.pop();
    EXPECT_GE(current, last);
    last = current;
  }
}
