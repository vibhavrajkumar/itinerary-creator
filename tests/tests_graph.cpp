#include "../cs225/catch/catch.hpp"
#include "../src/graph.h"
#include "tests_helper.hpp"

TEST_CASE("Graph::Basic", "[Graph]") {
  //Tests basic graph functions to construct graph
  
  Graph<IntVertex> graph;
  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));

  graph.addEdge("1", "3", 3);
  graph.addEdge("1", "2", 2);
  graph.addEdge("2", "3", 3);
  graph.addEdge("3", "1", 1);

  // addEdge of not existing node
  REQUIRE_THROWS_AS(graph.addEdge("4", "1", 0), std::runtime_error);

  // size
  REQUIRE(graph.size() == 3);

  // getNode
  REQUIRE(graph.getNode("1") == 1);
  REQUIRE(graph.getNode("2") == 2);
  REQUIRE(graph.getNode("3") == 3);
  REQUIRE_THROWS_AS(graph.getNode("4"), std::runtime_error);

  // getIndex
  REQUIRE(graph.getIndex("1") == 0);
  REQUIRE(graph.getIndex("2") == 1);
  REQUIRE(graph.getIndex("3") == 2);

  // getEdges
  std::vector<std::vector<int>> ans;

  ans = {{1, 3, 3}, {1, 2, 2}};
  matchVectorComplex(graph.getIncidentEdges("1"), ans, cmpVectorEdges);
  ans = {{2, 3, 3}};
  matchVectorComplex(graph.getIncidentEdges("2"), ans, cmpVectorEdges);
  ans = {{3, 1, 1}};
  matchVectorComplex(graph.getIncidentEdges("3"), ans, cmpVectorEdges);

  REQUIRE_THROWS_AS(graph.getIncidentEdges("4"), std::runtime_error);

  // getEdge
  REQUIRE(cmpVectorEdges(graph.getEdge("1", "3"), {1, 3, 3}));
  REQUIRE(cmpVectorEdges(graph.getEdge("2", "3"), {2, 3, 3}));
  REQUIRE(cmpVectorEdges(graph.getEdge(0, 2), {1, 3, 3}));
  REQUIRE(cmpVectorEdges(graph.getEdge(1, 2), {2, 3, 3}));
  
  REQUIRE_THROWS_AS(graph.getEdge("3", "2"), std::runtime_error);
  REQUIRE_THROWS_AS(graph.getEdge(2, 1), std::runtime_error);
}

TEST_CASE("Graph::RemoveNode()_Basic", "[Graph]"){
  Graph<IntVertex> graph;

  REQUIRE(graph.removeNode("1") == false); 

  graph.addNode(IntVertex(1));
  graph.addNode(IntVertex(2));
  graph.addNode(IntVertex(3));

  graph.addEdge("1", "3", 3);
  graph.addEdge("1", "2", 2);
  graph.addEdge("2", "3", 3);
  graph.addEdge("3", "1", 1);
  graph.addEdge("3", "2", 2); 

  size_t previous_size_nodes = graph.getNodes().size();
  size_t previous_size_edges = graph.getEdges().size(); 
  int idx = graph.getIndex("3"); 
  REQUIRE(graph.removeNode("7") == false); 

  REQUIRE(graph.removeNode("1") == true); 

  REQUIRE(graph.getNodes().size() == previous_size_nodes - 1); 
  REQUIRE(graph.getEdges().size() == previous_size_edges - 1); 

  std::vector<std::vector<int> > ans = {{3,2,2}}; 

  matchVectorComplex(graph.getIncidentEdges("3"),ans,cmpVectorEdges); 
  REQUIRE(graph.getIndex("3") == idx-1);
}
