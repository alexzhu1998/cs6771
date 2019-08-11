/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"

// TODO(students): Fill this in.

/* Constructors */

SCENARIO("Constructing a graph with default, copy, and move") {
  WHEN("")
  WHEN("You construct an graph with iterators") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
  	gdwg::Graph<std::string, double> b{v.begin(),v.end()};

    THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes() == 4);
      REQUIRE(b.at(0) == "Hello");
      REQUIRE(b.at(1) == "how");
      REQUIRE(b.at(2) == "are");
      REQUIRE(b.at(3) == "you");
      REQUIRE(b.getEdges() == 0);
    }
  }
  WHEN("You construct a graph with a tuple iterator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};


    THEN("An EV with corresponding dimension and values will be produced") {
      REQUIRE(b.GetNodes() == 3);
      REQUIRE(b.at(0) == "Hello");
      REQUIRE(b.at(1) == "how");
      REQUIRE(b.at(2) == "are");
      REQUIRE(b.getEdges() == 2);
      // TODO: check the edges
    }
  }
  WHEN("You construct a graph with an initialiser list") {
    gdwg::Graph<char, std::string> b{'a', 'b', 'x', 'y'};

    THEN("Default magnitudes should be 0") {
      REQUIRE(b.GetNodes() == 4);
      REQUIRE(b.at(0) == "a");
      REQUIRE(b.at(1) == "b");
      REQUIRE(b.at(2) == "x");
      REQUIRE(b.at(3) == "y");
      REQUIRE(b.getEdges() == 0);
    }
  }
}
