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
    
    // TODO: Destructor
    ~Node() {
    	for (auto& edge : out_edges) {
    		delete(edge);
    	}
    	for (auto& edge : in_edges) {
    		delete(edge);
    	}
    }
  };

	// Edge Definition
  struct Edge {
    std::weak_ptr<Node> dest;
    std::weak_ptr<Node> src;
    E weight;

		// Edge Constructors
  	Edge() = default;

    Edge(std::weak_ptr<Node> source, std::weak_ptr<Edge> destination, E w) : dest{destination}, src{source}, weight{w} {};
  
  	/* Destructor */
  	~Edge() {
  		/* Reset weak pointer to destination, destroying path */
  		dest.reset(); 
  	}
  };

  /************************************
   * GRAPH CONSTRUCTORS & DESTRUCTORS *
   ************************************/

	// Nodes == strings (out_edges and in_edges)
	// Edges == dest_node, src_node, weight(double)

  /* Default contructor*/	
  Graph(): nodes{}, edges{} {};

  /* Constructor iterates over nodes and adds them to the graph*/
  Graph(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
    for (auto i = begin; i != end; ++i) {
      Node n = Node{*i};	
      nodes.insert(n);
    }
  }
  
  /* Constructor iterates over tuples of source node, destination node and edge weight and add them to the graph
   * Essentially iterates over a vector of edges and adds them to a new graph
	 */
  Graph(std::vector<std::tuple<std::string, std::string, double>>::const_iterator begin, 
        std::vector<std::tuple<std::string, std::string, double>>::const_iterator end) {
		// tuple is of <string, string, double> 
		// Assumption is made that first string is dest and second string is src

		// for each tuple in the vector
		// if either node not present, create the node
		// create the edge and add to graph
		for (auto i = begin; i != end; ++i) {
			// if nodes missing, create them
			if (nodes.find(std::get<0>(*i)) < 1) {
				nodes.insert(Node(std::get<0>(*i)));
			}
			if (nodes.find(std::get<1>(*i)) < 1) {
				nodes.insert(Node(std::get<1>(*i)));
			}

			edges.insert(Edge(std::get<0>(*i), std::get<1>(*i), std::get<2>(*i)));
			// TODO this insert does not add edges to the in_edges and out_edges
			// create a custom insert() function that adds to in_edges and out_edges
		}
  }

  /* Initialiser list constructor */
  Graph(std::initializer_list<N> new_nodes) {
    nodes.insert(nodes.end(), new_nodes.begin(), new_nodes.end());
  };

  class const_iterator {};

  /* Copy constructor */
  Graph(const Graph& o) : nodes{}, edges{} {
    if (this != &o) {
    	// TODO: delete "this"

    	/* Copy across class atttributes */
    	for (const auto& node : o.nodes) {
    		// TODO: insert node
    	}

    	for (const auto& edge : o.edges) {
    		// TODO: insert edge
    	}
    }
    /* Else, same object. No copy required */
  }

  /* Move constructor */
  Graph (const Graph&& o) {
  	if (this != &o) {
  		// TODO: delete "this" properly

    	/* Copy across class atttributes */
    	for (const auto& node : o.nodes) {
    		// TODO: insert node
    	}

    	for (const auto& edge : o.edges) {
    		// TODO: insert edge
    	}
    	// todo; delete
  	} 
  }

	/* Destructor */
  	// TODO
	~Graph() {
		/*
		for (auto& edge : edges) {
			// todo
		}
		for (auto& node : nodes) {
			// dammit
		}*/
	}

	/*************
	* OPERATORS *
	*************/

	/* Copy assignment */
	Graph& operator=(Graph& o) {
		if (this != &o) {
	    	// TODO: delete "this"

	    	/* Copy across class atttributes */
	    	for (const auto& node : o.nodes) {
	    		// TODO: insert node
	    	}

	    	for (const auto& edge : o.edges) {
	    		// TODO: insert edge
	    	}
    	}
    	return *this;
	}

	/* Move assigment */
	Graph& operator= (const Graph&& o) {
		if (this != &o) {
	    	// TODO: delete "this"

	    	/* Copy across class atttributes */
	    	for (const auto& node : o.nodes) {
	    		// TODO: insert node
	    	}

	    	for (const auto& edge : o.edges) {
	    		// TODO: insert edge
	    	}
	    	// delete other - for move
		}
		return *this;
	}

	/***********
	 * METHODS *
	 ***********/

	bool InsertNode(const N&);
	bool InsertEdge(const N&, const N&, const E&);
	bool DeleteNode(const N&);
	bool Replace(const N&, const N&);
	void MergeReplace(const N&, const N&);
	void Clear();
	bool IsNode(const N&);
	bool IsConnected(const N&, const N&);
	std::vector<N> GetNodes();
	std::vector<N> GetConnected(const N&);
	std::vector<E> GetWeights(const N&, const N&);
	const_iterator find(const N&, const N&);
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
	bool operator==(const Graph&);
	bool operator!=(const Graph&);
	std::ostream& operator<<(std::ostream&);

 private:
  // TODO set compare protocol
  std::set<std::shared_ptr<Node>> nodes;
  std::set<std::shared_ptr<Edge>> edges;
  
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
