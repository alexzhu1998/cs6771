// #include "assignments/dg/graph.h" // probably not needed... 

#include <iterator>
#include <vector>

/*****************
 * CONSTRUCTORS
 *****************/


/* Copy constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& other) {
	// this.nodes_ = copy nodes_
	for (const auto &node : other.nodes_) {
		InsertNode(node->value);
	}

	// this.edges_ = copy edges_
	for (const auto &edge : other.edges_) {
		InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
	}
}

/* Move constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& other) noexcept {
	// this.nodes_ = copy nodes_
	for (const auto &node : other.nodes_) {
		InsertNode(node->value);
	}

	// this.edges_ = copy edges_
	for (const auto &edge : other.edges_) {
		InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
	}

	// but delete other afterwards
	other.~Graph();
}


/*****************
 * OPERATORS
 *****************/

/* Copy Operator */
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E>& other) {
	if (this == &other) {
		} else {
			this->Clear();
			for (const auto &node : other.nodes_) {
				this->InsertNode(node->value);
			}
			for (const auto &edge : other.edges_) {
				this->InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
			}
		}
	return *this;
}

/* Move operator */
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E>&& other) {
		if (this == &other) {
		} else {
			this->Clear();
			for (const auto & node : other.nodes_) {
				this->InsertNode(node->value);
			}
			for (const auto & edge : other.edges_) {
				this->InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
			}
			other.Clear();
		}
		return *this;
	}


/***********
 * METHODS *
 ***********/

/* InsertNode */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
	// check if node containing val already exists (return false)
	auto node_list = this->GetNodes();
	if (std::find(node_list.begin(), node_list.end(), val) != node_list.end())
		return false;

	auto ret = nodes_.insert(std::make_shared<gdwg::Graph<N, E>::Node>(val));
	return ret.second;
}

/* InsertEdge */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
	// raise an exception if src or dst not found in graph
	// THIS FUNCTION DOES NOT CREATE NODES 

	// check if edge already exists (return false)
	for (const auto &it : this->edges_) {
		auto src_node = it->src.lock();
		auto dst_node = it->dst.lock();
		if (src_node->value == src && dst_node->value == dst && it->weight == w) {
			return false;
		}
	}
	
	// housekeeping TODO can we initiate them as shared_ptrs
	std::weak_ptr<gdwg::Graph<N, E>::Node> src_node;
	std::weak_ptr<gdwg::Graph<N, E>::Node> dst_node;

	// locating source and destination nodes_
	for (const auto &it : this->nodes_) {
		if (it->value == src)
			src_node = it;
	}
	for (const auto &it : this->nodes_) {
		if (it->value == dst)
			dst_node = it;
	}

	// escalating weak_ptrs to shared_ptrs
	std::shared_ptr<Node> src_sptr = src_node.lock();
	std::shared_ptr<Node> dst_sptr = dst_node.lock();

	// creating edge
	auto edge = std::make_shared<Edge>(src_sptr, dst_sptr, w);
	this->edges_.insert(edge);

	// adding edges_ to in_edges_ and out_edges_ of dst/src nodes_
	dst_sptr->in_edges_.push_back(edge);
	src_sptr->out_edges_.push_back(edge);

	// returns true if successfully added
	return true;
}

/* Delete node */
template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N &del) noexcept { 
	// Delete note and all associated incoming/outgoing edges_
	std::shared_ptr<gdwg::Graph<N, E>::Node> del_node = nullptr;

	// Check if in list of nodes_
	for (const auto &it : this->nodes_) {
		if (it->value == del) {
			del_node = it;	
		}
	}

	// If node not found
	if (del_node == nullptr) {
		return false;
	}

	for (const auto &it : this->edges_) {
		std::cout << it->src.lock()->value << "\n";
		if (it->src.lock()->value == del || it->dst.lock()->value == del) {
			this->erase(it->src.lock()->value, it->dst.lock()->value, it->weight);
			std::cout << "nyes\n";
		}
	}

	nodes_.erase(del_node);
	return true;
}

/* Replace node */
template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N &old_data, const N& new_data)  { 
	if (this->IsNode(new_data) == true)
		return false;
	for (const auto &it : this->nodes_) {
		if (it->value == old_data) {
			it->value = new_data;
		}
	}

	return true;
}

/* MergeReplace */
template <typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
	const auto &old_node = NodeExists(oldData);
	const auto &new_node = NodeExists(newData);

	// replace old_node with new_node in node->out_edges_ and node->in_edges_
	for (const auto &it : old_node->out_edges_) {
		// set the src of the edge to new_node
		it.lock()->src = new_node;
		// add weak pointers to new_node->out_edges_
		new_node->out_edges_.push_back(it);
	}

	for (const auto &it : old_node->in_edges_) {
		// set the dst of the edge to new_node
		it.lock()->dst = new_node;
		// add weak pointers to new_node->in_edges_
		new_node->in_edges_.push_back(it);
	}

	// clean all of old_node;
	this->DeleteNode(oldData);
}

/* IsNode */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {
	// loop through nodes_ in (this)
	for (const auto &it : this->nodes_) {
		if (it->value == val) {
			return true;
		}
	}
	return false;
}

/* GetNodes */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const {
  std::vector<N> ret_nodes_;
  for (const auto& node : this->nodes_) {
    ret_nodes_.push_back(node->value);
  }

  return ret_nodes_;
}


/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
    edges_.clear();
    nodes_.clear();
}

/*
 * Return all nodes_ connected by outgoing edges_ to a given node
 */ 
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {
	const auto &node = NodeExists(src);
    std::vector<N> ret_nodes_ = {};

	if (node == nullptr) {
		throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
	}

	for (const auto &out_edge : node.out_edges_) {
		ret_nodes_.push_back(out_edge->lock()->dst->lock());
	}

	return ret_nodes_;
}
 
// GetWeights
template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
  	const auto &src_node = NodeExists(src);
  	const auto &dst_node = NodeExists(dst);
  	std::vector<E> ret_edges_ = {};


	if (src_node == nullptr || dst_node == nullptr) {
		throw std::out_of_range("Cannot call Graph::GetWeights if src doesn't exist in the graph");
	}

	for (const auto &out_edge : src_node.out_edges_) {
		ret_edges_.push_back(out_edge->lock());
	}

	return ret_edges_;
}

/*
 * Find a given edge in the graph.
 */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& wt) {
	const auto &src_node = NodeExists(src);
	const auto &dst_node = NodeExists(dst);
	if (src_node == nullptr || dst_node == nullptr) {
		return edges_.end();
	}

	for (const auto it = edges_.begin(); it != edges_.end; ++it) {
		if (it->lock()->dst->lock()->value == dst 
			&& it->lock()->src->lock()->value == src 
			&& it->lock()->weight == wt) {
				return it;
		}
	}

	/* if we found nothing, return the end */
	return edges_.end();
}

/* erase(edge) */
template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
	// return false if edge not found
	bool found = false;
	for (const auto &edge : this->edges_) {
		auto src_node = edge->src.lock();
		auto dst_node = edge->dst.lock();

		// return false if edge not found
		// if edge(src, dst, w) exists
		if (src_node->value == src && dst_node->value == dst && edge->weight == w) {
			found = true;
			for (auto it = src_node->out_edges_.begin(); it != src_node->out_edges_.end(); ++it) {
				auto out_edge_dst = it->lock()->dst.lock();
				if (out_edge_dst->value == dst && it->lock()->weight == w) {
					src_node->out_edges_.erase(it);
					break;
				}
			}

			for (auto it = dst_node->in_edges_.begin(); it != dst_node->in_edges_.end(); ++it) {
				auto in_edge_src = it->lock()->src.lock();
				if (in_edge_src->value == src && it->lock()->weight == w) {
					dst_node->in_edges_.erase(it);
					break;
				}
			}
			
			// removing the break will cause the loop to segfault because capacity
			// is greater than size and the end() iterator is not adjusted it's not 
			// a huge problem because edges_ are unique, so a break can be used
		}
	}
	
	return found;
}

/*************
 * ITERATORS *
 *************/
 
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() {

}
