#include "../cs225/catch/catch.hpp"
#include "../src/tsp.h"
#include "tests_helper.hpp"

//Creates graph from distance matrix
void createGraph(Graph<IntVertex>& graph, const std::vector<std::vector<int>>& dist) {
  if(dist.empty()) return;
  
  if (dist.size() != dist.at(0).size()) {
    throw std::runtime_error("Distance matrix not square.");
  }

  int size = static_cast<int>(dist.size());
  for (int i = 0; i < size; ++i) {
    graph.addNode(IntVertex(i));
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i != j) {
        graph.addEdge(std::to_string(j), std::to_string(i), dist.at(i).at(j));
      }
    }
  }
}

//Test cases to test the Traveling Salesman problem using the Hamiltonian Path Algorithm

TEST_CASE("TSP::Basic", "[TSP]") {
  //Basic TSP
  Graph<IntVertex> g;
  std::vector<std::vector<int>> dist = {
    {0, 2, 9, 10},
    {1, 0, 6, 4},
    {15, 7, 0, 8},
    {6, 3, 12, 0}
  };
  createGraph(g, dist);

  TSP<IntVertex> tsp(g);
  // 0 -> 1 -> 3 -> 2 -> 0
  std::vector<std::vector<int>> ans = {
    {0, 1, 1}, {1, 3, 3}, {3, 2, 8}, {2, 0, 9}
  };
  matchVectorComplex(tsp.getHamiltonianPath(), ans, cmpVectorEdges);
}

TEST_CASE("TSP::Larger", "[TSP]") {
  //Larger TSP
  Graph<IntVertex> g;
  std::vector<std::vector<int>> dist = {
        {0, 2451, 713, 1018, 1631, 1374, 2408, 1000, 2571, 875, 1420, 2145, 1972},
        {2451, 0, 1745, 1524, 831, 1240, 959, 2596, 403, 1589, 1374, 357, 579},
        {713, 1745, 0, 355, 920, 803, 1737, 851, 1858, 262, 940, 1453, 1260},
        {1018, 1524, 355, 0, 700, 862, 1395, 1123, 1584, 466, 1056, 1280, 987},
        {1631, 831, 920, 700, 0, 663, 1021, 1769, 949, 796, 879, 586, 371},
        {1374, 1240, 803, 862, 663, 0, 1681, 1551, 1765, 547, 225, 887, 999},
        {2408, 959, 1737, 1395, 1021, 1681, 0, 2493, 678, 1724, 1891, 1114, 701},
        {213, 2596, 851, 1123, 1769, 1551, 2493, 0, 2699, 1038, 1605, 2300, 2099},
        {2571, 403, 1858, 1584, 949, 1765, 678, 2699, 0, 1744, 1645, 653, 600},
        {875, 1589, 262, 466, 796, 547, 1724, 1038, 1744, 0, 679, 1272, 1162},
        {1420, 1374, 940, 1056, 879, 225, 1891, 1605, 1645, 679, 0, 1017, 1200},
        {2145, 357, 1453, 1280, 586, 887, 1114, 2300, 653, 1272, 1017, 0, 504},
        {1972, 579, 1260, 987, 371, 999, 701, 2099, 600, 1162, 1200, 504, 0},
    };
  createGraph(g, dist);

  TSP<IntVertex> tsp(g);
  
  // 0 -> 7 -> 2 -> 3 -> 4 -> 12 -> 6 -> 8 -> 1 -> 11 -> 10 -> 5 -> 9 -> 0
  std::vector<std::vector<int>> ans = {
    {0, 7, 213}, {7, 2, 851}, {2, 3, 355}, {3, 4, 700}, {4, 12, 371}, {12, 6, 701}, {6, 8, 678}, {8, 1, 403}, {1, 11, 357}, {11, 10, 1017}, {10, 5, 225}, {5, 9, 547}, {9, 0, 875}
  };

  matchVectorComplex(tsp.getHamiltonianPath(), ans, cmpVectorEdges);
}

TEST_CASE("TSP::No Path", "[TSP]") {
  //No path exists
  Graph<IntVertex> g;
  std::vector<std::vector<int>> dist = {};
  createGraph(g, dist);

  TSP<IntVertex> tsp(g);
  // //Empty
  std::vector<std::vector<int>> ans = {};
  matchVectorComplex(tsp.getHamiltonianPath(), ans, cmpVectorEdges);
}

TEST_CASE("TSP::Mini 1", "[TSP]") {
  //Really small tsp test case, 1 node in graph
  Graph<IntVertex> g;
  std::vector<std::vector<int>> dist = { {0} };
  createGraph(g, dist);

  TSP<IntVertex> tsp(g);
  //Empty
  std::vector<std::vector<int>> ans = {};
  matchVectorComplex(tsp.getHamiltonianPath(), ans, cmpVectorEdges);
}

TEST_CASE("TSP::Mini 2", "[TSP]") {
  //Really small tsp test case, 2 nodes in graph
  Graph<IntVertex> g;
  std::vector<std::vector<int>> dist = {
    {0, 2,},
    {1, 0}
  };
  createGraph(g, dist);

  TSP<IntVertex> tsp(g);
  // 0 -> 1 -> 0
  std::vector<std::vector<int>> ans = {
    {0, 1, 1}, {1, 0, 2}
  };
  matchVectorComplex(tsp.getHamiltonianPath(), ans, cmpVectorEdges);
}