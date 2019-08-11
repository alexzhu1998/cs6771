#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <initializer_list>
#include <iterator>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <iostream>
#include <algorithm>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:

  /******************
   * NODE AND EDGES * 
	 ******************/

  // Node and Edge Declaration
  struct Node;
  struct Edge;

	// Node Definition
  struct Node {
    N value;
    std::vector<std::weak_ptr<Edge>> out_edges;
    std::vector<std::weak_ptr<Edge>> in_edges;

		// Node Constructors
    Node() = default;
    Node(N node_value) : value{node_value} {};
		// TODO should we have initialisers/methods for adding to int/out_edges?
		
	bool operator==(const Node& o) {
		return (this->value == o.value && this->out_edges == o.out_edges && this->in_edges == o.in_edges);
	}

	bool operator!=(const Node& o) {
		return !(this->value == o.value && this->out_edges == o.out_edges && this->in_edges == o.in_edges);
	}    
  };

	// Edge Definition
  struct Edge {
	std::weak_ptr<Node> src;
    std::weak_ptr<Node> dst;
    E weight;

		// Edge Constructors
  	Edge() = default;

    Edge(std::weak_ptr<Node> source, 
         std::weak_ptr<Node> destination, E w) : src{source}, dst{destination}, weight{w} {};

    bool operator==(const Edge& rhs) {
	    return (this->src == rhs.src && this->dst == rhs.dst && this->weight == rhs.weight);
	}

	bool operator!=(const Edge& rhs) {
	    return !(this->src == rhs.src && this->dst == rhs.dst && this->weight == rhs.weight);
	}
  
  	/* Destructor */
  	~Edge() {
  		/* Reset weak pointer to destination, destroying path */
  		dst.reset(); 
  	}
  };

	/* Sorting edges */
	// TODO
	struct SortEdgeComparator {
	};

  /************************************
   * GRAPH CONSTRUCTORS & DESTRUCTORS *
   ************************************/

	// Nodes == strings (out_edges and in_edges)
	// Edges == dest_node, src_node, weight(double)

  /* Default contructor*/	
  Graph(): nodes{}, edges{} {};

  /* Constructor iterates over nodes and adds them to the graph*/
  Graph(std::vector<std::string>::const_iterator begin, 
				std::vector<std::string>::const_iterator end) {
    for (auto i = begin; i != end; ++i) {
			this->InsertNode(*i);
    }
  }
  
  /* Constructor iterates over tuples containing source node, destination node and edge 
	 * weight and add them to the graph. Essentially iterates over a vector of edges and 
	 * adds them to a new graph.
	 */
	Graph(std::vector<std::tuple<std::string, std::string, double>>::const_iterator begin, 
				std::vector<std::tuple<std::string, std::string, double>>::const_iterator end) {

		for (auto i = begin; i != end; ++i) {
			// getting the strings from the tuples
			std::string src_string = std::get<0>(*i);
			std::string dest_string = std::get<1>(*i);

			// if nodes missing, create them
			if (this->IsNode(src_string) == false) {
				this->InsertNode(src_string);
			}
			if (this->IsNode(dest_string) == false) {
				this->InsertNode(dest_string);
			}
			
			this->InsertEdge(std::get<0>(*i), std::get<1>(*i), std::get<2>(*i));
		}
	}

	/* Initialiser list constructor */
	Graph(std::initializer_list<N> new_nodes) {
		for (const auto &it : new_nodes) {
			this->InsertNode(it);
		}
	};

  class const_iterator {};

	/* Copy constructor */
	Graph(const Graph&);
	/* Move constructor */
	Graph(Graph&&) noexcept;
		
	/* Destructor */
	~Graph() {
		nodes.clear();
		edges.clear();
	}

	/*************
	* OPERATORS *
	*************/

	/* Copy assignment */
	Graph& operator=(const Graph& other);
	/* Move assigment */
	Graph& operator=(Graph&& other);


	/***********
	 * METHODS *
	 ***********/
	bool InsertNode(const N&);
	bool InsertEdge(const N&, const N&, const E&);
	bool DeleteNode(const N&) noexcept;
	bool Replace(const N&, const N&);
	void MergeReplace(const N&, const N&);
	void Clear() noexcept;
	bool IsNode(const N&);
	bool IsConnected(const N&, const N&);
	std::vector<N> GetNodes() const ;
	std::vector<N> GetConnected(const N&);
	std::vector<E> GetWeights(const N&, const N&);
	const_iterator find(const N&, const N&, const E&);
	bool erase(const N&, const N&, const E&);

	/*************
	 * ITERATORS *
	 *************/
	const_iterator erase(const_iterator);
	const_iterator cbegin();
	const_iterator cend();
	const_iterator crbegin();
	const_iterator crend();
	//const_reverse_iterator crend();
	const_iterator begin();
	const_iterator end();
	//const_reverse_iterator rbegin();
	//const_reverse_iterator rend();

	/***********
	 * FRIENDS *
	 ***********/
	// friend bool operator==(const gdwg::Graph<N, E>&, const gdwg::Graph<N, E>&);
	// friend bool operator!=(const gdwg::Graph<N, E>&, const gdwg::Graph<N, E>&);
	friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g) {
		// For each node
	    for (const auto& node : g.nodes) {
	      	os << node->value;
			os << " (\n";
			// Each node has a vector containing edges
			auto begin = node->out_edges.begin();
			auto end = node->out_edges.end();
			// Loop through this vector
			for (auto it = begin; it != end; ++it) {
				// Create shared_ptr from weak_ptr to manage
				auto edge = it->lock();
				auto dest_node = edge->dst.lock();
				os << "  " << dest_node->value << " | " << edge->weight << "\n";
			}
			os << ")\n";
	    }

	    return os;
	}

	// This is probably wrong tbh, right now relying on operator overloading with nodes and edges
	friend bool operator==(const gdwg::Graph<N, E>& a, const gdwg::Graph<N, E>& b) {
		return (a.edges == b.edges || a.nodes == b.nodes);
	}

	friend bool operator!=(const gdwg::Graph<N, E>& a, const gdwg::Graph<N, E>& b) {
		return !(a.edges == b.edges || a.nodes == b.nodes);
	}


	/***************
	 * EXTRA FUNCTIONS
	 ***************/
	std::shared_ptr<Node> GetNode(const N&);
	std::shared_ptr<Node> node_exists(const N&) const;
 
 private:
  // TODO set compare protocol
  std::set<std::shared_ptr<Node>> nodes;
  std::set<std::shared_ptr<Edge>> edges;
 
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
