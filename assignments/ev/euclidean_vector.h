#ifndef EUCLIDEAN_VECTOR_ASST
#define EUCLIDEAN_VECTOR_ASST

#include <exception>
#include <string>
#include <memory>

#include <vector>
#include <list>
#include <ostream>

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
    EuclideanVector(): EuclideanVector{1} {};
	
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
		EuclideanVector(const EuclideanVector&);
		// Move constructor
		EuclideanVector(EuclideanVector&&) noexcept;

	  // Destructor
		~EuclideanVector() noexcept;


    // Copy assignment operator
		EuclideanVector& operator=(const EuclideanVector&);
		// Move assignment operator
		EuclideanVector& operator=(EuclideanVector&&) noexcept;
    // Subscript operator (write/read)
    double& operator[](const int index);
    const double& operator[](const int index) const;
		// += operator
		EuclideanVector& operator+=(const EuclideanVector&);
    // -= operator
   	EuclideanVector& operator-=(const EuclideanVector&);
    // *= operator (scalar multiplication only)
    EuclideanVector& operator*=(const double);
    // /= operator (scalar division only)
    EuclideanVector& operator/=(const double);

    // Vector type conversion operator
    explicit operator std::vector<double>() const;
    // List type conversion operator
    explicit operator std::list<double>() const;

    // Methods
    double at(int) const;
    double& at(int);
		int GetNumDimensions() const;
    double GetEuclideanNorm() const;
    EuclideanVector CreateUnitVector();

    // Friends
    // Output Stream
    friend bool operator==(const EuclideanVector&, const EuclideanVector&);
    friend bool operator!=(const EuclideanVector&, const EuclideanVector&);
    friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
    friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
    friend double operator*(const EuclideanVector&, const EuclideanVector&);
    friend EuclideanVector operator*(const EuclideanVector&, double);
    friend EuclideanVector operator*(double, const EuclideanVector&);
    friend EuclideanVector operator/(const EuclideanVector&, double);

  	friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);


  	// TODO(you): add more
 	private:
    std::unique_ptr<double[]> magnitudes_;
		// TODO(you): add more
		int size_;

};

#endif	// EUCLIDEAN_VECTOR_ASST
