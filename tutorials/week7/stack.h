#ifndef LECTURES_WEEK7_STACK_H_
#define LECTURES_WEEK7_STACK_H_

#include <vector>

template <typename T>
class Stack {
 public:
  // void push(T);
  // T pop();

	// template <typename T>
	void push(T t) {
		stack_.push_back(t);
	}

	// template <typename T>
	T pop() {
		T end = stack_.back();
		stack_.pop_back();
		return end;
	}
 private:
  std::vector<T> stack_;
};

#endif  // LECTURES_WEEK7_STACK_H_

