#include "tutorials/week3/car.h"

// TODO(tutorial): fill me in
// Create const member functions to get the manufacturer and number of seats
// WHat does it mean for class / function to be const correct?
// 	 A const correct class provides const member functions when no state is changed
// 	 inside a function, and provides both const and non-const overloads for when a 
// 	 function returns a reference to a data member that user may be able to modify.


// static object count initilaised to 0
int Car::n_objects = 0;

// oh jokes this is the destructor
Car::~Car() noexcept {
	--n_objects;
}

const std::string& Car::GetManufacturer() const {
	return manufacturer_;
}

int Car::GetNumSeats() const {
	return num_seats_;
}

int Car::GetNumCars() {
	return n_objects;
}
