#pragma once

#include <cmath>
#include <map>
#include <queue>
#include <string>
#include <type_traits>
#include <vector>
#include <functional>
#include <iostream>

#include "vertex.h"

template <typename T, typename Extend = typename std::enable_if<std::is_base_of<Vertex, T>::value>::type>

// Graph class to represent airports as nodes and flight paths as edges
class Graph {
 public:
  Graph();

  //Edge class to represent directional, weighted edges
  class Edge {
   public:
    T* from;
    T* to;
    int weight;

    //Initialized edge
    Edge(T* from, T* to, int weight) : from(from), to(to), weight(weight) {}

    //Checks if edge is equal to other edge
    bool operator==(const Edge& other) const {
      return from->getId() == other.from->getId() && to->getId() == other.to->getId() &&
             std::abs(weight - other.weight) < 0.01;
    }

    //Checks if edge is less than other edge
    bool operator<(const Edge& other) const {
      if (from->getId() != other.from->getId()) return from->getId() < other.from->getId();
      if (to->getId() != other.to->getId()) return to->getId() < other.to->getId();
      return weight < other.weight;
    }

    //Prints out edge
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
      os << "{" << edge.from->getId() << " -> " << edge.to->getId() << ", w: " << edge.weight << "}";
      return os;
    }

    //Checks if edge is not equal to other edge
    bool operator!=(const Edge& other) const{
      return !(*from == *other.from && *to == *other.to
          && std::abs(weight - other.weight) < 0.01);
    }
  };

  //Adds node to graph
  void addNode(T node);

  //Adds directed,weighted edge to graph
  void addEdge(const std::string& from, const std::string& to, int weight);

  //Returns node in graph from string id
  const T& getNode(const std::string& id) const;

  //Returns index of node in vector from string id
  size_t getIndex(const std::string& id) const;

  //Returns a vector of all edges going out of the node from string id
  const std::vector<Edge>& getIncidentEdges(const std::string& id) const;

  //Returns edge between 2 nodes from their string ids
  const Edge& getEdge(const std::string& from, const std::string& to) const;

  //Returns edge between 2 nodes from their indexes
  const Edge& getEdge(size_t fromIdx, size_t toIdx) const;

  //Returns a vector of all nodes in graph
  const std::vector<T*>& getNodes() const;

  //Returns a vector of all edges in graph
  const std::map<std::string, std::vector<Edge>>& getEdges() const;

  //Return number of nodes in graph
  size_t size() const;

  //Iterate through graph with BFS
  std::vector<std::vector<std::string>> BFS();

  //Iterate through graph with BFS given a starting node
  std::vector<std::vector<std::string>> BFS(std::string id);

  //Helper BFS function
  std::vector<std::string> _BFS(std::string id);

  //Returns if traversal visited a node from string id 
  bool didVisit(std::string id);

  //Removes node given string id and returns if node was able to be removed
  bool removeNode(std::string id); 


 private:
  std::map<std::string, bool> visited;
  
  std::map<std::string, T> nodes_;
  std::map<std::string, std::vector<Edge>> edges_;
  std::map<std::string, int> indices_;
  std::vector<T*> nodes_vector_;

  T& _getNode(const std::string& id);

  void decrement(int i); 
};

#include "graph.hpp"