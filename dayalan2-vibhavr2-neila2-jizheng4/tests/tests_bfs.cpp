#include "../cs225/catch/catch.hpp"
#include "../src/graph.h"
#include "tests_helper.hpp"

TEST_CASE("BFS::Basic BFS", "[BFS]") {
  //Normal BFS test case

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));

  graph.addEdge("1", "2", 2);
  graph.addEdge("1", "3", 4);
  graph.addEdge("1", "4", 1);
  graph.addEdge("2", "3", 5);
  graph.addEdge("3", "4", 3);
  graph.addEdge("4", "1", 3);

  std::vector<std::vector<std::string>> ans1 = {{"1", "2", "3", "4"}};
  std::vector<std::vector<std::string>> output1 = graph.BFS();

  REQUIRE(output1 == ans1);

  std::vector<std::vector<std::string>> ans2 = {{"2", "3", "4", "1"}};
  std::vector<std::vector<std::string>> output2 = graph.BFS("2");

  REQUIRE(output2 == ans2);
}

TEST_CASE("BFS::Larger BFS", "[BFS]") {
  //Larger BFS test case

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(10));
  graph.addNode(IntVertex(6));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(9));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));
  graph.addNode(IntVertex(12));
  graph.addNode(IntVertex(7));
  graph.addNode(IntVertex(8));
  graph.addNode(IntVertex(11));

  graph.addEdge("2", "3", 2);
  graph.addEdge("3", "5", 4);
  graph.addEdge("3", "6", 1);
  graph.addEdge("3", "7", 5);
  graph.addEdge("1", "4", 2);
  graph.addEdge("4", "1", 2);
  graph.addEdge("5", "8", 8);
  graph.addEdge("5", "9", 3);
  graph.addEdge("8", "1", 4);
  graph.addEdge("8", "2", 1);
  graph.addEdge("8", "10", 3);
  graph.addEdge("11", "10", 4);
  graph.addEdge("10", "12", 3);
  graph.addEdge("10", "2", 3);
  graph.addEdge("12", "11", 2);

  std::vector<std::vector<std::string>> ans1 = {{"2", "3", "5", "6", "7", "8", "9", "1", "10", "4", "12", "11"}};
  std::vector<std::vector<std::string>> output1 = graph.BFS("2");

  REQUIRE(output1 == ans1);

  std::vector<std::vector<std::string>> ans2 = {{"10", "12", "2", "11", "3", "5", "6", "7", "8", "9", "1", "4"}};
  std::vector<std::vector<std::string>> output2 = graph.BFS("10");

  REQUIRE(output2 == ans2);
}

TEST_CASE("BFS::Multiple paths in disconnected graphs", "[BFS]") {
  //Return multiple paths for each connected component in disconnected graph
  //This way it still traverses all nodes in graph even if nodes are disconnected

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));

  graph.addEdge("1", "2", 2);
  graph.addEdge("2", "1", 4);
  graph.addEdge("3", "4", 1);
  graph.addEdge("4", "3", 5);

  std::vector<std::vector<std::string>> ans1 = {{"1", "2"}, {"3", "4"}};
  std::vector<std::vector<std::string>> output1 = graph.BFS("1");

  REQUIRE(output1 == ans1);

  std::vector<std::vector<std::string>> ans2 = {{"2", "1"}, {"3", "4"}};
  std::vector<std::vector<std::string>> output2 = graph.BFS("2");

  REQUIRE(output2 == ans2);
}

TEST_CASE("BFS::Multiple paths for unreachable nodes", "[BFS]") {
  //Return multiple paths if nodes are unreachable
  //Ex: There is an airport with only airlines going out of it and none going to it

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(6));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));
  graph.addNode(IntVertex(7));

  graph.addEdge("1" ,"2", 3);
  graph.addEdge("1" ,"3", 9);
  graph.addEdge("1" ,"4", 3);
  graph.addEdge("1" ,"5", 1);
  graph.addEdge("6" ,"2", 3);
  graph.addEdge("5" ,"4", 2);
  graph.addEdge("2" ,"3", 6);
  graph.addEdge("3" ,"6", 2);
  graph.addEdge("7", "1", 4);

  std::vector<std::vector<std::string>> ans1 = {{"2", "3", "6"}, {"1", "4", "5"}, {"7"}};
  std::vector<std::vector<std::string>> output1 = graph.BFS("2");

  REQUIRE(output1 == ans1);

  std::vector<std::vector<std::string>> ans2 = {{"6", "2", "3"}, {"1", "4", "5"}, {"7"}};
  std::vector<std::vector<std::string>> output2 = graph.BFS("6");

  REQUIRE(output2 == ans2);
}

TEST_CASE("BFS::Null Graph", "[BFS]") {
  //Return empty vector on null graph
  Graph<IntVertex> graph;

  std::vector<std::vector<std::string>> ans1 = {};
  std::vector<std::vector<std::string>> output1 = graph.BFS();

  REQUIRE(output1 == ans1);
}

TEST_CASE("BFS::Invlaid Nodes", "[BFS]") {
  //Throws error is invalid node is passed in

  Graph<IntVertex> graph;
  graph.addNode(IntVertex(6));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));
  graph.addNode(IntVertex(5));
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(4));
  graph.addNode(IntVertex(7));

  graph.addEdge("1" ,"2", 3);
  graph.addEdge("1" ,"3", 9);
  graph.addEdge("1" ,"4", 3);
  graph.addEdge("1" ,"5", 1);
  graph.addEdge("6" ,"2", 3);
  graph.addEdge("5" ,"4", 2);
  graph.addEdge("2" ,"3", 6);
  graph.addEdge("3" ,"6", 2);
  graph.addEdge("7", "1", 4);

  REQUIRE_THROWS_AS(graph.BFS("8"),std::runtime_error);
  REQUIRE_THROWS_AS(graph.BFS("he"),std::runtime_error);
  REQUIRE_THROWS_AS(graph.BFS("-1"),std::runtime_error);
}