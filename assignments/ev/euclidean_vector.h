#ifndef EUCLIDEAN_VECTOR_ASST
#define EUCLIDEAN_VECTOR_ASST

#include <exception>
#include <string>
#include <memory>

#include <vector>

class EuclideanVectorError : public std::exception {
 	public:
		explicit EuclideanVectorError(const std::string& what) : what_(what) {}
		const char* what() const noexcept{ return what_.c_str(); }
 	private:
  	std::string what_;
};

class EuclideanVector {
 	public:
		// TODO: should the implementation of constructors be in euclidean_vector.h
		// especially how you would structure delegated constructors in .cpp file

		// Default constructor if no values are set
		// EuclideanVector(): EuclideanVector{1} {};
	
		// Default constructor - takes in dimensions, but no magnitudes
		explicit EuclideanVector(int i): magnitudes_{std::make_unique<double[]>(i)},
																		 size_{i} {}
    // 
		// A constructor takes in the number of dimensions (int) and initialises 
		// the magnitude in each dimension as the second argument (double)
		EuclideanVector(int size, double dimension) : EuclideanVector(size) {
			for (int i = 0; i < size_; i++) {
				magnitudes_[i] = dimension;
			}
		}

		// A constructor that takes in the start and end of an iterator to a 
		// std:vector and works out the required dimensions and sets the 
		// magnitudes in each each dimensions according to the iterated values
		EuclideanVector(std::vector<double>::iterator b, 
				std::vector<double>::iterator e) : EuclideanVector(std::distance(b, e)) {
			for (int i = 0; i < size_; i++) {
				magnitudes_[i] = *b;
				b++;
			}
		}

		// Copy constructor
		EuclideanVector(const EuclideanVector& other);
		// Move constructor
		EuclideanVector(EuclideanVector&& other) noexcept;
		// Copy assignment operator
		EuclideanVector& operator=(const EuclideanVector&) = default;
		// Move assignment operator
		EuclideanVector& operator=(EuclideanVector&&) = default;

		// + operator
		EuclideanVector& operator+=(const EuclideanVector& b);

		// Destructor
		~EuclideanVector() noexcept;

		int GetNumDimensions();

  	friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  	// TODO(you): add more
 	private:
		std::unique_ptr<double[]> magnitudes_;
		// TODO(you): add more
		int size_;

};

#endif	// EUCLIDEAN_VECTOR_ASST
