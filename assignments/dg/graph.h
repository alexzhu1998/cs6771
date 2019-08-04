#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <initializer_list>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:

  /******************
   * NODE AND EDGES *
   *****************/
  // node and edge implementation
  struct Node;
  struct Edge;

  struct Node {
    N value;
    std::vector<std::weak_ptr<Edge>> out_edges;
    std::vector<std::weak_ptr<Edge>> in_edges;
    Node() = default;
    Node(N node_value) : value{node_value} {};
    
    // TODO: Destructor
  };

  struct Edge {
    std::weak_ptr<Node> dest;
    std::weak_ptr<Node> src;
    E weight; /* Given in template */

    Edge(std::weak_ptr<Node> source, std::weak_ptr<Edge> destination, E w) : dest{destination}, src{source}, weight{w} {};
  
    // TODO: Destructor
  };

  /****************
   * CONSTRUCTORS *
   ****************/
  /* Default contructor*/
  Graph(): nodes{}, edges{} {};

  /* Iterator constructor */
  Graph(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
    for (auto i = begin; i != end; ++i) {
      Node n = Node{*i};
      nodes.insert(n);
    }
  }
  
  /* Iterates over tuples of source node, destination node and edge weight and add them to the gra
   */
  Graph(std::vector<std::tuple<std::string, std::string, double>>::const_iterator begin, 
        std::vector<std::tuple<std::string, std::string, double>>::const_iterator end) {
    for  
  }

  /* Initialiser list constructor */
  Graph(std::initializer_list<N> new_nodes) {
    nodes.insert(nodes.end(), new_nodes.begin(), new_nodes.end());
  };

  class const_iterator {};

  /*************************************
  * COPY/MOVE CONSTRUCTORS, DESTRUCTOR *
  **************************************/

  /* Copy constructor */
  Graph(const Graph& o) {
    // iterate
  }

  /* Move constructor */

  /* Destructor */
  
 private:
  // TODO set compare protocol
  std::set<std::shared_ptr<Node>> nodes;
  std::set<std::shared_ptr<Edge>> edges;
  
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
