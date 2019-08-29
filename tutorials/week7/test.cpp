#ifndef STRINGQUEUE_H_
#define STRINGQUEUE_H_

#include <string>
#include <memory>
#include <stdexcept>

template <typename T, int max_size>
class Queue {
 public:
  explicit Queue() : queue_{std::make_unique<T[]>(max_size)} {}
  Queue(const Queue& q) {
  	size_curr_ = q.size_curr_;
  	queue_ = std::make_unique<T[]>(max_size);
  	for (int i = 0; i < size_curr_; ++i) {
  	  queue_[i] = q.queue_[i];
  	}
  }
  void enque(T s);
  T deque();
  int size() const;
 private:
  int size_curr_;
  std::unique_ptr<T[]> queue_;
};

template <typename T>
void Queue<T>::enque(T s) {
  if (size_curr_ + 1 >= max_size) {
  	throw std::overflow_error{"Queue is full"};
  }
  queue_[size_curr_] = s;
  size_curr_ += 1;
}

template <typename T>
T Queue<T>::deque() {
  if (size_curr_ == 0) {
  	throw std::logic_error{"No items in queue"};
  }
  T item = queue_[0];
  for (auto i = 1; i <= size_curr_; ++i) {
  	queue_[i - 1] = queue_[i];
  }

  size_curr_--;
  return item;
}

template <typename T>
int Queue<T>::size() const {
  return size_curr_;
}

#endif  // STRINGQUEUE_H_
