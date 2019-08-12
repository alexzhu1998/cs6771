/*
 * Advanced C++ (COMP6771) 2019T2 Assignment 2
 
 * Amri Chamela (z5116701) - a.chamela@student.unsw.edu.au
 * Christopher Shi - TODO 
 *
 * A Graph class that provides the implementation and functionality to create and manipulate
 * a directed weighted graph, along with a custom iterator to traverse the edges of the 
 * graph.
 *
 */

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
		// Node Destroyer?
		~Node() {
			
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

	/* Sorting edges_ */
	// TODO
	struct SortEdgeComparator {
	};

  /************************************
   * GRAPH CONSTRUCTORS & DESTRUCTORS *
   ************************************/

	// Nodes == strings (out_edges and in_edges)
	// Edges == dest_node, src_node, weight(double)

  /* Default contructor*/	
  Graph(): nodes_{}, edges_{} {};

  /* Constructor iterates over nodes_ and adds them to the graph*/
  Graph(std::vector<std::string>::const_iterator begin, 
				std::vector<std::string>::const_iterator end) {
    for (auto i = begin; i != end; ++i) {
			this->InsertNode(*i);
    }
  }
  
  /* Constructor iterates over tuples containing source node, destination node and edge 
	 * weight and add them to the graph. Essentially iterates over a vector of edges_ and 
	 * adds them to a new graph.
	 */
	Graph(std::vector<std::tuple<std::string, std::string, double>>::const_iterator begin, 
				std::vector<std::tuple<std::string, std::string, double>>::const_iterator end) {

		for (auto i = begin; i != end; ++i) {
			// getting the strings from the tuples
			std::string src_string = std::get<0>(*i);
			std::string dest_string = std::get<1>(*i);

			// if nodes_ missing, create them
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
	Graph(std::initializer_list<N> new_nodes_) {
		for (const auto &it : new_nodes_) {
			this->InsertNode(it);
		}
	};

	/* Copy constructor */
	Graph(const Graph&);
	/* Move constructor */
	Graph(Graph&&) noexcept;
		
	/* Destructor */
	~Graph() {
		nodes_.clear();
		edges_.clear();
	}

	/*************
	* OPERATORS *
	*************/

	/* Copy assignment */
	Graph& operator=(const Graph& other);
	/* Move assigment */
	Graph& operator=(Graph&& other);

	/******************
	 * ITERATOR CLASS *
	 ******************/
	class const_iterator {
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = std::tuple<N, N, E>;
			using reference = std::tuple<const N&, const N&, const E&>;
			using pointer = std::tuple<const N*, const N*, const E*>;
			using difference_type = int;

			reference operator*() const noexcept;
			// reference operator*() const { return this->edges_->lock(); }
						
			const_iterator& operator++();
			const_iterator operator++(int) {
				auto copy{*this};
				++(*this);
				return copy;
			}	

			const_iterator& operator--();
			const_iterator operator--(int) {
				auto copy{*this};
				--(*this);
				return copy;
			}
			
			// This one isn't strictly required, but it's nice to have
			pointer operator->() const { return &(operator*()); }

			friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) noexcept {
				return (lhs.edge_ == rhs.edge_);
			}

			friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) noexcept { 
				return !(lhs == rhs); 
			}

		private:
			typename std::set<std::shared_ptr<Edge>>::iterator edge_;

			friend class Graph;
			const_iterator(const decltype(edge_) edge): edge_{edge} {};
	};

	/***********
	 * METHODS *
	 ***********/
	bool InsertNode(const N&);
	bool InsertEdge(const N&, const N&, const E&);
	bool DeleteNode(const N&) noexcept;
	bool Replace(const N&, const N&);
	void MergeReplace(const N&, const N&);
	void Clear() noexcept;
	bool IsNode(const N&) const;
	bool IsConnected(const N&, const N&) const;
	std::vector<N> GetNodes() const;
	std::vector<N> GetConnected(const N&) const;
	std::vector<E> GetWeights(const N&, const N&) const;
	const_iterator find(const N&, const N&, const E&);
	bool erase(const N&, const N&, const E&);
	const_iterator erase(const_iterator);

	/*************
	 * ITERATORS *
	 *************/

	using iterator = const_iterator;
	iterator begin() noexcept { return cbegin(); }
	iterator end() noexcept { return cend(); }
	const_iterator cbegin();
	const_iterator cend();
	const_iterator begin() const noexcept { return cbegin(); }
	const_iterator end() const noexcept { return cend(); }

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	reverse_iterator rbegin() noexcept { return reverse_iterator{end()}; }
	reverse_iterator rend() noexcept { return reverse_iterator{begin()}; }
	const_reverse_iterator crbegin();
	const_reverse_iterator crend();
	const_reverse_iterator rbegin();
	const_reverse_iterator rend();

	/***********
	 * FRIENDS *
	 ***********/
	friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g) {
		// For each node
	    for (const auto& node : g.nodes_) {
	      	os << node->value;
			os << " (\n";
			// Each node has a vector containing edges_
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

	// This is probably wrong tbh, right now relying on operator overloading with nodes_ and edges_
	friend bool operator==(const gdwg::Graph<N, E>& a, const gdwg::Graph<N, E>& b) {
		return (a.edges_ == b.edges_ || a.nodes_ == b.nodes_);
	}

	friend bool operator!=(const gdwg::Graph<N, E>& a, const gdwg::Graph<N, E>& b) {
		return !(a.edges_ == b.edges_ || a.nodes_ == b.nodes_);
	}


	/*******************
	 * EXTRA FUNCTIONS *
	 *******************/
	std::shared_ptr<Node> GetNode(const N&);

	bool edge_exists(N src, N dst, E w) {
		// check if edge already exists (return false)
		for (const auto &it : this->edges_) {
			auto src_node = it->src.lock();
			auto dst_node = it->dst.lock();
			if (src_node->value == src && dst_node->value == dst && it->weight == w) {
				return true;
			}
		}
		return false;
	}


	std::shared_ptr<Node> NodeExists(const N& val) const{
		for(const auto& node : nodes_){
			if(node.get()->value == val){
					return node;
			}
		}
		return {};
		return nullptr;
	}
 
 private:
	// TODO set compare protocol
	std::set<std::shared_ptr<Node>> nodes_;
	std::set<std::shared_ptr<Edge>> edges_;
}; // namespace gdwg
}

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
