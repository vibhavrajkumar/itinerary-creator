#pragma once

#include "graph.h"
#include "airport.h"
#include "fileio.h"

#include <iostream>

// The Data class is a singleton lazy initialized. When initialized,
// it will load the dataset of the vertices and edges into a graph.
class Data {
 public:
  // Get the singleton instance of Data.
  static Data& instance();

  // Get a reference to the graph stored in Data.
  Graph<Airport>& getGraph() { return graph_; }

 private:
  Data();
  void _loadData();

  Graph<Airport> graph_;
};