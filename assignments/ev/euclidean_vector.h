// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructor with default value of 1
  EuclideanVector(): EuclideanVector{1} {}
  // Default constructor
  explicit EuclideanVector(int i): magnitudes_{std::make_unique<double[]>(i)}, size_{i} {}
  
  // Constructor with int size and double dimension
  EuclideanVector(int size, double dimension) : EuclideanVector(size) {
    for (int i = 0; i < size_; i++) {
      magnitudes_[i] = dimension;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  // TODO(you): add more
 private:
  std::unique_ptr<double[]> magnitudes_;
  // TODO(you): add more
  int size_;
};
