#ifndef STRINGQUEUE_H_
#define STRINGQUEUE_H_

#include <string>
#include <memory>
#include <stdexcept>


template <typename T, int max_size>
class Queue {
	public:

		// Delegating constructor
		// explicit Queue() : Queue(5) {};
		
		// Default constructor for non type parameter version
		explicit Queue() : queue_{std::make_unique<T[]>(max_size)} {}

		// Constructor using size
		Queue(int size) : size_curr_{0}, queue_{std::make_unique<T[]>(size)} {}
		// Copy constructor
		Queue(const Queue& q) {
			size_curr_ = q.size_curr_;
			// size_max_ = q.size_max_;
			queue_ = std::make_unique<T[]>(max_size);
			for (int i = 0; i < size_curr_; ++i) {
				queue_[i] = q.queue_[i];
			}
		}

		// Move constructor
		// Should be the same as copy but you delete the original after.
		Queue(Queue&& q) noexcept : queue_{std::move(q.queue_)}, size_curr_{q.size_curr_} {
			q.size_curr_ = 0;
		}
		
		// Copy assignment
		Queue& operator=(const Queue& q) {
			if (this == &q)
				return *this;
			if (queue_.get() != nullptr)
				queue_.reset();


			size_curr_ = q.size_curr_;
			queue_ = std::make_unique<T[]>(max_size);
			for (int i = 0; i < size_curr_; ++i) {
				queue_[i] = q.queue_[i];
			}

			return *this;
		}
	
		// Move assignment
		Queue& operator=(Queue&& q) noexcept {
			queue_ = std::move(q.queue_);
			size_curr_ = q.size_curr_;
			q.size_curr_ = 0;

			return *this;
		}
		
		// Member Functions
		void enque(T s);
		T deque();
		int size() const;

	private:
		int size_curr_;
		// int size_max_;
		std::unique_ptr<T[]> queue_;

};

// Enque member function
template <typename T, int max_size>
void Queue<T, max_size>::enque(T s) {
	if (size_curr_ + 1 > max_size)	 {
		throw std::overflow_error{"Queue is full"};
	}
	queue_[size_curr_] = s;
	size_curr_ += 1;
}

// Deque member function
template <typename T, int max_size>
T Queue<T, max_size>::deque() {
	if (size_curr_ == 0) {
		throw std::logic_error{"No items in queue"};
	}

	T item = queue_[0];
	// Shift all elements forward
	for (auto i = 1; i <= size_curr_; ++i) {
		queue_[i-1] = queue_[i];
	}
	size_curr_--;

	return item;
}

// Size member function
template <typename T, int max_size>
int Queue<T, max_size>::size() const {
	return size_curr_;
}



#endif // STRINGQUEUE_H_
