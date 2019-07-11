#include <iostream>
#include <vector>
#include <list>
#include <utility>

#include "assignments/ev/euclidean_vector.h"

int main() {
  EuclideanVector a(2);

	std::vector<double> l{1, 2, 3};
	EuclideanVector b{l.begin(), l.end()};
  std::cout << b << "\n";

	std::vector<double> v2{4, 5, 6, 7};
	EuclideanVector c{v2.begin(), v2.end()};
	
	std::vector<double> a1{5, 4, 3, 2, 1};
	EuclideanVector d{a1.begin(), a1.end()};
	
	std::vector<double> a2{9, 0, 8, 6, 7};
	EuclideanVector e{a2.begin(), a2.end()};
	
	// use the copy constructor
	EuclideanVector f{e};

  // use the copy assignment operator
  d = e;
  std::cout << d << "\n";

  // use the move assignment operator
  d = std::move(b);
  std::cout << d << "\n";

  d.at(1) = 4.3;
  std::cout << d.at(1) << "\n";
  std::cout << d << "\n";


  //std::cout << "list conversion\n";
  //auto vf = std::list<double>{d};
  //for (auto v: vf) {
    //std::cout << v << "\n";
  //}
	
  // std::cout << a.GetNumDimensions() << ": " << a << '\n';
  // std::cout << "D1:" << b.at(1) << " " << b << '\n';
  // std::cout << c << " Euclidean Norm = " << c.GetEuclideanNorm() << '\n';
  // std::cout << d << " Unit Vector: " << d.CreateUnitVector()
  //           << " L = " << d.CreateUnitVector().GetEuclideanNorm() << '\n';
  // std::cout << e << '\n';
  // std::cout << f << '\n';
	
	// test the move constructor
	//EuclideanVector g = std::move(f);

	// std::cout << g << '\n';
	// std::cout << f << '\n';
  // 
  // // try operator overloading
	//e += d;
  //e -= d;
  
  // std::cout << e << '\n';
  // 
  // EuclideanVector h = e - g;
  // std::cout << h << '\n';
  // 
  // // test scalar multiplication
  // h *= 2;
  // std::cout << h << '\n';
  // 
  // EuclideanVector j = b / 2;
  // std::cout << j << '\n';
  // 
  // std::cout << "dot product = " << j * b << '\n';
  // 
  // if (g == (e - d))
  //   std::cout << "true" << '\n';
  // if (j != b)
  //   std::cout << "false" << '\n';
  // 
  // j[0] = 1;
  // std::cout << j << '\n';
  // 
  // // type cast from EuclideanVector to a std::vector
  // auto lj = std::vector<double>{j};
  // 
  // for (auto d : lj) {
  //   std::cout << d << '\n';
  // }
}
