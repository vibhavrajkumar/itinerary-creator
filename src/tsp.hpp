#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <string>

template <typename T, typename Extend>
TSP<T, Extend>::TSP(Graph<T> graph) {
  graph_ = graph;
  if (!_validateGraph()) {
    throw std::runtime_error("Invalid graph_ input!");
  }
}

template <typename T, typename Extend>
bool TSP<T, Extend>::_validateGraph() const {
  size_t size = graph_.size();
  for (auto* node : graph_.getNodes()) {
    if (graph_.getIncidentEdges(node->getId()).size() != size - 1) {
      return false;
    }
  }
  return true;
}

// https://stackoverflow.com/questions/9430568/generating-combinations-in-c
template <typename T, typename Extend>
std::vector<std::set<size_t>> TSP<T, Extend>::_combinations(size_t n,
                                                            size_t r) const {
  std::vector<std::set<size_t>> ret;
  std::vector<bool> v(n);
  std::fill(v.begin(), v.begin() + r, true);

  do {
    std::set<size_t> combination;
    for (size_t i = 0; i < n; i++) {
      if (v.at(i)) {
        combination.insert(i + 1);
      }
    }
    ret.push_back(combination);
  } while (std::prev_permutation(v.begin(), v.end()));

  return ret;
}

// Pseudocode from https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
template <typename T, typename Extend>
std::vector<typename Graph<T>::Edge> TSP<T, Extend>::getHamiltonianPath() {
  // Initial Conditions
  std::map<std::pair<size_t, std::set<size_t>>, int> dist;
  std::map<std::pair<size_t, std::set<size_t>>, size_t> prev;
  size_t size = graph_.size();
  if(size == 0 || size == 1) return {};
  for (size_t k = 1; k < size; k++) {
    dist.insert({{k, {k}}, graph_.getEdge(0, k).weight});
    prev.insert({{k, {k}}, 0});
  }

  // DP
  for (size_t s = 2; s < size; ++s) {
    for (auto& set : _combinations(size - 1, s)) {
      for (size_t k : set) {
        std::set<size_t> compliment = set;
        compliment.erase(k);
        int& currDist = dist[{k, set}] = INT_MAX;
        size_t& prevNode = prev[{k, set}] = k;
        for (size_t m : compliment) {
          int newDist = dist.at({m, compliment}) + graph_.getEdge(m, k).weight;
          if (newDist < currDist) {
            currDist = newDist;
            prevNode = m;
          }
        }
      }
    }
  }

  // Figure out last step
  int minDist = INT_MAX;
  size_t finalStep = 0;
  std::set<size_t> intermediaries;
  for (size_t k = 1; k < size; ++k) intermediaries.insert(k);
  for (size_t k = 1; k < size; ++k) {
    int totalDist = dist.at({k, intermediaries}) + graph_.getEdge(k, 0).weight;
    if (totalDist < minDist) {
      minDist = totalDist;
      finalStep = k;
    }
  }
  intermediaries.insert(0);
  dist.insert({{0, intermediaries}, minDist});
  prev.insert({{0, intermediaries}, finalStep});

  // Backtrace
  std::vector<typename Graph<T>::Edge> ret;
  size_t currNode = 0;
  do {
    size_t prevNode = prev.at({currNode, intermediaries});
    intermediaries.erase(currNode);
    ret.push_back(graph_.getEdge(prevNode, currNode));
    currNode = prevNode;
  } while (currNode != 0);
  std::reverse(ret.begin(), ret.end());
  return ret;
}