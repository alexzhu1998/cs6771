// #include "assignments/dg/graph.h" // probably not needed... 

/*****************
 * CONSTRUCTORS
 *****************/

/* Copy constructor for graph */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const Graph&) {
	// this.nodes = copy nodes
	// this.edges = copy edges
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



// /* Delete node */
// void gdwg::Graph<N, E>::DeleteNode(const N &node) noexcept { 
// 	/* Check if in list of nodes */

// 	/* Delete */
// }

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
void gdwg::Graph<N, E>::Clear() {
    edges.clear();
    nodes.clear();
}
