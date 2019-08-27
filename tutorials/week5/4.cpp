// Point.h:
#include <vector>
#include <cmath>

class Point {
  public:
    Point(int x, int y) : x_(x), y_(y) {}
		
		// Length of the origin from the points current coordinates
		// Pythagoras
		operator double() {
			return sqrt(x_*x_ + y_*y_);
		}

  private:
    int x_;
    int y_;
};

// Point.cpp:
#include <iostream>
#include <vector>
int main() {
  Point p{1,2};
  double length = p;
}
