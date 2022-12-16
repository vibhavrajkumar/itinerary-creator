#pragma once

#include "../cs225/catch/catch.hpp"
#include "../src/vertex.h"
#include "../src/graph.h"

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <string>

template <typename K, typename V>
void matchMap(const std::map<K, V>& output, const std::map<K, V>& ans) {
  REQUIRE(output.size() == ans.size());

  for (auto it = ans.begin(); it != ans.end(); it++) {
    K key = it->first;
    V value = it->second;
    if (output.count(key) <= 0) {
      INFO("Map missing key: " + std::to_string(key));
    }
    REQUIRE(output.count(key) > 0);
    if (output.at(key) != value) {
      INFO("Map at " + std::to_string(key) + " is " + output.at(key) +
           ", but should be " + value);
    }
    REQUIRE(output.at(key) != value);
  }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "Vector: ";
  if (vec.empty()) os << "(empty)";
  else os << vec.at(0);
  for (size_t i = 1; i < vec.size(); i++) {
    os << ", " << vec.at(i);
  }
  return os;
}

template <typename T, typename U, typename Compare>
void matchVectorComplex(const std::vector<T>& output, const std::vector<U>& ans,
                        Compare cmp) {
  REQUIRE(output.size() == ans.size());
  for (size_t i = 0; i < output.size(); i++) {
    if (!cmp(output.at(i), ans.at(i))) {
      INFO("Vector differ at " + std::to_string(i));
      std::cout << "Expected: " << std::endl;
      std::cout << ans << std::endl;
      std::cout << "Actual: " << std::endl;
      std::cout << output << std::endl;
    }
    REQUIRE(cmp(output.at(i), ans.at(i)));
  }
}

template <typename T>
void printPath(std::vector<std::vector<T>> path) {
  std::cout<<""<<std::endl;
  size_t len = path.size();
  for(size_t i=0; i<len; i++) {
    std::cout<<path[i][0]<< " -> ";
  }
  std::cout<<path[len-1][1]<<"\n"<<std::endl;
}

class IntVertex : public Vertex {
 public:
  int data;
  IntVertex(int data) : data(data) {}
  std::string getId() const { return std::to_string(data); }
  bool operator==(const int other) const { return data == other; }
  bool operator==(const IntVertex& other) const { return data == other.data; }
  bool operator!=(const IntVertex& other) const {return !(data == other.data);}
  bool operator!=(const int other) const {return !(data == other);}

};


auto cmpVectorEdges = [](const typename Graph<IntVertex>::Edge& edge,
                         const std::vector<int>& other) {
  if (other.size() != 3) throw std::runtime_error("Test case invalid!");
  return *(edge.from) == other.at(0) && *(edge.to) == other.at(1) &&
          edge.weight == other.at(2);
};
