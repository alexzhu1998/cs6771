#include "tutorials/week4/Point.h"

#include <ostream>
#include <istream>
#include <iostream>

// function implementation of output operator for point class
std::ostream& operator<<(std::ostream& os, const Point& p) {
	// assigning to output stream
	os << "(" << p.x_ << "," << p.y_ << ")";
	return os;
}

// function implementation of input operator for point class
std::istream& operator>>(std::istream& is, Point& type) {
	return is >> type.x_ >> type.y_;
}

int main() {
	Point p{1,2};
	std::cout << p << '\n';
}
