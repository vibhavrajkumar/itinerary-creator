#pragma once

#include <vector>

#include "graph.h"

template <typename T,
          typename Extend =
              typename std::enable_if<std::is_base_of<Vertex, T>::value>::type>
class Dijkstra {
 // See dijkstra.hpp for detailed documentation  
 public:
  Dijkstra(Graph<T> graph) { graph_ = graph; };
  Graph<T>& getGraph() { return graph_; }
  std::vector<typename Graph<T>::Edge> getShortestPath(
      const T* startNode, const T* endNode);

 private:
  Graph<T> graph_;
};

#include "dijkstra.hpp"