// #include "assignments/dg/graph.h" // probably not needed... 

/*****************
 * CONSTRUCTORS
 *****************/
/*template <typename N, typename E>
std::shared_ptr<Node> gdwg::Graph<N, E>::node_exists(const N& node_name) const{
    for(const auto& node : nodes){
        if(i.get()->val == node_name){
            return node;
        }
    }
    return {};
}*/

/* Copy constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& other) {
	// this.nodes = copy nodes
	for (const auto &it : other.nodes) {
		InsertNode(it->value);
	}

	// this.edges = copy edges
	for (const auto &it : other.edges) {
		auto src_sptr = it->src.lock();
		auto dst_sptr = it->dst.lock();

		auto src_string = src_sptr->value;
		auto dst_string = dst_sptr->value;
		
		InsertEdge(src_string, dst_string, it->weight);
	}
}

/* Move constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>&& other) noexcept {
	// this.nodes = copy nodes
	for (const auto &it : other.nodes) {
		InsertNode(it->value);
	}

	// this.edges = copy edges
	for (const auto &it : other.edges) {
		auto src_sptr = it->src.lock();
		auto dst_sptr = it->dst.lock();

		auto src_string = src_sptr->value;
		auto dst_string = dst_sptr->value;
		
		InsertEdge(src_string, dst_string, it->weight);
	}

	// but delete other afterwards
	other.~Graph();
}

/***********
 * METHODS *
 ***********/
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
	// check if node containing val already exists (return false)
	auto node_list = this->GetNodes();
	if (std::find(node_list.begin(), node_list.end(), val) != node_list.end())
		return false;

	auto ret = nodes.insert(std::make_shared<gdwg::Graph<N, E>::Node>(val));
	return ret.second;
}

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
	
	// housekeeping 
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
bool gdwg::Graph<N, E>::DeleteNode(const N &node) noexcept { 
	/* Check if in list of nodes */
	const auto& found_node = node_exists(node);

	if (found_node == nullptr) {
		return 0;
	}

	for (const auto& out_node : found_node.get()->out_edges) {
		if (!out_node.expired()) {
			edges.erase(out_node.lock());
		}	
	}

	for (const auto& in_node : found_node.get()->in_edges) {
		if (!in_node.expired()) {
			edges.erase(in_node.lock());
		}	
	}

	nodes.erase(found_node);

	return 1;
}

/* Delete node */
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

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {

}

template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
	
}

//template <typename N, typename E>
//const_iterator gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& wt) {
	
//}


/*************
 * ITERATORS *
 *************/

