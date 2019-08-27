// Point.h

#include <ostream>
#include <istream>

class Point {
	public:
		Point(int x, int y) : x_{x}, y_{y} {};

		// these are prototypes i think
		friend std::ostream& operator<<(std::ostream& os, const Point& type);
		friend std::istream& operator>>(std::istream& is, Point& type);

		

		Point& operator+=(const Point& p);
		Point& operator-=(const Point& p);
		// 3. Why would this be considered not a wise decision to provide this overload?
		// 	Because there are more than one way to multiply two vectors together: 
		// Point& operator*=(const Point& p);

		// 4. Why are some operator overloads done as member functions vs friends?
		// 	- Non members: for when the operator doesn't take an instance of the class as 
		// 	the LHS argument.
		// 		If we need this non-member function to access private fields of the class
		// 		type,  we define this non-member overload as a friend. 
		// 		we define this non-member overload as a friend.
		// 	- Members: For when the operator does take an instance of class as the LHS arg

	private:
		int x_;
		int y_;
};
