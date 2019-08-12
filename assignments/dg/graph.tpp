/*
 * Advanced C++ (COMP6771) 2019T2 Assignment 2

 * Amri Chamela (z5116701) - a.chamela@student.unsw.edu.au
 * Christopher Shi (z5165244) - christopher.shi@unsw
 *
 * Implementation of graph.h:
 * "A Graph class that provides the implementation and functionality to create and manipulate
 * a directed weighted graph, along with a custom iterator to traverse the edges of the
 * graph."
 *
 */

#include <iterator>
#include <memory>
#include <vector>

/***********
 * HELPERS *
 ***********/

/* Bool if edge exists */
template <typename N, typename E>
bool gdwg::Graph<N, E>::EdgeExists(const N src, const N dst, const E w) const {
	/* check if edge already exists (return false) */
	for (const auto& it : this->edges_) {
		auto src_node = it->src.lock();
		auto dst_node = it->dst.lock();
		if (src_node->value == src && dst_node->value == dst && it->weight == w) {
			return true;
		}
	}
	return false;
}

/* Return pointer to a node */
template <typename N, typename E>
std::shared_ptr<typename gdwg::Graph<N, E>::Node> gdwg::Graph<N, E>::NodeExists(const N& val) const {
	for (const auto& node : nodes_) {
		if (node.get()->value == val) {
			return node;
		}
	}
	return nullptr;
}


/*****************
 * CONSTRUCTORS
 *****************/
/* Constructor iterates over nodes_ and adds them to the graph*/
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator begin,
       typename std::vector<N>::const_iterator end) noexcept{
	for (auto i = begin; i != end; ++i) {
	    this->InsertNode(*i);
	}
}

/* iterator constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(
	typename std::vector<std::tuple<N, N, E>>::const_iterator begin,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end) noexcept {
    for (auto i = begin; i != end; ++i) {
      /* getting the strings from the tuples */
      auto src_string = std::get<0>(*i);
      auto dest_string = std::get<1>(*i);

      /* if nodes_ missing, create them */
      if (this->IsNode(src_string) == false) {
        this->InsertNode(src_string);
      }
      if (this->IsNode(dest_string) == false) {
        this->InsertNode(dest_string);
      }

      this->InsertEdge(std::get<0>(*i), std::get<1>(*i), std::get<2>(*i));
    }
}

/* INITIALISER list constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(std::initializer_list<N> new_nodes_) noexcept {
    for (const auto& it : new_nodes_) {
      this->InsertNode(it);
    }
}

/* Copy constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& other) {
  for (const auto& node : other.nodes_) {
    InsertNode(node->value);
  }

  for (const auto& edge : other.edges_) {
    InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
  }
}

/* Move constructor */
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& other) noexcept {
  for (const auto& node : other.nodes_) {
    InsertNode(node->value);
  }

  for (const auto& edge : other.edges_) {
    InsertEdge(edge->src.lock().get()->value, edge->dst.lock().get()->value, edge->weight);
  }

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
    for (const auto& node : other.nodes_) {
      this->InsertNode(node->value);
    }
    for (const auto& edge : other.edges_) {
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
    for (const auto& node : other.nodes_) {
      this->InsertNode(node->value);
    }
    for (const auto& edge : other.edges_) {
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
  /* raise an exception if src or dst not found in graph */
  if (this->IsNode(src) == false || this->IsNode(dst) == false) {
    throw std::runtime_error(
        "Cannot call Graph::InsertEdge when either src or dst node does not exist");
  }

  /* check if edge already exists (return false) */
  for (const auto& it : this->edges_) {
    auto src_node = it->src.lock();
    auto dst_node = it->dst.lock();
    if (src_node->value == src && dst_node->value == dst && it->weight == w) {
      return false;
    }
  }

  std::weak_ptr<gdwg::Graph<N, E>::Node> src_node;
  std::weak_ptr<gdwg::Graph<N, E>::Node> dst_node;

  /* locating source and destination nodes_ */
  for (const auto& it : this->nodes_) {
    if (it->value == src)
      src_node = it;
  }
  for (const auto& it : this->nodes_) {
    if (it->value == dst)
      dst_node = it;
  }

  /* escalating weak_ptrs to shared_ptrs */
  std::shared_ptr<gdwg::Graph<N, E>::Node> src_sptr = src_node.lock();
  std::shared_ptr<gdwg::Graph<N, E>::Node> dst_sptr = dst_node.lock();

  /* creating edge */
  auto edge = std::make_shared<gdwg::Graph<N, E>::Edge>(src_sptr, dst_sptr, w);
  this->edges_.insert(edge);
	
	/* adding edges_ to in_edges and out_edges of dst/src nodes_ */
  dst_sptr->in_edges.push_back(edge);
  src_sptr->out_edges.push_back(edge);

  /* returns true if successfully added */
  return true;
}

/* Delete node */
template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& del) noexcept {
  /* Delete note and all associated incoming/outgoing edges_ */
  std::shared_ptr<gdwg::Graph<N, E>::Node> del_node = nullptr;

  /* Check if in list of nodes_ */
  for (const auto& it : this->nodes_) {
    if (it->value == del) {
      del_node = it;
    }
  }

  if (del_node == nullptr) {
    return false;
  }

  for (const auto& it : this->edges_) {
    if (it->src.lock()->value == del || it->dst.lock()->value == del) {
      this->erase(it->src.lock()->value, it->dst.lock()->value, it->weight);
    }
  }

  nodes_.erase(del_node);
  return true;
}

/* Replace node */
template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& old_data, const N& new_data) {
  if (this->IsNode(old_data) == false) {
    throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
  }

  /* If no node that contains value oldData can be found */
  if (this->IsNode(new_data) == true) {
    return false;
  }

  for (const auto& it : this->nodes_) {
    if (it->value == old_data) {
      it->value = new_data;
    }
  }

  return true;
}

/* MergeReplace */
template <typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& old_data, const N& new_data) {
  if (this->IsNode(new_data) == false || this->IsNode(old_data) == false) {
    throw std::runtime_error(
        "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
  }

  const auto& old_node = NodeExists(old_data);
  const auto& new_node = NodeExists(new_data);

  /* replace old_node with new_node in node->out_edges and node->in_edges */
  for (const auto& it : old_node->out_edges) {
    if (EdgeExists(new_node->value, it.lock()->dst.lock()->value, it.lock()->weight) == false) {
      /* set the src of the edge to new_node */
      it.lock()->src = new_node;
      /* add weak pointers to new_node->out_edges */
      new_node->out_edges.push_back(it);
    }
  }

  for (const auto& it : old_node->in_edges) {
    if (EdgeExists(it.lock()->src.lock()->value, new_node->value, it.lock()->weight) == false) {
      /* set the dst of the edge to new_node */
      it.lock()->dst = new_node;
      /* add weak pointers to new_node->in_edges */
      new_node->in_edges.push_back(it);
    }
  }

  /* clean all of old_node; */
  this->DeleteNode(old_data);
}

/* Clear/delete */
template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() noexcept {
  edges_.clear();
  nodes_.clear();
}

/* IsNode */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) const {
  /* loop through nodes_ in (this) */
  for (const auto& it : this->nodes_) {
    if (it->value == val) {
      return true;
    }
  }
  return false;
}

/* Determine if two nodes are connected */
template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) const {
  /* throw exception if one of the given nodes doesn't exist */
  if (this->IsNode(src) == false || this->IsNode(dst) == false) {
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  /* find a match in the src node's outgoing edges */
  const auto& src_node = NodeExists(src);
  for (const auto& edges : src_node->out_edges) {
    if (edges.lock()->dst.lock()->value == dst) {
      return true;
    }
  }

  return false;
}

/* Get all nodes in graph */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const {
  std::vector<N> ret_nodes_;
  for (const auto& node : this->nodes_) {
    ret_nodes_.push_back(node->value);
  }

  return ret_nodes_;
}

/* Return all nodes_ connected by outgoing edges_ to a given node */
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) const {
  const auto& node = NodeExists(src);
  std::vector<N> ret_nodes_ = {};

  /* Throw exception if src not in graph */
  if (node == nullptr) {
    throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }

  for (const auto& out_edge : node->out_edges) {
    ret_nodes_.push_back(out_edge.lock()->dst.lock()->value);
  }

  return ret_nodes_;
}

/*
 * Get weights of edges between two nodes
 */
template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) const {
  const auto& src_node = NodeExists(src);
  const auto& dst_node = NodeExists(dst);
  std::vector<E> ret_edges_ = {};

  /* throw exception if src doesn't exist or dst */
  if (src_node == nullptr || dst_node == nullptr) {
    throw std::out_of_range(
        "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
  }

  /* Retreieve edges and return */
  for (const auto& out_edge : src_node->out_edges) {
    ret_edges_.push_back(out_edge.lock()->weight);
  }

  return ret_edges_;
}

/*
 * Find a given edge in the graph.
 */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& wt) {
  const auto& src_node = NodeExists(src);
  const auto& dst_node = NodeExists(dst);
  if (src_node == nullptr || dst_node == nullptr) {
    return end();
  }

  for (auto it = this->edges_.begin(); it != this->edges_.end(); ++it) {
    if ((*it)->dst.lock()->value == dst && (*it)->src.lock()->value == src && (*it)->weight == wt) {
      return {it};
    }
  }

  /* if we found nothing, return the end */
  return end();
}

/* erase(edge) */
template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
  /* return false if edge not found */
  bool found = false;
  for (const auto& edge : this->edges_) {
    auto src_node = edge->src.lock();
    auto dst_node = edge->dst.lock();

    /* if edge(src, dst, w) exists */
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

      /* removing the break will cause the loop to segfault because capacity
       * is greater than size and the end() iterator is not adjusted it's not
       * a huge problem because edges_ are unique, so a break can be used */
    }
  }

  return found;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::erase(typename gdwg::Graph<N, E>::const_iterator it) {
  const auto& [src, dst, weight] = *it;

  typename gdwg::Graph<N, E>::const_iterator ret_val = this->edges_.begin();
  for (auto edge = this->edges_.begin(); edge != this->edges_.end(); ++edge) {
    if ((*edge)->src.lock()->value == src && (*edge)->dst.lock()->value == dst &&
        (*edge)->weight == weight) {
      /* record next */
      ++edge;
      ret_val = edge;
      break;
    }
  }

  /* implementation is a wrapper around bool erase */
  if (this->erase(src, dst, weight) == true) {
    return ret_val;
  } else {
    return end();
  }
}

/*************
 * ITERATORS *
 *************/

/* * operator */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator::reference gdwg::Graph<N, E>::const_iterator::
operator*() const noexcept {
  return {(*edge_)->src.lock()->value, (*edge_)->dst.lock()->value, (*edge_)->weight};
}

/* cbegin() */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() noexcept{
  auto begin = this->edges_.begin();
  return {begin};
}

/* cend() */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() noexcept{
  auto end = (this->edges_.end());
  return {end};
}

/* ++ */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::
operator++() noexcept {
  ++edge_;
  return *this;
}

/* -- */
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::
operator--() noexcept {
  --edge_;
  return *this;
}
