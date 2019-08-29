#ifndef TUTORIALS_WEEK8_ROPE_H_
#define TUTORIALS_WEEK8_ROPE_H_

#include <string>
#include <utility>
#include <vector>

class Rope {
 public:
  explicit Rope(std::vector<std::string> rope): rope_{std::move(rope)} {}
	
	template <typename T>
  class Base_Iterator {
   public:
    // TODO(tutorial): fill this in.
    using iterator_category = std::forward_iterator_tag;
    using value_type = char;
    using reference = char&;
    using pointer = char*;
    using difference_type = int;

    reference operator*() const;
    Base_Iterator& operator++();
    Base_Iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }
    // This one isn't strictly required, but it's nice to have.
    pointer operator->() const { return &(operator*()); }

		// This needs to be implemented
		friend bool operator==(const Base_Iterator& lhs, const Base_Iterator& rhs) {
			// We need to check the sentinel because comparison of default constructed Base_Iterators is undefined
			// lhs outer = rhs outer AND lhs outer == lhs sentinel OR lhs inner == rhs inner
			return lhs.outer_ == rhs.outer_ && (lhs.outer_ == lhs.sentinel_ || lhs.inner_ == rhs.inner_);
		}
    friend bool operator!=(const Base_Iterator& lhs, const Base_Iterator& rhs) { return !(lhs == rhs); }

   private:
    // TODO(tutorial): What data members should we put here?
		//
		// Notice that this is iterating through vector
		std::vector<std::string>::iterator outer_;
		const std::vector<std::string>::iterator sentinel_;

		// and that this is iterating through string
		std::string::iterator inner_;

		friend class Rope;
		Base_Iterator(const decltype(outer_)& outer, 
						 const decltype(sentinel_)& sentinel, 
						 const decltype(inner_)& inner) : outer_{outer}, sentinel_{sentinel}, inner_{inner} {}
  };
 
	using iterator = Base_Iterator<char>;
	iterator begin();
	iterator end();

	using const_iterator = Base_Iterator<const char>;

 private:
  std::vector<std::string> rope_;
};


#endif  // TUTORIALS_WEEK8_ROPE_H_
