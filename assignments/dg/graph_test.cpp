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

  /* Empty Construction */
  WHEN("You construct an empty graph with a vector of strings") {
     std::vector<std::string> v{};
     gdwg::Graph<std::string, double> b{v.begin(),v.end()};

     THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes().size() == 0);
    }
  }
  WHEN("You construct an empty graph with a vector of tuples") {
     auto v = std::vector<std::tuple<std::string, std::string, double>>{};
     gdwg::Graph<std::string, double> b{v.begin(),v.end()};

     THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes().size() == 0);
    }
  }
  WHEN("You construct a graph with an empty initialiser list") {
    gdwg::Graph<char, std::string> b{};

    THEN("A graph with no nodes or edges is produced") {
      REQUIRE(b.GetNodes().size() == 0);
    }
  }

  /* Populated construction */
  WHEN("You construct an graph with iterators") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
  	gdwg::Graph<std::string, double> b{v.begin(),v.end()};

    THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes().size() == 4);
      REQUIRE(b.IsNode("Hello") == true);
      REQUIRE(b.IsNode("how") == true);
      REQUIRE(b.IsNode("are") == true);
      REQUIRE(b.IsNode("you") == true);
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
      REQUIRE(b.GetNodes().size() == 3);
      REQUIRE(b.IsNode("Hello") == true);
      REQUIRE(b.IsNode("how") == true);
      REQUIRE(b.IsNode("are") == true);
    }
  }
  WHEN("You construct a graph with an initialiser list") {
    gdwg::Graph<char, std::string> b{'a', 'b', 'x', 'y'};

    THEN("Default magnitudes should be 0") {
      REQUIRE(b.GetNodes().size() == 4);
      REQUIRE(b.IsNode('a') == true);
      REQUIRE(b.IsNode('b') == true);
      REQUIRE(b.IsNode('b') == true);
      REQUIRE(b.IsNode('y') == true);
    }
  }

  /* Copy/Move construction */
  WHEN("You copy construct a graph with an empty graph") {
    gdwg::Graph<char, std::string> b{};
    gdwg::Graph<char, std::string> b2{b};

    THEN("The copied graph should be empty") {
      REQUIRE(b2.GetNodes().size() == 0);
    }
  }

  WHEN("You construct a graph with a copy constructor") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    gdwg::Graph<std::string, double> b_copy{b};

    THEN("The copy should be equivalent to the old graph") {
      REQUIRE(b_copy.GetNodes().size() == 3);
      REQUIRE(b_copy.IsNode("Hello") == true);
      REQUIRE(b_copy.IsNode("how") == true);
      REQUIRE(b_copy.IsNode("are") == true);
      REQUIRE(b_copy.GetWeights(s1, s2).size() == 1);
      REQUIRE(b_copy.GetWeights(s2, s3).size() == 1);
    }
  }

  WHEN("You move construct a graph with an empty graph") {
    gdwg::Graph<char, std::string> b{};
    gdwg::Graph<char, std::string> b2{std::move(b)};

    THEN("The copied graph should be empty") {
      REQUIRE(b2.GetNodes().size() == 0);
      //REQUIRE(b == NULL);
    }
  }

  WHEN("You move construct a graph") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    gdwg::Graph<std::string, double> b_copy{std::move(b)};

    THEN("The copy should be equivalent to the old graph with old graph destroyed") {
      REQUIRE(b_copy.GetNodes().size() == 3);
      REQUIRE(b_copy.IsNode("Hello") == true);
      REQUIRE(b_copy.IsNode("how") == true);
      REQUIRE(b_copy.IsNode("are") == true);
      REQUIRE(b_copy.GetWeights(s1, s2).size() == 1);
      REQUIRE(b_copy.GetWeights(s2, s3).size() == 1);
      //REQUIRE(b == NULL);
    }
  }
}

// COPY/MOVE ASSIGNMENT
SCENARIO("Utilising copy/move assignments") {
  /* Copy/Move construction */
  WHEN("You copy construct a graph with an empty graph") {
    gdwg::Graph<char, std::string> b{};
    gdwg::Graph<char, std::string> b2;
    b2 = b;

    THEN("The copied graph should be empty") {
      REQUIRE(b2.GetNodes().size() == 0);
    }
  }

  WHEN("You construct a graph with a copy constructor") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    gdwg::Graph<std::string, double> b_copy;

    b_copy = b;

    THEN("The copy should be equivalent to the old graph") {
      REQUIRE(b_copy.GetNodes().size() == 3);
      REQUIRE(b_copy.IsNode("Hello") == true);
      REQUIRE(b_copy.IsNode("how") == true);
      REQUIRE(b_copy.IsNode("are") == true);
      REQUIRE(b_copy.GetWeights(s1, s2).size() == 1);
      REQUIRE(b_copy.GetWeights(s2, s3).size() == 1);
    }
  }

  WHEN("You move an empty graph to a new graph") {
    gdwg::Graph<char, std::string> b{};
    gdwg::Graph<char, std::string> b2;
    b2 = std::move(b);

    THEN("The copied graph should be empty") {
      REQUIRE(b2.GetNodes().size() == 0);
      //REQUIRE(b == NULL);
    }
  }

  WHEN("You move a populated graph to a new graph") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    gdwg::Graph<std::string, double> b_copy;

    b_copy = std::move(b);

    THEN("The copy should be equivalent to the old graph with old graph destroyed") {
      REQUIRE(b_copy.GetNodes().size() == 3);
      REQUIRE(b_copy.IsNode("Hello") == true);
      REQUIRE(b_copy.IsNode("how") == true);
      REQUIRE(b_copy.IsNode("are") == true);
      REQUIRE(b_copy.GetWeights(s1, s2).size() == 1);
      REQUIRE(b_copy.GetWeights(s2, s3).size() == 1);
      //REQUIRE(b == NULL);
    }
  }
}


/**
 * ITERATORS
 */
SCENARIO("Accessing a graph's iterator") {
  WHEN("Accessing the beginning using begin") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    //auto it = b.cbegin();

    //THEN("it should point to the beginning of the edge container") {
    //  REQUIRE(*it->lock()->src == "Hello");
    //}
  } 
}