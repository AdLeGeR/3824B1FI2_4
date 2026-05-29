#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "QueueWithTracking.h"

using std::pair;
using std::swap;
using std::vector;

template <typename T>
void defaultSetIndex(T data, size_t index) {}

template <typename T>
class BinaryHeap {
  vector<T>
      heap;  // структура в которой в порядке бинарной кучи хранятся все данные

  void siftUp(size_t index) {
    while (index != 0 && heap[index] <
           heap[(index - 1) / 2]) {  // пока не достигли корня и текущий элемент
                                     // меньше родителя
      swap(heap[index],
           heap[(index - 1) / 2]);  // меняем местами с родителем
      index = (index - 1) / 2;      // переходим к позиции родителя
    }
  }
  void siftDown(size_t index) {
    while (2 * index + 1 < heap.size()) {  // пока есть хотя бы левый ребенок
      size_t left = 2 * index + 1;
      size_t right = 2 * index + 2;
      size_t smallest = index;
      if (left < heap.size() && heap[left] < heap[smallest]) {
        smallest = left;
      }
      if (right < heap.size() && heap[right] < heap[smallest]) {
        smallest = right;
      }
      if (smallest != index) {
        swap(heap[index], heap[smallest]);
        index = smallest;  // переходим к позиции ребенка
      } else {
        break;  // если текущий элемент меньше обоих детей, то куча уже
                // восстановлена
      }
    }
  }

 public:
  BinaryHeap(size_t count) {
    heap.reserve(count);
  }
  void push(T data) {
    heap.push_back(data);
    siftUp(heap.size() - 1);
  }
  T pop() {
    if (heap.empty())
      throw std::runtime_error("Segmentation fault");
    T data = heap[0];
    if (heap.size() ==
        1) {  // если в куче был только один элемент, то просто удаляем его
      heap.pop_back();
      return data;
    }
    heap[0] = heap.back();
    heap.pop_back();
    siftDown(0);
    return data;
  }
  bool isEmpty() {
    return heap.size() == 0;
  }
};

template <typename T>
class BinaryHeapWithTracking : public QueueWithTracking<T> {
  vector<pair<T, size_t>>
      heap;  // структура в которой в порядке бинарной кучи хранятся все данные
  // во втором поле пары хранится индекс элемента в массиве indexes, который
  // указывает на положение элемента в куче
  vector<size_t> indexes;  // вектор индексов, которые указывают на положение
                           // элемента в куче
  // индекс в этом векторе определяется при добавлении элемента в кучу.
  BinaryHeap<size_t>
      freeIndexes;  // куча свободных индексов для новых элементов

  void siftUp(size_t index) {
    while (index != 0 &&
           heap[index] <
        heap[(index - 1) / 2]) {  // пока не достигли корня и текущий элемент
                                  // меньше родителя меняем местами с родителем
      indexes[heap[index].second] =
          (index - 1) / 2;  // обновляем индекс в indexes для текущего элемента
      indexes[heap[(index - 1) / 2].second] =
          index;  // обновляем индекс в indexes для родителя

          swap(heap[index], heap[(index - 1) / 2]);

      index = (index - 1) / 2;  // переходим к позиции родителя
    }
  }

  void siftDown(size_t index) {
    while (2 * index + 1 < heap.size()) {  // пока есть хотя бы левый ребенок
      size_t left = 2 * index + 1;
      size_t right = 2 * index + 2;
      size_t smallest = index;
      if (left < heap.size() && heap[left] < heap[smallest]) {
        smallest = left;
      }
      if (right < heap.size() && heap[right] < heap[smallest]) {
        smallest = right;
      }
      if (smallest != index) {
          indexes[heap[index].second] =
            smallest;  // обновляем индекс в indexes для текущего элемента
        indexes[heap[smallest].second] =
            index;  // обновляем индекс в indexes для ребенка
        swap(heap[index], heap[smallest]);
        index = smallest;  // переходим к позиции ребенка
      } else {
        break;  // если текущий элемент меньше обоих детей, то куча уже
                // восстановлена
      }
    }
  }

 public:
  BinaryHeapWithTracking(size_t count): freeIndexes(count) {
    heap.reserve(count);
  }
  size_t push(T data) override {
    size_t index;
    if (freeIndexes.isEmpty()) {
      indexes.push_back(heap.size());  // сохраняем индекс нового элемента
      index = indexes.size()-1;          // индекс для нового элемента
    } else {
      index = freeIndexes.pop();         // получаем свободный индекс
      indexes[index] = heap.size();  // сохраняем индекс нового элемента
    }
    heap.push_back(pair<T, size_t>(data, index));
    siftUp(heap.size() - 1);
    return index;  // возвращаем индекс элемента в indexes
  }
  T pop() override {
    if (heap.empty())
      throw std::runtime_error("Segmentation fault");
    T data = heap[0].first;
    size_t index = heap[0].second;  // получаем индекс элемента в indexes
    freeIndexes.push(index);        // освобождаем индекс для будущих элементов
    if (heap.size() ==
        1) {  // если в куче был только один элемент, то просто удаляем его
      heap.pop_back();
      return data;
    }
    heap[0] = heap.back();
    index = heap[0].second;  // обновляем индекс элемента, который
    indexes[index] = 0;      // переместился на корень
    heap.pop_back();
    siftDown(0);
    return data;
  }
  void decreaseKey(size_t index, T data) override {
    heap[indexes[index]].first = data;
    siftUp(indexes[index]);  // восстанавливаем кучу, всплывая элемент вверх
  }
  bool isEmpty() const override {
    return heap.size() == 0;
  }
};


