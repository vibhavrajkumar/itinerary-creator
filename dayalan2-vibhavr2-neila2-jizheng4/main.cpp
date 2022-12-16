#include <algorithm>
#include <iostream>
#include <limits>

#include "src/airport.h"
#include "src/data.h"
#include "src/dijkstra.h"
#include "src/graph.h"
#include "src/tsp.h"

using Edge = typename Graph<Airport>::Edge;

// Copies the graph into a Dijkstra object, and delete the blacklisted nodes
// from graph.
Dijkstra<Airport> blacklist(Graph<Airport>& graph,
                            std::vector<std::string> to_remove) {
  Dijkstra<Airport> dijkstra(graph);
  for (size_t i = 0; i < to_remove.size(); i++) {
    dijkstra.getGraph().removeNode(to_remove.at(i));
  }
  return dijkstra;
}

// Calls n * (n-1) Dijkstra runs on the graph to generate the subgraph
// used for TSP Algorithm.
Graph<Airport> generateWhitelistGraph(
    Dijkstra<Airport>& dijkstra, std::vector<std::string>& whitelist,
    std::map<Edge, std::vector<Edge>>& subroutines) {
  Graph<Airport> subgraph;
  auto& graph = dijkstra.getGraph();
  for (std::string& id : whitelist) {
    subgraph.addNode(graph.getNode(id));
  }
  subroutines.clear();

  for (size_t i = 0; i < whitelist.size(); ++i) {
    const Airport* apI = &graph.getNode(whitelist.at(i));
    for (size_t j = 0; j < whitelist.size(); ++j) {
      if (i == j) continue;
      const Airport* apJ = &graph.getNode(whitelist.at(j));

      std::vector<Edge> subroutine = dijkstra.getShortestPath(apI, apJ);
      int dist = 0;
      for (Edge& edge : subroutine) {
        dist += edge.weight;
      }
      if (dist == 0) dist = INT_MAX / 100;

      subgraph.addEdge(apI->getId(), apJ->getId(), dist);
      subroutines.insert(
          {subgraph.getEdge(apI->getId(), apJ->getId()), subroutine});
    }
  }

  return subgraph;
}

// Gets the Hamiltonian Cycle and translates it into regular routes.
std::vector<Edge> getHamiltonianRoute(
    Graph<Airport>& subgraph, std::map<Edge, std::vector<Edge>>& subroutines) {
  std::vector<Edge> ret;
  TSP<Airport> tsp(subgraph);
  std::vector<Edge> tspPath = tsp.getHamiltonianPath();

  for (Edge& edge : tspPath) {
    std::vector<Edge>& subroutine = subroutines.at(edge);
    if (subroutine.empty())
      throw std::runtime_error(edge.from->getId() + " -> " + edge.to->getId());
    ret.insert(ret.end(), subroutine.begin(), subroutine.end());
  }

  return ret;
}

const std::string kReset = "\033[0m";
const std::string kRed = "\033[31m";
const std::string kYellow = "\033[33m";
const std::string kGreen = "\033[32m";
const std::string kGray = "\033[90m";
const std::string kCyan = "\033[36m";
const std::string kMagenta = "\033[35m";

int main() {
  std::cout << kGray;
  Graph<Airport>& g = Data::instance().getGraph();
  std::cout << kReset;

  std::string start;
  std::string dest;
  std::string whitelist_apt;
  std::string blacklist_apt;
  std::vector<std::string> white_list;
  std::vector<std::string> black_list;

  while (true) {
    std::cout << kYellow << "Enter the ID of the airport you are flying out of: " << kReset;
    std::cin >> start;
    try {
      g.getNode(start);
    } catch (const std::runtime_error& e) {
      std::cout << kRed << "Invalid airport ID." << kReset << std::endl;
      continue;
    }
    break;
  }

  white_list.push_back(start);

  while (true) {
    std::cout << kGreen << "Enter an airport you would like to stop at, at most " << 10 - white_list.size() << " more airports. Type 'done' "
                 "when done entering airports: " << kReset;
    std::cin >> whitelist_apt;
    if (whitelist_apt == "done") {
      if (white_list.size() == 1) {
        std::cout << kRed << "Must have at least one airport in whitelist!" << kReset << std::endl;
        continue;
      }
      break;
    }
    try {
      g.getNode(whitelist_apt);
    } catch (const std::runtime_error& e) {
      std::cout << kRed << "Invalid airport ID." << kReset << std::endl;
      continue;
    }
    if (std::count(white_list.begin(), white_list.end(), whitelist_apt)) {
      std::cout << kRed << "You already added this airport to the whitelist."
                << kReset << std::endl;
      continue;
    }
    white_list.push_back(whitelist_apt);

    if (white_list.size() == 10) {
      std::cout << kRed << "Whitelist full. " << kReset;
      break;
    }
  }

  std::cout << kGreen << "Your whitelist: " << kReset;
  if (white_list.empty()) std::cout << "(empty)";
  for (std::string& s : white_list) {
    std::cout << s << ' ';
  }
  std::cout << std::endl;

  while (true) {
    std::cout << kMagenta << "Enter an airport you would ΝΟΤ like to stop at, at most " << 20 - black_list.size() << " more airports. Type 'done' "
                 "when done entering airports: " << kReset;
    std::cin >> blacklist_apt;
    if (blacklist_apt == "done") {
      break;
    }
    try {
      g.getNode(blacklist_apt);
    } catch (const std::runtime_error& e) {
      std::cout << kRed << "Invalid airport ID." << kReset << std::endl;
      continue;
    }
    if (std::count(black_list.begin(), black_list.end(), blacklist_apt)) {
      std::cout << kRed << "You already added this airport to the blacklist."
                << kReset << std::endl;
      continue;
    }

    if (blacklist_apt == start) {
      std::cout << kRed << "You cannot include the start point in the blacklist."
                << kReset << std::endl;
      continue;
    }

    if (std::count(white_list.begin(), white_list.end(), blacklist_apt)) {
      std::cout
          << kRed << "You cannot have an airport in both the blacklist and whitelist."
          << kReset << std::endl;
      continue;
    }
    black_list.push_back(blacklist_apt);

    if (black_list.size() == 20) {
      std::cout << kRed << "Blacklist full. " << kReset;
      break;
    }
  }

  std::cout << kMagenta << "Your blacklist: " << kReset;
  if (black_list.empty()) std::cout << "(empty)";
  for (std::string& s : black_list) {
    std::cout << s << ' ';
  }
  std::cout << std::endl;

  std::cout << std::endl << kGray << "Calculating path..." << kReset;
  Dijkstra<Airport> dijkstra = blacklist(g, black_list);
  std::map<Edge, std::vector<Edge>> m;
  Graph<Airport> whitelist_graph =
      generateWhitelistGraph(dijkstra, white_list, m);
  std::vector<Edge> route;
  try {
    route = getHamiltonianRoute(whitelist_graph, m);
  } catch (std::runtime_error e) {
    std::cout << kRed
        << "Sorry, we did not find a valid path. Either you included a crucial airport in the blacklist, or the "
           "dataset is not strong enough. Our algorithm tries to find a route of "
        << e.what()
        << ", but failed. "
        << kReset << std::endl;
    return 0;
  }

  size_t distance = 0;
  std::cout << std::endl << kGreen << "Here is your trip: " << kReset << std::endl;
  for (size_t i = 0; i < route.size(); ++i) {
    Edge& edge = route.at(i);
    if (i == 0)
      std::cout << kCyan << edge.from->getName() << kReset << " (" << edge.from->getId()
                << ") -> ";
    if (i == route.size() - 1)
      std::cout << kCyan << edge.to->getName() << kReset << " (" << edge.to->getId() << ")"
                << std::endl;
    else
      std::cout << kCyan << edge.to->getName() << kReset << " (" << edge.to->getId() << ") -> ";
    distance += edge.weight;
  }
  std::cout << "The total distance travelled is: " << distance << std::endl;
  return 0;
}
