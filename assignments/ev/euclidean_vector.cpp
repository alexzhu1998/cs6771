#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful 
// https://en.cppreference.com/w/cpp/algorithm
#include <cmath>

// Copy constructor 
EuclideanVector::EuclideanVector(const EuclideanVector& other) : 
	magnitudes_{std::make_unique<double[]>(other.size_)}, size_{other.size_} {
	for (int i = 0; i < size_; i++) {
		magnitudes_[i] = other.magnitudes_[i];
	}
}

// Move constructor
EuclideanVector::EuclideanVector(EuclideanVector&& other) noexcept : 
	magnitudes_{std::move(other.magnitudes_)}, 
	size_{other.size_} {
		other.size_ = 0;
}

// Destructor implementation
EuclideanVector::~EuclideanVector() {
  magnitudes_.reset();
  size_ = 0;
}

// Copy assignment operator
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& ev) {
  if (this == &ev)  {
    return *this;
  }
  
  // if unique_ptr contains something, reset it before writing from ev
  if (magnitudes_.get() != nullptr) {
    magnitudes_.reset();
  }

  auto size = ev.GetNumDimensions();
  size_ = size;
  magnitudes_ = std::make_unique<double[]>(size);

  for (int i = 0; i < size; i++) {
    magnitudes_[i] = ev.magnitudes_[i];
  }
  return *this;
}

// Move assignment operator
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& ev) noexcept {
  magnitudes_ = std::move(ev.magnitudes_);
  size_ = ev.size_;
  ev.size_ = 0;
  return *this;
}

// Subscript operator
double& EuclideanVector::operator[](const int index) {
  return magnitudes_[index];
}

const double& EuclideanVector::operator[](const int index) const {
  return magnitudes_[index];
}

//+= operator
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& ev) {
  auto X = this->GetNumDimensions();
  auto Y = ev->GetNumDimensions();
  for (int i = 0; i < size_; i++) {
    magnitudes_[i]+= ev.magnitudes_[i];
  } 
  return *this;  
}

//if (this->size_ != o.size_) {
  //std::ostringstream error_stream;
  //error_stream << "Dimensions of LHS(" 
               //<< this->GetNumDimensions() << ") and RHS(" 
               //<< o.GetNumDimensions() << ") do not match";
  //throw std::invalid_argument(error_stream.str());
//}

//-= operator
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& ev) {
  for (int i = 0; i < size_; i++) {
    magnitudes_[i]-= ev.magnitudes_[i];
  } 
  return *this;  
}

// *= operator
EuclideanVector& EuclideanVector::operator*=(const double sc) {
  for (int i = 0; i < size_; i++) {
    magnitudes_[i]*=sc;
  }
  return *this;
}

// /= operator
EuclideanVector& EuclideanVector::operator/=(const double sc) {
  for (int i = 0; i < size_; i++) {
    magnitudes_[i]/=sc;
  }
  return *this;
}

// Vector type conversion
EuclideanVector::operator std::vector<double>() const {
  std::vector<double> ret;

  auto size = this->GetNumDimensions();
  for (int i = 0; i < size; i++) {
    ret.push_back(magnitudes_[i]);
  }
  return ret;
}

// List type conversion
EuclideanVector::operator std::list<double>() const{
  std::list<double> ret;

  auto size = this->GetNumDimensions();
  for (int i = 0; i < size; i++) {
    ret.push_front(magnitudes_[i]);
  }
  return ret;
}

// Value of magnitude
double EuclideanVector::at(int i) const {
  // TODO provide error checking
  return magnitudes_[i];
}

// Reference of magnitude
double& EuclideanVector::at(int i) {
  // TODO provide error checking
  return magnitudes_[i];
}

// GetNumDimensions
int EuclideanVector::GetNumDimensions() const {
	return size_;
}

double EuclideanVector::GetEuclideanNorm() {
  auto size = this->GetNumDimensions();
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += std::pow(magnitudes_[i], 2);
  }

  return std::sqrt(sum);
}

// Friends
bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  bool eq = true;
  auto size = lhs.GetNumDimensions();
  for (int i = 0; i < size; ++i) {
    if (lhs.at(i) != rhs.at(i)) {
      eq = false;
      break;
    }
  }
  return eq;
}

bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  return !(lhs == rhs);
}



// Output Stream
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[";
  auto d = v.GetNumDimensions();
  for (int i = 0; i < d; i++) {
    // replace with subscript operator
    os << v.magnitudes_[i];
    if (d - i != 1) {
      os << " ";
    }
  }
  os << "]";

  return os;
}


