/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

  == Response ==

  The tests chosen here ensure 100% test coverage over the code that has been written, and
  also attempts to diversify test cases in comparing and utilising different use cases
  considering the class being handled is templated and has numerous methods of
  population and checking validity with regards to nodes and edges.

  As such, tests were often written to consider edge cases, used a mix of contructors and
  also dat types for these constructors. Edges cases commonly considered were empty graphs.
  graphs with minimal data, and graphs with more than minimal data.

  Due to the time constraint it was attempted to cover these cases in minimal amounts, often
  combining the testing of different methods while keeping another method as the focus of the
  tests, e.g. GetNodes was utilised in almost all tests and did not need a separate testing
  suite. Similar functions that fell under this category were monitored, and if an edge case
  did not arise, e.g. exceptions thrown in IsConnected, they were featured in their own
  separate tests.

  The specification was used as a reference when writing the tests to allow them to be written
  as a user from which the implementation was abstracted away from.
*/

#include "assignments/dg/graph.h"

#include <utility>

#include "catch.h"

/****************
 * CONSTRUCTORS *
 ****************/
SCENARIO("Constructing a graph with default, copy, and move") {
  /* Empty Construction */
  WHEN("You construct an empty graph with a vector of strings") {
    std::vector<std::string> v{};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};

    THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes().size() == 0);
    }
  }
  WHEN("You construct an empty graph with a vector of tuples") {
    auto v = std::vector<std::tuple<std::string, std::string, double>>{};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};

    THEN("An EV with corresponding size and values should be produced") {
      REQUIRE(b.GetNodes().size() == 0);
    }
  }
  WHEN("You construct a graph with an empty initialiser list") {
    gdwg::Graph<char, std::string> b{};

    THEN("A graph with no nodes or edges is produced") { REQUIRE(b.GetNodes().size() == 0); }
  }

  /* Populated construction */
  WHEN("You construct an graph with iterators") {
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};

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

    THEN("The copied graph should be empty") { REQUIRE(b2.GetNodes().size() == 0); }
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
      // REQUIRE(b == NULL);
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
      // REQUIRE(b == NULL);
    }
  }
}

/***********************
 * COPY/MOVE ASSIGMENT *
 ***********************/

SCENARIO("Utilising copy/move assignments") {
  /* Copy/Move construction */
  WHEN("You copy construct a graph with an empty graph") {
    gdwg::Graph<char, std::string> b{};
    gdwg::Graph<char, std::string> b2;
    b2 = b;

    THEN("The copied graph should be empty") { REQUIRE(b2.GetNodes().size() == 0); }
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
      // REQUIRE(b == NULL);
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
      // REQUIRE(b == NULL);
    }
  }
}

/***********
 * METHODS *
 ***********/

SCENARIO("Populating graph with insert node") {
  WHEN("Adding a node to an empty graph") {
    gdwg::Graph<std::string, double> g;
    std::string s{"a"};
    bool result1 = g.InsertNode(s);

    THEN("The graph should have a new node") {
      REQUIRE(g.GetNodes().size() == 1);
      REQUIRE(g.IsNode("a") == true);
      REQUIRE(result1 == true);
    }
  }

  WHEN("Adding mutliple nodes to a graph") {
    gdwg::Graph<std::string, double> g{"a"};
    std::string s{"b"};
    std::string t{"c"};
    bool result1 = g.InsertNode(s);
    bool result2 = g.InsertNode(t);

    THEN("The graph should have a new node") {
      REQUIRE(g.GetNodes().size() == 3);
      REQUIRE(g.IsNode("a") == true);
      REQUIRE(g.IsNode("b") == true);
      REQUIRE(g.IsNode("c") == true);
      REQUIRE(result1 == true);
      REQUIRE(result2 == true);
    }
  }

  WHEN("Adding a node that already exists in a graph") {
    gdwg::Graph<std::string, double> g{"a"};
    std::string s{"b"};
    std::string t{"a"};
    bool result1 = g.InsertNode(s);
    bool result2 = g.InsertNode(t);

    THEN("The graph should remain unchanged") {
      REQUIRE(g.GetNodes().size() == 2);
      REQUIRE(g.IsNode("a") == true);
      REQUIRE(g.IsNode("b") == true);
      REQUIRE(result1 == true);
      REQUIRE(result2 == false);
    }
  }
}

SCENARIO("Populating graph with insertEdge") {
  WHEN("Adding an edge to an empty graph") {
    gdwg::Graph<char, double> g{'a'};

    THEN("A runtime exception will be thrown") {
      REQUIRE_THROWS_AS(g.InsertEdge('a', 'b', 1), std::runtime_error);
      REQUIRE_THROWS_WITH(
          g.InsertEdge('a', 'b', 1),
          "Cannot call Graph::InsertEdge when either src or dst node does not exist");
      REQUIRE_THROWS_AS(g.InsertEdge('b', 'a', 1), std::runtime_error);
      REQUIRE_THROWS_WITH(
          g.InsertEdge('b', 'a', 1),
          "Cannot call Graph::InsertEdge when either src or dst node does not exist");
    }
  }

  WHEN("Adding an edge to a graph") {
    gdwg::Graph<char, int> b{'a', 'b', 'x', 'y'};
    bool result = b.InsertEdge('a', 'b', 2);

    THEN("Edge will exist in graph with given weight") {
      REQUIRE(b.IsConnected('a', 'b') == true);
      REQUIRE(b.IsConnected('b', 'a') == false);
      REQUIRE(b.GetWeights('a', 'b').size() == 1);
      REQUIRE(*(b.GetWeights('a', 'b').begin()) == 2);
      REQUIRE(b.GetWeights('b', 'a').size() == 0);
      REQUIRE(result == true);
    }
  }

  WHEN("Adding an edge pointed at the same node") {
    gdwg::Graph<char, int> b{'a', 'b', 'x', 'y'};
    bool result = b.InsertEdge('a', 'a', 2);

    THEN("Edge will exist in graph with given weight") {
      REQUIRE(b.IsConnected('a', 'a') == true);
      REQUIRE(b.GetWeights('a', 'a').size() == 1);
      REQUIRE(*(b.GetWeights('a', 'a').begin()) == 2);
      REQUIRE(result == true);
    }
  }

  WHEN("Adding an edge pointed at the same node") {
    gdwg::Graph<char, int> b{'a', 'b', 'x', 'y'};
    bool result1 = b.InsertEdge('a', 'a', 2);
    bool result2 = b.InsertEdge('a', 'a', 2);

    THEN("Edge will exist in graph with given weight") {
      REQUIRE(b.IsConnected('a', 'a') == true);
      REQUIRE(b.GetWeights('a', 'a').size() == 1);
      REQUIRE(*(b.GetWeights('a', 'a').begin()) == 2);
      REQUIRE(result1 == true);
      REQUIRE(result2 == false);
    }
  }
}

SCENARIO("Deleting a node from a graph") {
  WHEN("The graph is empty") {
    gdwg::Graph<char, int> b{};
    bool result1 = b.DeleteNode('a');

    THEN("Result will be false") {
      REQUIRE(b.GetNodes().size() == 0);
      REQUIRE(result1 == false);
    }
  }

  WHEN("Deleting an existing node from the graph") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    bool result1 = b.DeleteNode("Hello");

    THEN("Node and accompanying edges will be deleted") {
      REQUIRE(result1 == true);
      REQUIRE(b.GetConnected("how").size() == 1);
      REQUIRE_THROWS_AS(b.GetWeights("Hello", "how"), std::out_of_range);
      REQUIRE_THROWS_WITH(b.GetConnected("Hello"),
                          "Cannot call Graph::GetConnected if src doesn't exist in the graph");
    }
  }
}

SCENARIO("Using is and get methods fringe cases") {
  WHEN("Getting a node's connected list that doesn't exist") {
    gdwg::Graph<char, int> b{'a', 'b', 'x', 'y'};

    THEN("An exception is thrown") {
      REQUIRE_THROWS_AS(b.GetConnected('c'), std::out_of_range);
      REQUIRE_THROWS_WITH(b.GetConnected('c'),
                          "Cannot call Graph::GetConnected if src doesn't exist in the graph");
      /* Check src and dest separately */
      REQUIRE_THROWS_AS(b.IsConnected('c', 'e'), std::runtime_error);
      REQUIRE_THROWS_WITH(
          b.IsConnected('c', 'e'),
          "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      REQUIRE_THROWS_AS(b.IsConnected('e', 'c'), std::runtime_error);
      REQUIRE_THROWS_WITH(
          b.IsConnected('e', 'c'),
          "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      /* Check src and dest separately */
      REQUIRE_THROWS_AS(b.GetWeights('a', 'e'), std::out_of_range);
      REQUIRE_THROWS_WITH(
          b.GetWeights('a', 'e'),
          "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
      REQUIRE_THROWS_AS(b.GetWeights('e', 'a'), std::out_of_range);
      REQUIRE_THROWS_WITH(
          b.GetWeights('e', 'a'),
          "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
    }
  }
}

SCENARIO("Replacing nodes in graph - normal and merge") {
  WHEN("Replacing a node that doesn't exist") {
    gdwg::Graph<char, int> b{'a', 'b', 'x', 'y'};

    THEN("An exception is thrown") {
      REQUIRE_THROWS_AS(b.Replace('c', 'a'), std::runtime_error);
      REQUIRE_THROWS_WITH(b.Replace('c', 'a'),
                          "Cannot call Graph::Replace on a node that doesn't exist");
    }
  }

  WHEN("A node is replaced in the graph") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    std::string s4{"Help me"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e3 = std::make_tuple(s1, s3, 3.0);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e3, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    bool result = b.Replace(s1, s4);
    bool result2 = b.Replace(s3, s4); /* cannot replace if data already exists */

    THEN("The copy should be equivalent to the old graph") {
      REQUIRE(result == true);
      REQUIRE(result2 == false);
      REQUIRE(b.GetNodes().size() == 3);
      REQUIRE(b.IsNode(s4) == true);
      REQUIRE(b.GetConnected(s4).size() == 2);
      REQUIRE(b.GetWeights(s4, s2).at(1) == 3.0);
      REQUIRE(b.GetWeights(s4, s3).at(0) == 5.4);
      REQUIRE(b.IsNode(s1) == false);
    }
  }

  WHEN("A node is merge replaced in an empty graph") {
    gdwg::Graph<char, int> c{};

    THEN("An exception is thrown") {
      REQUIRE_THROWS_AS(c.MergeReplace('c', 'a'), std::runtime_error);
      REQUIRE_THROWS_WITH(
          c.MergeReplace('c', 'a'),
          "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
      REQUIRE_THROWS_AS(c.MergeReplace('a', 'c'), std::runtime_error);
      REQUIRE_THROWS_WITH(
          c.MergeReplace('a', 'c'),
          "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
    }
  }

  WHEN("A node is merge replaced") {}
}

/*************
 * ITERATORS *
 *************/

SCENARIO("Accessing a graph's iterator") {
  WHEN("Generating a graph") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
		auto e3 = std::make_tuple(s3, s1, 9.8);
		auto e4 = std::make_tuple(s3, s2, 1.1);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
	
    THEN("Begin should point to the beginning of the edge container") {

			auto begin = b.cbegin();
			const auto& [from, to, weight] = *begin;

      REQUIRE(from == "Hello");
      REQUIRE(to == "how");
      REQUIRE(weight == 5.4);
    }

		// TODO
		THEN("Begin++ should point to the second edge in the container") {}

   	THEN("End should point to the end of the edge container") {
		  auto end = b.cend();
    	const auto& [from, to, weight] = *end;
   
      REQUIRE(from == "how");
      REQUIRE(to == "are");
      REQUIRE(weight == 7.6);
    }

		// TODO
		THEN("Edge-- should point to the second last edge in the container") {}

	}
}

/***********
 * FRIENDS *
 ***********/
SCENARIO("Using graph friend functions") {
  WHEN("Creating two graphs with the same values") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e_cont1 = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> a{e_cont1.begin(), e_cont1.end()};

    /* Edges are inserted in different order */
    std::string s4{"Hello"};
    std::string s5{"how"};
    std::string s6{"are"};
    auto e3 = std::make_tuple(s4, s5, 5.4);
    auto e4 = std::make_tuple(s5, s6, 7.6);
    auto e_cont2 = std::vector<std::tuple<std::string, std::string, double>>{e4, e3};
    gdwg::Graph<std::string, double> b{e_cont2.begin(), e_cont2.end()};

    THEN("Both graphs should be equal") { REQUIRE(a == b); }
  }

  WHEN("Creating two graphs with the same values") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.3);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e_cont1 = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> a{e_cont1.begin(), e_cont1.end()};

    std::string s4{"Hello"};
    std::string s5{"how"};
    std::string s6{"are"};
    auto e3 = std::make_tuple(s4, s5, 5.4);
    auto e4 = std::make_tuple(s5, s6, 7.6);
    auto e_cont2 = std::vector<std::tuple<std::string, std::string, double>>{e3, e4};
    gdwg::Graph<std::string, double> b{e_cont2.begin(), e_cont2.end()};

    THEN("Both graphs should be equal") { REQUIRE(a != b); }
  }

  WHEN("Printing out empty graph") {
    std::ostringstream oss;
    gdwg::Graph<std::string, double> g{};
    oss << g;

    THEN("Print out nothing") { REQUIRE(oss.str() == ""); }
  }

  WHEN("Printing out graph with nodes with no edges and not sorted upon insertion") {
    gdwg::Graph<char, int> b{'a', 'x', 'y', 'b'};
    std::ostringstream oss;

    oss << b;
    THEN("Print out a graph with empty nodes") {
      REQUIRE(oss.str() == "a (\n)\nb (\n)\nx (\n)\ny (\n)\n");
    }
  }

  WHEN("Printing out graph with a combination of nodes and edges populated") {
    auto e1 = std::make_tuple(1, 2, 5.3);
    auto e2 = std::make_tuple(2, 3, -1.0);
    auto e3 = std::make_tuple(2, 2, 5.3);
    auto e4 = std::make_tuple(3, 1, 4.0);
    auto e = std::vector<std::tuple<int, int, double>>{e3, e4, e2, e1};
    gdwg::Graph<int, double> b{e.begin(), e.end()};
    b.InsertNode(-2);

    std::ostringstream oss;
    oss << b;

    THEN("Print out the graph") {
      REQUIRE(oss.str() ==
              "-2 (\n)\n1 (\n  2 | 5.3\n)\n2 (\n  2 | 5.3\n  3 | -1\n)\n3 (\n  1 | 4\n)\n");
    }
  }
}
