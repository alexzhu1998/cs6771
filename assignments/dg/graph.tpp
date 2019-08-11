// #include "assignments/dg/graph.h" // probably not needed... 

/*****************
 * CONSTRUCTORS
 *****************/

/* Copy constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& other) {
	// this.nodes = copy nodes
	for (const auto &node : other.nodes) {
		InsertNode(node->value);
	}

	// this.edges = copy edges
	for (const auto &edge : other.edges) {
		InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
	}
}

/* Move constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& other) noexcept {
	// this.nodes = copy nodes
	for (const auto &node : other.nodes) {
		InsertNode(node->value);
	}

	// this.edges = copy edges
	for (const auto &edge : other.edges) {
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
			for (const auto &node : other.nodes) {
				this->InsertNode(node->value);
			}
			for (const auto &edge : other.edges) {
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
			for (const auto & node : other.nodes) {
				this->InsertNode(node->value);
			}
			for (const auto & edge : other.edges) {
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

	auto ret = nodes.insert(std::make_shared<gdwg::Graph<N, E>::Node>(val));
	return ret.second;
}

/* InsertEdge */
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
	// raise an exception if src or dst not found in graph
	// THIS FUNCTION DOES NOT CREATE NODES 

	// check if edge already exists (return false)
	for (const auto &it : this->edges) {
		auto src_node = it->src.lock();
		auto dst_node = it->dst.lock();
		if (src_node->value == src && dst_node->value == dst && it->weight == w) {
			return false;
		}
	}
	
	// housekeeping TODO can we initiate them as shared_ptrs
	std::weak_ptr<gdwg::Graph<N, E>::Node> src_node;
	std::weak_ptr<gdwg::Graph<N, E>::Node> dst_node;

	// locating source and destination nodes
	for (const auto &it : this->nodes) {
		if (it->value == src)
			src_node = it;
	}
	for (const auto &it : this->nodes) {
		if (it->value == dst)
			dst_node = it;
	}

	// escalating weak_ptrs to shared_ptrs
	std::shared_ptr<Node> src_sptr = src_node.lock();
	std::shared_ptr<Node> dst_sptr = dst_node.lock();

	// creating edge
	auto edge = std::make_shared<Edge>(src_sptr, dst_sptr, w);
	this->edges.insert(edge);

	// adding edges to in_edges and out_edges of dst/src nodes
	dst_sptr->in_edges.push_back(edge);
	src_sptr->out_edges.push_back(edge);

	// returns true if successfully added
	return true;
}

/* Delete node */
template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N &del) noexcept { 
	// Delete note and all associated incoming/outgoing edges
	std::shared_ptr<gdwg::Graph<N, E>::Node> del_node = nullptr;

	// Check if in list of nodes
	for (const auto &it : this->nodes) {
		if (it->value == del) {
			del_node = it;	
		}
	}

	// If node not found
	if (del_node == nullptr) {
		return false;
	}

	for (const auto &it : this->edges) {
		std::cout << it->src.lock()->value << "\n";
		if (it->src.lock()->value == del || it->dst.lock()->value == del) {
			this->erase(it->src.lock()->value, it->dst.lock()->value, it->weight);
			std::cout << "nyes\n";
		}
	}

	nodes.erase(del_node);
	return true;
}

/* Replace node */
// TODOS
template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N &old_data, const N& new_data)  { 
	/* Check if in list of nodes */
	const auto& old_node = node_exists(old_data);

	if (old_node == nullptr) {
		throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
	}

	/* Cannot replace is data already exists */
	const auto& new_node = node_exists(new_data);
	if (new_node != nullptr) {
		return false;
	}

	// TODO: ERASE OLD EDGES AND ADD TO NEW NODE
	nodes.erase(old_node);

	/* Delete */
	return 1;
}

/* IsNode */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {
	// loop through nodes in (this)
	for (const auto &it : this->nodes) {
		if (it->value == val) {
			return true;
		}
	}
	return false;
}

/* GetNodes */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const {
  std::vector<N> ret_nodes;
  for (const auto& node : this->nodes) {
    ret_nodes.push_back(node->value);
  }

  return ret_nodes;
}


/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
    edges.clear();
    nodes.clear();
}

/*
 * Return all nodes connected by outgoing edges to a given node
 */ 
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {
	const auto &node = node_exists(src);
    std::vector<N> ret_nodes = {};

	if (node == nullptr) {
		throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
	}

	for (const auto &out_edge : node.out_edges) {
		ret_nodes.push_back(out_edge->lock()->dst->lock());
	}

	return ret_nodes;
}
 
template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
  	const auto &src_node = node_exists(src);
  	const auto &dst_node = node_exists(dst);
  	std::vector<E> ret_edges = {};


	if (src_node == nullptr || dst_node == nullptr) {
		throw std::out_of_range("Cannot call Graph::GetWeights if src doesn't exist in the graph");
	}

	for (const auto &out_edge : src_node.out_edges) {
		ret_edges.push_back(out_edge->lock());
	}

	return ret_edges;
}

/*
 * Find a given edge in the graph.
 */
// template <typename N, typename E>
// const_iterator gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& wt) {
//   
// }

/* erase(edge) */
template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
	// return false if edge not found
	bool found = false;
	for (const auto &edge : this->edges) {
		auto src_node = edge->src.lock();
		auto dst_node = edge->dst.lock();

				// if edge(src, dst, w) exists
		if (src_node->value == src && dst_node->value == dst && edge->weight == w) {
			found = true;
			for (auto it = src_node->out_edges.begin(); it != src_node->out_edges.end(); ++it) {
				auto out_edge_dst = it->lock()->dst.lock();
				if (out_edge_dst->value == dst && it->lock()->weight == w) {
					src_node->out_edges.erase(it);
					break;
				}
			}

			for (auto it = dst_node->in_edges.begin(); it != dst_node->in_edges.end(); ++it) {
				auto in_edge_src = it->lock()->src.lock();
				if (in_edge_src->value == src && it->lock()->weight == w) {
					dst_node->in_edges.erase(it);
					break;
				}
			}
			
			// removing the break will cause the loop to segfault because capacity
			// is greater than size and the end() iterator is not adjusted it's not 
			// a huge problem because edges are unique, so a break can be used
		}
	}
	
	return found;
}

/*************
 * ITERATORS *
 *************/

