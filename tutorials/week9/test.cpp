#include <iostream>

template <typename T>
void printPointer(T t) {
  if constexpr (traits::is_a_pointer<T>::value) {
  	std::cout << *t << "\n";
  } else {
  	std::cout << t << "\n";
  }
}
