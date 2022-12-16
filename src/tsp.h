#pragma once

#include <vector>
#include <set>

#include "graph.h"

template <typename T,
          typename Extend =
              typename std::enable_if<std::is_base_of<Vertex, T>::value>::type>
class TSP {
 public:
  // Create a TSP Object with respect to a given graph.
  TSP(Graph<T> graph);

  // Get the Hamiltonian path starting and ending from index 0 of the graph.
  std::vector<typename Graph<T>::Edge> getHamiltonianPath();

 private:
  Graph<T> graph_;

  // Used in initialization. The graph passed into the constructor requires
  // two edges in both directions for each pair in the graph.
  bool _validateGraph() const;

  // Used in getHamiltonianPath. Returns a vector of sets, representing all
  // possible combinations of choosing r elements in numbers 0 ~ n-1.
  std::vector<std::set<size_t>> _combinations(size_t n, size_t r) const;
};

#include "tsp.hpp"