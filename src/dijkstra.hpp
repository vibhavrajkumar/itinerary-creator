#include <queue>

template <typename T, typename Extend>
std::vector<typename Graph<T>::Edge> Dijkstra<T, Extend>::getShortestPath(
    const T* startNode, const T* endNode) {
  // get size of graph to initialize vectors
  size_t graph_size = graph_.size();

  // declare priority queue to be used in Dijkstra traversal
  std::priority_queue<std::pair<size_t, const T*>,
                      std::vector<std::pair<size_t, const T*> >,
                      std::greater<std::pair<size_t, const T*> > >
      q;

  std::vector<bool> visited;
  visited.assign(graph_size, false);
  // initialize vector of parents(storing the parent of each node at an indice)
  std::vector<const typename Graph<T>::Edge*> parents;

  // initialize vector that stores the distance from each node to the start node
  std::vector<int> distances;

  // assign all distances initially to largest possible int value
  distances.assign(graph_size, INT_MAX);
  // push the starting node into the queue with distance 0 (it has 0 distance
  // from itself)
  q.push(std::pair<size_t, const T*>(0, startNode));

  distances.at(graph_.getIndex(startNode->getId())) = 0;

  // assign all the nodes in parents to NULL initially
  parents.assign(graph_size, NULL);
  parents.at(graph_.getIndex(startNode->getId())) = NULL;

  while (!q.empty()) {
    // pop top off the queue, store for processing
    const T* fromNode = q.top().second;
    visited.at(graph_.getIndex(q.top().second->getId())) = true;
    q.pop();

    // get all connected edges to current node
    const std::vector<typename Graph<T>::Edge>& connected_edges =
        graph_.getIncidentEdges(fromNode->getId());

    // loop through connected edges
    for (size_t i = 0; i < connected_edges.size(); i++) {
      // get the weight of the given connected node
      int weight = connected_edges.at(i).weight;
      size_t toIdx = graph_.getIndex(connected_edges.at(i).to->getId());

      if (!visited.at(toIdx)) {
        // compare given weight with current weight (initially current weight
        // are all infinity) if larger, than enter conditional statement
        if (distances.at(toIdx) >
            distances.at(graph_.getIndex(fromNode->getId())) + weight) {
          // update current distance with distance from connected node plus the
          // weight of the edge
          distances.at(toIdx) =
              distances.at(graph_.getIndex(fromNode->getId())) + weight;
          // push connected node into the queue
          q.push(std::pair<size_t, const T*>(distances.at(toIdx),
                                             graph_.getNodes().at(toIdx)));

          // update the parent of the connected node as the current node
          const typename Graph<T>::Edge* test = &connected_edges.at(i);
          parents.at(toIdx) = &connected_edges.at(i);
        }
      }
    }
  }

  // backtracking using parents vector to go from endpoint back to startpoint
  const T* curr_node = endNode;
  std::vector<typename Graph<T>::Edge> ret;
  while (curr_node->getId() != startNode->getId()) {
    const typename Graph<T>::Edge* curr_edge =
        parents.at(graph_.getIndex(curr_node->getId()));
    if (curr_edge == NULL) return std::vector<typename Graph<T>::Edge>();
    ret.push_back(*curr_edge);
    curr_node = curr_edge->from;
  }

  // reverse the return vector (after the while loop the vector gives a path
  // from end to start) we want a path from start to end, so the reverse is
  // neccessary
  std::reverse(ret.begin(), ret.end());

  return ret;
}