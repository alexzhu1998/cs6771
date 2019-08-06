#include "assignments/dg/graph.h" // probably not needed... 

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
// bool gdwg::Graph<N, E>::IsNode(const N&) {
//   if (nodes.find(N) != 0) {
//     return true;
//   } else {
//     return false;
//   }
// }



template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const {
  std::vector<N> ret_nodes;
  for (const auto& node : this->nodes) {
    ret_nodes.push_back(node.value);
  }

  return nodes;
}

/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() {
    edges.clear();
    nodes.clear();
}

// template <typename N, typename E>
// std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g) {
//   // for (const auto &it : g.nodes) {
//   //   os << it->value << "\n";
//   // }

//   // for each node in the nodes
//   // for (const auto& node : g.Nodes) {
//   //   os << node.value;
//   //   os << " (\n";
//     // for (const auto& out_edge : node) {
//     //   os << "  " << out_edge.dest << " | " << out_edge.weight << "\n";
//     // }
//   //   os << ")\n";
//   // }

//   return os;
// }
