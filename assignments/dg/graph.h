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
    
  };

	// Edge Definition
  struct Edge {
		std::weak_ptr<Node> src;
    std::weak_ptr<Node> dest;
    E weight;

		// Edge Constructors
  	Edge() = default;

    Edge(std::weak_ptr<Node> source, 
         std::weak_ptr<Node> destination, E w) : src{source}, dest{destination}, weight{w} {};
  
  	/* Destructor */
  	~Edge() {
  		/* Reset weak pointer to destination, destroying path */
  		dest.reset(); 
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
      nodes.insert(std::make_shared<Node>(*i));
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
				nodes.insert(std::make_shared<Node>(src_string));
			}
			if (this->IsNode(dest_string) == false) {
				nodes.insert(std::make_shared<Node>(dest_string));
			}

			// housekeeping
			std::weak_ptr<Node> src_node;
			std::weak_ptr<Node> dest_node; 

			// locating source and destination nodes
			for (const auto &it : this->nodes) {
				if (it->value == src_string)
					src_node = it;
			}
			for (const auto &it : this->nodes) {
				if (it->value == dest_string)
					dest_node = it;
			}
			
			// escalating weak_ptrs to shared_ptrs
			std::shared_ptr<Node> src_sptr = src_node.lock();
			std::shared_ptr<Node> dest_sptr = dest_node.lock();
		
			// creating edge
			auto edge = std::make_shared<Edge>(src_sptr, dest_sptr, std::get<2>(*i));
			edges.insert(edge);

			// adding edges to in_edges and out_edges
			dest_sptr->in_edges.push_back(edge);
			src_sptr->out_edges.push_back(edge);
		}
	}

	/* Initialiser list constructor */
	Graph(std::initializer_list<N> new_nodes) {
		for (const auto &it : new_nodes) {
			nodes.insert(std::make_shared<Node>(it));
		}
	};

  class const_iterator {};

  /* Copy constructor */
  Graph(const Graph& o) : nodes{}, edges{} {
		// if (this == &o)
		//   return *this;

    if (this != &o) {
    	// TODO: delete "this" // TODO do you need to delete this if this is a copy constructor?

    	/* Copy across class atttributes */
    	for (const auto& node : o.nodes) {
				// TODO: insert node
				nodes.insert(node);
    	}

    	for (const auto& edge : o.edges) {
    		// TODO: insert edge
				edges.insert(edge);
    	}
    }
    /* Else, same object. No copy required */
  }

  /* Move constructor */
  Graph (const Graph&& o) noexcept {
  	if (this != &o) {
  		// TODO: delete "this" properly

    	/* Copy across class atttributes */
    	for (const auto& node : o.nodes) {
    		// TODO: insert node
				nodes.insert(node);
    	}

    	for (const auto& edge : o.edges) {
    		// TODO: insert edge
				edges.insert(edge);
    	}

			~Graph(o);
    	// todo; delete
  	} 
  }

	/* Destructor */
  // TODO not sure if this looks correct
	~Graph() {
    nodes.clear();
    edges.clear();
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
	std::vector<N> GetNodes() const ;
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
				auto dest_node = edge->dest.lock();
				os << "  " << dest_node->value << " | " << edge->weight << "\n";
			}
			
			os << ")\n";
    }

    return os;
  }


	/***************
	 * EXTRA FUNCTIONS
	 ***************/
	std::shared_ptr<Node> GetNode(const N&);
 
 private:
  // TODO set compare protocol
  std::set<std::shared_ptr<Node>> nodes;
  std::set<std::shared_ptr<Edge>> edges;
 
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
