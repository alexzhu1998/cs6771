// #include "assignments/dg/graph.h" // probably not needed... 


/***********
 * METHODS *
 ***********/
// bool gdwg::Graph<N, E>::InsertNode(const N& new_node) {
// 	return nodes.insert(Node(new_node)).second;
// }

// bool gdwg::Graph<N, E>::InsertEdge(const N& new_node) {
//     //return nodes.insert(std::make_shared<Node>(Node{input_node})).second;
// }

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
    ret_nodes.push_back(node.value);
  }

  return nodes;
}

/* GetNode (Gets Single Node) */ 
// Use IsNode first before this function
// template <typename N, typename E>
// std::shared_ptr<typename gdwg::Graph<N, E>::Node> gdwg::Graph<N, E>::GetNode(const N& val) {
//   for (const auto &it : this->nodes) {
//     if (it->value == val) {
//       return it;
//     }
//   }
//   // To keep compiler happy only
//   auto node = std::make_shared<typename gdwg::Graph<N, E>::Node>("NULL");
//   return node;
// }

/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() {
    edges.clear();
    nodes.clear();
}
