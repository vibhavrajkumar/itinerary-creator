#include "../cs225/catch/catch.hpp"
#include "../src/dijkstra.h"
#include "tests_helper.hpp"

TEST_CASE("Dijkstra::Test Case 1", "[Dijkstra]") {
  //Normal Dijkstra test case

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));

  graph.addEdge("1", "2", 2);
  graph.addEdge("2", "3", 2);
  graph.addEdge("2", "4", 1);
  graph.addEdge("1", "3", 5);
  graph.addEdge("3", "4", 3);
  graph.addEdge("1", "4", 4);

  Dijkstra<IntVertex> d(graph);

  // Node 1 to 4. 1 -2-> 2; 2 -1-> 4.
  std::vector<std::vector<int>> path = {{1, 2, 2}, {2, 4, 1}};
  matchVectorComplex(d.getShortestPath(&graph.getNode("1"), &graph.getNode("4")), path, cmpVectorEdges);
  // Node 1 to 3. 1 -2-> 2; 2 -2-> 3.
  path = {{1, 2, 2}, {2, 3, 2}};
  matchVectorComplex(d.getShortestPath(&graph.getNode("1"), &graph.getNode("3")), path, cmpVectorEdges);
}

TEST_CASE("Dijkstra::Test Case 2", "[Dijkstra]") {
  //Large Dijkstra test case

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(6));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(0));
  graph.addNode(IntVertex(4));

  graph.addEdge("2", "0", 4);
  graph.addEdge("2", "5", 5);
  graph.addEdge("0", "1", 2);
  graph.addEdge("0", "3", 1);
  graph.addEdge("1", "4", 10);
  graph.addEdge("1", "3", 3);
  graph.addEdge("3", "2", 2);
  graph.addEdge("3", "5", 8);
  graph.addEdge("3", "6", 4);
  graph.addEdge("3", "4", 2);
  graph.addEdge("4", "6", 6);
  graph.addEdge("6", "5", 1);

  Dijkstra<IntVertex> d(graph);

  // 0 -> 3 -> 6 -> 5.
  std::vector<std::vector<int>> path = {{0, 3, 1}, {3, 6, 4}, {6, 5, 1}};
  matchVectorComplex(d.getShortestPath(&graph.getNode("0"), &graph.getNode("5")), path, cmpVectorEdges);
}

TEST_CASE("Dijkstra::Test Case 3", "[Dijkstra]") {
  //Return path with fewest nodes if 2 paths are the same distance

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(0));
  graph.addNode(IntVertex(4));

  graph.addEdge("0", "4", 10);
  graph.addEdge("0", "1", 7);
  graph.addEdge("1", "4", 3);
  graph.addEdge("1", "2", 2);
  graph.addEdge("2", "0", 1);
  graph.addEdge("0", "3", 2);
  graph.addEdge("4", "3", 2);
  graph.addEdge("3", "4", 9);
  graph.addEdge("4", "2", 3);
  graph.addEdge("4", "0", 10);

  Dijkstra<IntVertex> d(graph);

  // 0 -> 4 instead of 0 -> 1 -> 4. Both length 10
  std::vector<std::vector<int>> path0 = {{0, 4, 10}};
  matchVectorComplex(d.getShortestPath(&graph.getNode("0"), &graph.getNode("4")), path0, cmpVectorEdges);

  // 1 -> 4 -> 3 instead of 1 -> 2 -> 0 -> 3. Both length 5
  std::vector<std::vector<int>> path1 = {{1, 4, 3},{4, 3, 2}};
  matchVectorComplex(d.getShortestPath(&graph.getNode("1"), &graph.getNode("3")), path1, cmpVectorEdges);
}

TEST_CASE("Dijkstra::Test Case 4", "[Dijkstra]") {
  //Return empty vector is no path exists

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(4));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(0));
  graph.addNode(IntVertex(1));

  graph.addEdge("0", "1", 1);
  graph.addEdge("2", "1", 3);
  graph.addEdge("3", "4", 4);
  graph.addEdge("4", "0", 3);

  Dijkstra<IntVertex> d(graph);

  std::vector<std::vector<int>> path = {};

  matchVectorComplex(d.getShortestPath(&graph.getNode("0"), &graph.getNode("2")), path, cmpVectorEdges);

  matchVectorComplex(d.getShortestPath(&graph.getNode("1"), &graph.getNode("4")), path, cmpVectorEdges);

  matchVectorComplex(d.getShortestPath(&graph.getNode("2"), &graph.getNode("5")), path, cmpVectorEdges);
}

TEST_CASE("Dijkstra::Test Case 5", "[Dijkstra]") {
  //Throws error is invalid node is passed in

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(0));
  graph.addNode(IntVertex(4));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(1));

  graph.addEdge("0", "1", 4);
  graph.addEdge("2", "1", 3);
  graph.addEdge("3", "4", 8);
  graph.addEdge("4", "0", 3);
  graph.addEdge("1", "2", 2);
  graph.addEdge("1", "4", 3);
  graph.addEdge("3", "0", 9);
  graph.addEdge("0", "4", 5);

  Dijkstra<IntVertex> d(graph);

  REQUIRE_THROWS_AS(d.getShortestPath(&graph.getNode("0"), &graph.getNode("5")),std::runtime_error);

  REQUIRE_THROWS_AS(d.getShortestPath(&graph.getNode("-1"), &graph.getNode("3")),std::runtime_error);
}