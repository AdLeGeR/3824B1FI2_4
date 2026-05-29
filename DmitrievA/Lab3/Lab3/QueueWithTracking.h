#pragma once

template <typename T>
class QueueWithTracking {
 public:
  QueueWithTracking() {}
  virtual size_t push(T data) = 0;
  virtual T pop() = 0;
  virtual void decreaseKey(size_t index, T data) = 0;
  virtual bool isEmpty() const = 0;
};