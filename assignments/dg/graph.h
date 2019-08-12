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
    std::vector<std::weak_ptr<Edge>> out_edges_;
    std::vector<std::weak_ptr<Edge>> in_edges_;

		// Node Constructors
    Node() = default;
    Node(N node_value) : value{node_value} {};
		// TODO should we have initialisers/methods for adding to int/out_edges_?
		
		bool operator==(const Node& o) {
			return (this->value == o.value && this->out_edges_ == o.out_edges_ && this->in_edges_ == o.in_edges_);
		}

		bool operator!=(const Node& o) {
			return !(this->value == o.value && this->out_edges_ == o.out_edges_ && this->in_edges_ == o.in_edges_);
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

	// Nodes == strings (out_edges_ and in_edges_)
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
			using iterator_category = std::forward_iterator_tag;
		    using value_type = char;
		    using reference = char&;
		    using pointer = char*;
		    using difference_type = int;

			pointer operator->() const { return &(operator*()); }
			Edge operator*() const { return edges_->lock(); }

			const_iterator operator--() {
				--inner_;
				if (inner_ == outer_->begin()) {
					do {
						--outer_;
					} 
					while (outer_ != sentinel_start_ && outer_->end() == outer_->begin());
						if (outer_ != sentinel_start_) {
							inner_ = outer_->end();
						}
				}
				return *this;
			}

			const_iterator operator++() {
				++inner_;
				if (inner_ == outer_->end()) {
					do {
						++outer_;
					} 
					while (outer_ != sentinel_end_ && outer_->begin() == outer_->end());
						if (outer_ != sentinel_end_) {
							inner_ = outer_->begin();
						}
				}
				return *this;
			}

			/* Prefix increment/decrement */
			const_iterator operator++(int) {
				auto copy{*this};
				++(*this);
				return copy;
			}

			const_iterator operator--(int) {
				auto copy{*this};
				--(*this);
				return copy;
			}

			 friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
		      // We need to check the sentinel because comparison of default constructed iterators is undefined.
		      return lhs.outer_ == rhs.outer_ && (lhs.outer_ == lhs.sentinel_ || lhs.inner_ == rhs.inner_);
		    }

			friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) { 
				return !(lhs == rhs); 
			}

		private:
			std::vector<std::string>::iterator outer_;
		    const std::vector<std::string>::iterator sentinel_end_;
		    const std::vector<std::string>::iterator sentinel_start_;
		    std::string::iterator inner_;

		    friend class Graph;
		    const_iterator(const decltype(outer_)& outer, const decltype(sentinel_end_)& sentinel_end, 
		    	const decltype(sentinel_start_)& sentinel_start, const decltype(inner_)& inner): 
		    	outer_{outer}, sentinel_end_{sentinel_end}, sentinel_start_{sentinel_start}, inner_{inner} {}
	};

	using const_reverse_iterator = const_iterator;

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
	    for (const auto& node : g.nodes_) {
	      	os << node->value;
			os << " (\n";
			// Each node has a vector containing edges_
			auto begin = node->out_edges_.begin();
			auto end = node->out_edges_.end();
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


	/***************
	 * EXTRA FUNCTIONS
	 ***************/
	std::shared_ptr<Node> GetNode(const N&);
	// std::shared_ptr<Node> NodeExists(const N&) const;

	std::shared_ptr<Node> NodeExists(N val) const{
		for(const auto& node : nodes_){
			if(node.get()->value == val){
					return node;
			}
		}
		return {};
	}
 
 private:
	// TODO set compare protocol
	std::set<std::shared_ptr<Node>> nodes_;
	std::set<std::shared_ptr<Edge>> edges_;
 	//explicit const_iterator(std::set<std::shared_ptr<Edge>> edge_it_): edge_it_{edges_} {}
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
