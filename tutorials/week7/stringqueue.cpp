#ifndef STRINGQUEUE_H_
#define STRINGQUEUE_H_

#include <string>
#include <memory>

class StringQueue {
 public:
  StringQueue(int size) : size_curr_{0}, size_max_{size}, queue_{std::make_unique<std::string[]>(size)} {}
  void enque(std::string s);
  std::string deque();
  int size() const;
 private:
  int size_curr_;
  int size_max_;
  std::unique_ptr<std::string[]> queue_;
};
#endif  // STRINGQUEUE_H_


// Convert this into a template type. The benefit of having a templated type is that
// you're not binded to a data type like a std::string, instead you can use whichever
// data type you want. 
//
// Replace std::string with type T, so std::string[] would be T[] and 
// - Complete all incomplete definitions
// - Add an appropriate default constructor
// - Add an appropriate copy constructor
//
// Next, make the size of this queue a non-type parameter
//
// [Exercpt]
// A non-type parameter is a special type of parameter that does not substitute for a type
// but is instead replaced by a value. It can be any of the following
// - A value that has integral type of enumeration
// - A pointer or reference to a class object, function, class member function
// - std::nullptr_t

