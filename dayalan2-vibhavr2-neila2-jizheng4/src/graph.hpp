#include <iostream>

#include "graph.h"

template <typename T, typename Extend>
Graph<T, Extend>::Graph() {}

template <typename T, typename Extend>
void Graph<T, Extend>::addNode(T node) {
  // Initalizes node in graph
  std::string id = node.getId();
  nodes_.insert({id, node});
  edges_.insert({id, {}});
  indices_.insert({id, nodes_.size() - 1});
  nodes_vector_.push_back(&_getNode(id));
}

template <typename T, typename Extend>
void Graph<T, Extend>::addEdge(const std::string& from, const std::string& to,
                               int weight) {
  // Make sure nodes exist
  T& nodeFrom = _getNode(from);
  T& nodeTo = _getNode(to);
  // Adds edge
  edges_.find(from)->second.push_back(Edge(&nodeFrom, &nodeTo, weight));
}

// Private helper that returns non const reference of node
template <typename T, typename Extend>
T& Graph<T, Extend>::_getNode(const std::string& id) {
  // Make sure node exists
  auto nodePair = nodes_.find(id);
  if (nodePair == nodes_.end()) {
    throw std::runtime_error("Did not find node for identifier " + id);
  }
  // Returns node
  return nodePair->second;
}

// Public function that returns const reference of node
template <typename T, typename Extend>
const T& Graph<T, Extend>::getNode(const std::string& id) const {
  // Make sure node exists
  auto nodePair = nodes_.find(id);
  if (nodePair == nodes_.end()) {
    throw std::runtime_error("Did not find node for identifier " + id);
  }
  // Returns node
  return nodePair->second;
}

template <typename T, typename Extend>
size_t Graph<T, Extend>::getIndex(const std::string& id) const {
  return indices_.at(id);
}

template <typename T, typename Extend>
const std::vector<typename Graph<T, Extend>::Edge>&
Graph<T, Extend>::getIncidentEdges(const std::string& id) const {
  getNode(id);                     // First make sure node exists
  return edges_.find(id)->second;  // Then fetch incident edges
}

template <typename T, typename Extend>
const typename Graph<T, Extend>::Edge& Graph<T, Extend>::getEdge(
    const std::string& from, const std::string& to) const {
  auto& incident = getIncidentEdges(from);

  auto it =
      std::find_if(incident.begin(), incident.end(), [&](const Edge& edge) {
        return edge.from->getId() == from && edge.to->getId() == to;
      });
  if (it == incident.end()) {
    throw std::runtime_error("Cannot find edge " + from + " -> " + to);
  }
  return *it;
}

template <typename T, typename Extend>
const typename Graph<T, Extend>::Edge& Graph<T, Extend>::getEdge(
    size_t fromIdx, size_t toIdx) const {
  return getEdge(nodes_vector_.at(fromIdx)->getId(),
                 nodes_vector_.at(toIdx)->getId());
}

template <typename T, typename Extend>
const std::vector<T*>& Graph<T, Extend>::getNodes() const {
  return nodes_vector_;
}

template <typename T, typename Extend>
const std::map<std::string, std::vector<typename Graph<T, Extend>::Edge>>&
Graph<T, Extend>::getEdges() const {
  return edges_;
}

template <typename T, typename Extend>
size_t Graph<T, Extend>::size() const {
  return nodes_.size();
}

template <typename T, typename Extend>
std::vector<std::vector<std::string>> Graph<T, Extend>::BFS() {
  visited.clear();
  std::vector<std::vector<std::string>> ret;
  // Iterates through map to make sure all nodes are visited even if nodes are
  // disconnected
  for (typename std::map<std::string, T>::iterator it = nodes_.begin();
       it != nodes_.end(); ++it) {
    // If node isn't visited, perform BFS on node
    if (!didVisit(it->first)) {
      std::vector<std::string> bfsList = _BFS(it->first);
      ret.push_back(bfsList);

      // If all nodes in graph are visited, return path
      if (visited.size() == size()) return ret;
    }
  }
  return ret;
}

template <typename T, typename Extend>
std::vector<std::vector<std::string>> Graph<T, Extend>::BFS(std::string id) {
  visited.clear();
  getNode(id);  // Make sure node exists
  std::vector<std::vector<std::string>> ret;
  // Performs BFS on starting node
  std::vector<std::string> initBFS = _BFS(id);
  ret.push_back(initBFS);
  // If all nodes in graph are visited, return path
  if (visited.size() == size()) return ret;

  // Otherwise iterate through graph and perform BFS until all nodes are visited
  for (typename std::map<std::string, T>::iterator it = nodes_.begin();
       it != nodes_.end(); ++it) {
    if (!didVisit(it->first)) {
      std::vector<std::string> bfsList = _BFS(it->first);
      ret.push_back(bfsList);

      if (visited.size() == size()) return ret;
    }
  }
  return ret;
}

// Basic BFS algorithim on graph from give node
template <typename T, typename Extend>
std::vector<std::string> Graph<T, Extend>::_BFS(std::string id) {
  std::vector<std::string> ret;
  if (didVisit(id)) return ret;

  std::queue<std::string> q;
  q.push(id);
  visited.insert({id, true});

  while (!q.empty()) {
    std::string curr = q.front();
    q.pop();
    ret.push_back(curr);

    std::vector<typename Graph<T, Extend>::Edge> adj_edges =
        getIncidentEdges(curr);
    for (auto elem : adj_edges) {
      std::string next = elem.to->getId();
      if (!didVisit(next)) {
        q.push(next);
        visited.insert({next, true});
      }
    }
  }

  return ret;
}

template <typename T, typename Extend>
bool Graph<T, Extend>::didVisit(std::string id) {
  return (visited.find(id) != visited.end());
}

template <typename T, typename Extend>
bool Graph<T, Extend>::removeNode(std::string id) {
  // verify that graph is not empty
  if (edges_.size() == 0) {
    std::cout << "The dataset is empty" << std::endl;
    return false;
  }

  // verify that edges with id exist
  if (edges_.count(id) > 0) {
    /*
    Loop through edges, if the destination of an edge is not the node to be
    removed, add to a temporary vector and set that temporary vector as the new
    edges vector of the node (will create a new edge vector without the removed
    node)
    */
    for (auto it = edges_.begin(); it != edges_.end(); it++) {
      std::vector<typename Graph<T, Extend>::Edge> new_edges;
      for (size_t i = 0; i < it->second.size(); i++) {
        const T* val = it->second.at(i).to;
        if (*val != getNode(id)) {
          new_edges.push_back(it->second.at(i));
        }
      }

      edges_.at(it->first) = new_edges;
    }
    // remove index in the edges map with the id to be removed
    edges_.erase(edges_.find(id));
    // remove index in the nodes vector and nodes map with the id to be removed
    nodes_.erase(nodes_.find(id));

    // loop through indicies map, and decrement each index after the index to be
    // removed
    for (size_t i = getIndex(id) + 1; i < nodes_vector_.size(); i++) {
      --indices_.at(nodes_vector_.at(i)->getId());
    }

    nodes_vector_.erase(nodes_vector_.begin() + getIndex(id));

    // remove index in the indicies map with the id to be removed
    indices_.erase(indices_.find(id));

    return true;
  } else {
    std::cout << "Could not find node with id: " << id << std::endl;
    return false;
  }
}