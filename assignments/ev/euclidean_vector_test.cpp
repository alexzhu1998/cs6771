/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

  Test cases will first be separated following the assignment specifcation and will
  simulate a white box approach. This is a simple way to ensure 100% test coverage.
  This includes testing for raising exceptions.

  Test cases will be tested against:
  - Zero vectors
  - Vectors with 1 magnitude
  - Vectors with multiple magnitudes
  - Negative and 0 magnitude values

  All parts of the interface will be tested, including:
  - All constructors
  - Destructor
  - Operators
  - Methods
  - Friends

  This also simulates testing carried out only with the understanding of the interface 
  provided in euclidea_vector.h. They will aim to replicate real life usage of the library

  Some of the input for the testing will be sanitised as per the assignment specification.
  Therefore, things like constructing a vector with a negative size won't be tested.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

// TODO(students): Fill this in.

#include <vector>
#include <list>

// Constructor tests
// Default constructor
SCENARIO("Construction of a base EuclideanVector") {
  WHEN("Instantiate without any input") {
    EuclideanVector a{};
    THEN("Get the size of a and make sure it's 1") {
      REQUIRE(a.GetNumDimensions() == 1);
    }
    THEN("Get the magnitude and make sure it's 0") {
      REQUIRE(a.at(0) == 0);
    }
  }
  WHEN("Instantiate with 0") {
    EuclideanVector a{0};
    THEN("Get the size of a and make sure it's 0") {
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }
  WHEN("Instantiate 3") {
    EuclideanVector a{3};
    THEN("Make sure the size is 3") {
      REQUIRE(a.GetNumDimensions() == 3);
    }
    THEN("Make sure all 3 magnitudes are equal to 0")
      REQUIRE(a.at(0) == 0);
      REQUIRE(a.at(1) == 0);
      REQUIRE(a.at(2) == 0);
  }
}

// Constructor using a size and magnitude value
SCENARIO("Construction of a EuclideanVector using size and magnitudes") {
  WHEN("Instantiate with 0, 0") {
    EuclideanVector a{0, 0};
    THEN("Make sure size is 0 - no magnitudes") {
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }
  WHEN("Instantiate with 1, 3") {
    EuclideanVector a{1, 3};
    THEN("Make sure size == 1, magnitudes are 3") {
      REQUIRE(a.GetNumDimensions() == 1);
      REQUIRE(a.at(0) == 3);
    }
  }
  WHEN("Instantiate with 3, -1") {
    EuclideanVector a{3, -1};
    THEN("Make sure size is 3, magnitudes are 3.3") {
      REQUIRE(a.GetNumDimensions() == 3);
      REQUIRE(a.at(0) == -1);
      REQUIRE(a.at(1) == -1);
      REQUIRE(a.at(2) == -1);
    }
  }
}

// Constructor using vector iterators
SCENARIO("Construction of a EuclideanVector using std::vector iterators") {
  WHEN("Instantiate with vector containing zeros") {
    std::vector<double> v1{0, 0, 0};
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("Make sure size is 3, magnitudes are all 0") {
      REQUIRE(a.GetNumDimensions() == 3);
      REQUIRE(a.at(0) == 0);
      REQUIRE(a.at(1) == 0);
      REQUIRE(a.at(2) == 0);
    }
    std::vector<double> v2{-1, 0, 3};
    EuclideanVector b{v2.begin(), v2.end()};
    THEN("Make sure size is 3, magnitudes are 0, 0, 3") {
      REQUIRE(b.GetNumDimensions() == 3);
      REQUIRE(b.at(0) == -1);
      REQUIRE(b.at(1) == 0);
      REQUIRE(b.at(2) == 3);
    }
  }

  WHEN("Instantiate with {1, 2, 3, 4, 5}") {
    std::vector<double> v1{1, 2, 3, 4, 5};
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("Make sure size is 5, magnitudes are 1, 2, 3, 4, 5") {
      REQUIRE(a.GetNumDimensions() == 5);
      REQUIRE(a.at(0) == 1);
      REQUIRE(a.at(1) == 2);
      REQUIRE(a.at(2) == 3);
      REQUIRE(a.at(3) == 4);
      REQUIRE(a.at(4) == 5);
    }
  }
}

// Constructor by copy
SCENARIO("Construction of EuclideanVector by copy") {
  WHEN("Instantiate with vector containing zeros") {
    std::vector<double> v1{0, 0, -1};
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{a};
    THEN("Make sure size and magnitues are the same") {
      REQUIRE(a.GetNumDimensions() == b.GetNumDimensions());
      REQUIRE(a.at(0) == b.at(0));
      REQUIRE(a.at(1) == b.at(1));
      REQUIRE(a.at(2) == b.at(2));
    }
  }

  WHEN("Instantiate with vector containing 1, 2, 3, 4, 5") {
    std::vector<double> v1{1, 2, 3, 4, 5};
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{a};
    THEN("Make sure size and magnitues are the same") {
      REQUIRE(a.GetNumDimensions() == b.GetNumDimensions());
      REQUIRE(a.at(0) == b.at(0));
      REQUIRE(a.at(1) == b.at(1));
      REQUIRE(a.at(2) == b.at(2));
      REQUIRE(a.at(3) == b.at(3));
      REQUIRE(a.at(4) == b.at(4));
      // Make sure different addresses
      REQUIRE(&a != &b);
    }
  }
  
  WHEN("Copy a empty vector") {
    EuclideanVector a{0};
    EuclideanVector b{a};
    THEN("Make sure size are the same / both 0") {
      REQUIRE(a.GetNumDimensions() == 0);
      REQUIRE(b.GetNumDimensions() == 0);
    }
  }
}

// Constructor by move
SCENARIO("Construction of EuclideanVector by move") {
  WHEN("Instantiate with vector containing zeros") {
    std::vector<double> v1{0, 0, -1};
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b = std::move(a);
    THEN("Make sure size and magnitues are the same") {
      REQUIRE(b.GetNumDimensions() == 3);
      REQUIRE(b.at(0) == 0);
      REQUIRE(b.at(1) == 0);
      REQUIRE(b.at(2) == -1);

      // Move successful
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }

  WHEN("Instantiate with vector containing 1, 2, 3, 4, 5") {
    std::vector<double> v1{1, 2, 3, 4, 5};
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b = std::move(a);
    THEN("Make sure size and magnitues are the same") {
      REQUIRE(b.GetNumDimensions() == 5);
      REQUIRE(b.at(0) == 1);
      REQUIRE(b.at(1) == 2);
      REQUIRE(b.at(2) == 3);
      REQUIRE(b.at(3) == 4);
      REQUIRE(b.at(4) == 5);

      // Move successful
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }

  WHEN("Move a empty vector") {
    EuclideanVector a{0};
    EuclideanVector b = std::move(a);
    THEN("Make sure size are the same / both 0") {
      REQUIRE(a.GetNumDimensions() == 0);
      REQUIRE(b.GetNumDimensions() == 0);
    }
  }
}

// Operator tests
// Copy by assigmnment
SCENARIO("Copy a EuclideanVector by assignment") {
  WHEN("Copying a vector containing 1, 1, 1") {
    EuclideanVector a{3, 1};
    auto b = a;
    THEN("Make sure size = 3 and magnitudes are correct") {
      REQUIRE(b.GetNumDimensions() == a.GetNumDimensions());
      REQUIRE(b.at(0) == a.at(0));
      REQUIRE(b.at(1) == a.at(1));
      REQUIRE(b.at(2) == a.at(2));
    }
  }
  WHEN("Copying a zero vector") {
    EuclideanVector a{3, 0};
    auto b = a;
    THEN("Make sure size = 3 and magnitudes are correct") {
      REQUIRE(b.GetNumDimensions() == a.GetNumDimensions());
      REQUIRE(b.at(0) == a.at(0));
      REQUIRE(b.at(1) == a.at(1));
      REQUIRE(b.at(2) == a.at(2));
    }
  }
}

// Move by assignment
SCENARIO("Move a EuclideanVector by assignment") {
  WHEN("Moving a vector containing 0, -1, 1.3") {
    std::vector<double> v1{0, -1, 1.3};
    EuclideanVector a{v1.begin(), v1.end()};
    auto b = std::move(a);
    THEN("Make sure size = 3 and magnitudes are correct") {
      REQUIRE(b.GetNumDimensions() == 3);
      REQUIRE(b.at(0) == 0);
      REQUIRE(b.at(1) == -1);
      REQUIRE(b.at(2) == 1.3);
    }
  }
  WHEN("Copying a zero vector") {
    EuclideanVector a{3, 0};
    auto b = std::move(a);
    THEN("Make sure size = 3 and magnitudes are correct") {
      REQUIRE(b.GetNumDimensions() == 3);
      REQUIRE(b.at(0) == 0);
      REQUIRE(b.at(1) == 0);
      REQUIRE(b.at(2) == 0);
    }
  }
}

// Subscript operator
SCENARIO("Getting and setting values using [] operators") {
  WHEN("Accessing an index") {
    EuclideanVector a{3};
    THEN ("Making sure an error is thrown") {
      REQUIRE(a[0] == 0);
    }
  }

  WHEN("Changing an index") {
    EuclideanVector a{3};
    a[1] = 2;
    THEN ("Making sure a[1] == 2") {
      REQUIRE(a[1] == 2);
      REQUIRE(a.GetNumDimensions() == 3);
    }
  }
}

// Arithmetic operators
SCENARIO("Arithmetic operators") {
  std::vector<double> v1{1, 2, 3};
  std::vector<double> v2{4, 5, 6, 7};
  std::vector<double> v3{-1, -2, -3};

  // Addition operator +=
  WHEN("Adding two vectors of different sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v2.begin(), v2.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a += b, "Dimensions of LHS(3) and RHS(4) do not match");
    }
  }
  WHEN("Adding two vectors of same sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v3.begin(), v3.end()};
    a += b;
    THEN("Magnitudes should be added") {
      REQUIRE(a.at(0) == 0);
      REQUIRE(a.at(1) == 0);
      REQUIRE(a.at(2) == 0);
    }
  }

  // Subtraciton operator -=
  WHEN("Subtracting two vectors of different sizes") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v2.begin(), v2.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a -= b, "Dimensions of LHS(3) and RHS(4) do not match");
    }
  }
  WHEN("Subtracting two vectors of same sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v3.begin(), v3.end()};
    a -= b;
    THEN("Magnitudes should be subtracted") {
      REQUIRE(a.at(0) == 2);
      REQUIRE(a.at(1) == 4);
      REQUIRE(a.at(2) == 6);
    }
  }

  // Multiplication operator *=
  WHEN("Multiplying a vector by a scalar") {
    EuclideanVector a{v1.begin(), v1.end()};
    a *= 3;
    THEN("Magnitudes should be multiplied") {
      REQUIRE(a.at(0) == 3);
      REQUIRE(a.at(1) == 6);
      REQUIRE(a.at(2) == 9);
    }
  }

  // Division operator /=
  WHEN("Dividing a vector by 0") {
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a /= 0, "Invalid vector division by 0");
    }
  }
  WHEN("Dividing a vector by a scalar") {
    EuclideanVector a{v1.begin(), v1.end()};
    a /= 2;
    THEN("Magnitudes should be subtracted") {
      REQUIRE(a.at(0) == 0.5);
      REQUIRE(a.at(1) == 1);
      REQUIRE(a.at(2) == 1.5);
    }
  }
}

// Type casting operators
SCENARIO("Type casting EuclideanVectors") {
  std::vector<double> v1{1, 2, 3};
  WHEN("Casting a EV into a std::vector") {
    EuclideanVector a{v1.begin(), v1.end()};
    std::vector<double> r{a};
    THEN("Make sure size and magnitude are the same") {
      REQUIRE(r.size() == a.GetNumDimensions());
      REQUIRE(r.at(0) == a.at(0));
      REQUIRE(r.at(1) == a.at(1));
      REQUIRE(r.at(2) == a.at(2));
    }
  }

  WHEN("Casting a EV into a std::list") {
    EuclideanVector a{v1.begin(), v1.end()};
    std::list<double> r{a};
    THEN("Make sure size, front and back are the same") {
      REQUIRE(r.size() == a.GetNumDimensions());
      REQUIRE(r.front() == 3);
      REQUIRE(r.back() == 1);
    }
  }
}


// Method tests
// .at()
SCENARIO("Using setters and getter methods") {
  EuclideanVector a{2};
  a[0] = 1;
  a[1] = 2;
  WHEN("You try to split an empty string") {
    THEN("You get a single empty result") {
      REQUIRE_THROWS_WITH(a.at(2), "Index 2 is not valid for this EuclideanVector object");
    }
  }
  WHEN("You try to get a value at a valid index(0)") {
    THEN("It should return 1") {
      REQUIRE(a.at(0) == 1);
    }
  }
  WHEN("You try to set a value at a valid index(0)") {
    a[0] = 4;
    THEN("It should return the new value when you access it") {
      REQUIRE(a.at(0) == 4);
    }
  }
}

// .GetNumDimensions()
SCENARIO("Using .GetNumDimensions() to return EV size") {
  std::vector<double> v1{1, 2, 3};
  WHEN ("You try to find the size of an empty vector") {
    EuclideanVector a{0};
    THEN("It should return size = 0") {
      REQUIRE(a.GetNumDimensions() == 0);
    }
  }
  WHEN ("You try to find the size of a non-empty vector") {
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("It should return size = 3") {
      REQUIRE(a.GetNumDimensions() == 3);
    }
  }
}

// .GetEuclideanNorm()
SCENARIO("Using .GetEuclideanNorm() to return Euclidean Norm of an EV") {
  WHEN("You try to find Euclidean Normal of empty vector") {
    EuclideanVector a{0};
    THEN("It should throw an error") {
      REQUIRE_THROWS_WITH(a.GetEuclideanNorm(), "EuclideanVector with no dimensions does not have a norm");
    }
  }
  
  std::vector<double> v1{3, 4};
  WHEN("You try to find Euclidean Normal of aa non-empty vector") {
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("It should return 5") {
      REQUIRE(a.GetEuclideanNorm() == 5);
    }
  }
}

// .CreateUnitVector()
SCENARIO("Using .CreateUnitVector() to create a Unit Vector of an EV") {
  WHEN("You try to find UV of EV with no dimensions") {
    EuclideanVector a{0};
    THEN("It should throw an error") {
      REQUIRE_THROWS_WITH(a.CreateUnitVector(), "EuclideanVector with no dimensions does not have a unit vector");
    }
  }

  WHEN("You try to find UV of EV with normal of 0") {
    EuclideanVector a{3};
    THEN("It should throw an error") {
      REQUIRE_THROWS_WITH(a.CreateUnitVector(), "EuclideanVector with euclidean normal of 0 does not have a unit vector");
    }
  }

  WHEN("You have two identical vectors") {
    EuclideanVector a{2};
    a[0] = 1;
    a[1] = 2;
    EuclideanVector b{2};
    b[0] = 1;
    b[1] = 2;
    THEN("Get their unit vectors") {
      EuclideanVector c{a.CreateUnitVector()};
      EuclideanVector d{b.CreateUnitVector()};
      REQUIRE(c == d);
    }
  }
}

// Friends testing
// Equals to not equals to
SCENARIO("Using == and != friends to compare EV") {
  EuclideanVector a{0};
  EuclideanVector b{0};
  EuclideanVector c{1};
   
  WHEN("You compare two empty vectors") {
   THEN("They should be equal") {
      REQUIRE(a == b);
    }
  }

  WHEN("You compare one empty vector and one non empty vector") {
    // the comparison is now different length
    THEN("They should not be equal") {
      REQUIRE_FALSE(a == c);
    
    }
  }
}

// Arithmetic operators
SCENARIO("Friend arithmetic operators") {
  std::vector<double> v1{1, 2, 3};
  std::vector<double> v2{4, 5, 6, 7};
  std::vector<double> v3{-1, -2, -3};

  // Addition friend +
  WHEN("Adding two vectors of different sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v2.begin(), v2.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a + b, "Dimensions of LHS(3) and RHS(4) do not match");
    }
  }
  WHEN("Adding two vectors of same sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v3.begin(), v3.end()};
    auto c = a + b;
    THEN("Magnitudes should be added") {
      REQUIRE(c.at(0) == 0);
      REQUIRE(c.at(1) == 0);
      REQUIRE(c.at(2) == 0);
    }
  }

  // Subtraciton friend -
  WHEN("Subtracting two vectors of different sizes") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v2.begin(), v2.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a - b, "Dimensions of LHS(3) and RHS(4) do not match");
    }
  }
  WHEN("Subtracting two vectors of same sizes together") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v3.begin(), v3.end()};
    auto c = a - b;
    THEN("Magnitudes should be subtracted") {
      REQUIRE(c.at(0) == 2);
      REQUIRE(c.at(1) == 4);
      REQUIRE(c.at(2) == 6);
    }
  }

  // Multiplication friend * (dot product)
  WHEN("Multiplying a vector by a vector") {
    EuclideanVector a{v1.begin(), v1.end()};
    EuclideanVector b{v3.begin(), v3.end()};
    auto c = a * b;
    THEN("Magnitudes should be multiplied") {
      REQUIRE(c == -14);
    }
  }

  // Multiplication friend *
  WHEN("Multiplying a vector by a scalar") {
    EuclideanVector a{v1.begin(), v1.end()};
    auto b = a * 3;
    THEN("Magnitudes should be multiplied") {
      REQUIRE(b.at(0) == 3);
      REQUIRE(b.at(1) == 6);
      REQUIRE(b.at(2) == 9);
    }
    auto c = 3 * b;
    THEN("Magnitudes should be multiplied") {
      REQUIRE(c.at(0) == 9);
      REQUIRE(c.at(1) == 18);
      REQUIRE(c.at(2) == 27);
    }
  }

  // Division friend /
  WHEN("Dividing a vector by 0") {
    EuclideanVector a{v1.begin(), v1.end()};
    THEN("An exception should be thrown") {
      REQUIRE_THROWS_WITH(a / 0, "Invalid vector division by 0");
    }
  }
  WHEN("Dividing a vector by a scalar") {
    EuclideanVector a{v1.begin(), v1.end()};
    auto b = a / 2;
    THEN("Magnitudes should be subtracted") {
      REQUIRE(b.at(0) == 0.5);
      REQUIRE(b.at(1) == 1);
      REQUIRE(b.at(2) == 1.5);
    }
  }
}