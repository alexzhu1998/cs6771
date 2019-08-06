#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  gdwg::Graph<std::string, int> g;
	
	std::vector<std::string> v{"Hello", "how", "are", "you"};
  gdwg::Graph<std::string, double> b1{v.begin(),v.end()};
  auto set = b1.nodes;

  for (const auto it : set) {
    std::cout << *it << "\n";
  }

  

	// std::string s1{"Hello"};
	// std::string s2{"how"};
	// std::string s3{"are"};
	// auto e1 = std::make_tuple(s1, s2, 5.4);
	// auto e2 = std::make_tuple(s2, s3, 7.6);
	// auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
	// gdwg::Graph<std::string, double> b2{e.begin(), e.end()};

	// std::cout << b2;


  /*g.InsertNode("hello");
  g.InsertNode("how");
  g.InsertNode("are");
  g.InsertNode("you?");

  g.InsertEdge("hello", "how", 5);
  g.InsertEdge("hello", "are", 8);
  g.InsertEdge("hello", "are", 2);

  g.InsertEdge("how", "you?", 1);
  g.InsertEdge("how", "hello", 4);

  g.InsertEdge("are", "you?", 3);

  std::cout << g << '\n';

  gdwg::Graph<std::string, int> g2{g};

  std::cout << g2 << "\n";

  // This is a structured binding.
  // https://en.cppreference.com/w/cpp/language/structured_binding
  // It allows you to unpack your tuple.
  for (const auto& [from, to, weight] : g) {
    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
  }*/
}
