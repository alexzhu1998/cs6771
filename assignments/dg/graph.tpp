#include "assignments/dg/graph.h" // probably not needed... 

/***********
 * METHODS *
 ***********/
bool gdwg::Graph<N, E>::addNode(const N& new_node) {
	return nodes.insert(Node(new_node)).second;
}

bool gdwg::Graph<N, E>::addEdge(const N& new_node) {
    //return nodes.insert(std::make_shared<Node>(Node{input_node})).second;
}

/* Delete node */
void gdwg::Graph<N, E>::deleteNode(const N &node) noexcept { 
	/* Check if in list of nodes */

	/* Delete */
}

/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
    edges.clear();
    nodes.clear();
}