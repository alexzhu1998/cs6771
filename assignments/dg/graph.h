#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_


#include <memory>
#include <set>
#include <vector>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
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

  std::set<std::shared_ptr<Node>> nodes;
  std::set<std::shared_ptr<Edge>> edges;

  // graph constructors
  Graph(): nodes{}, edges{}{};

  class const_iterator {};
  
 private:
 
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
