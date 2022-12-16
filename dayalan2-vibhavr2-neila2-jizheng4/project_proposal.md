# Project Proposal

## Leading Question

Given a blacklist of airports that should not be visited, and a whitelist of destinations that are intended to be in the trip, what is the shortest path of flight?

Sometimes air restrictions, passport issues, COVID issues, bad weather, or other problems will discourage the traveller to go to certain airports in his/her trip. Our program aims to support user-defined blacklists of airports. Of course, the user could also choose his/her several destinations and input them into our program. The output will be the shortest path available for the traveller's flight.

## Data Acquisition and Processing

We will be using the airport/airline data from [OpenFlights](https://openflights.org/data.html).

Both datasets come in CSV format. The airport dataset (`airports.dat`) is about 1.1MB, storing coordinates, 3-letter/4-letter codes, airport names, and other information on one line for each airport. This will be the vertices of our graph. The airlines dataset (`routes.dat`) is about 400KB, storing the codes of the two airports it is connecting and other information on oneline for each airline. This will be the edges of our graph. The weight of each edge will be the length of the airline route: every airport has its geological coordinate information in its dataset, and the length of each route can be computed based on the coordinates of the start and ending airports.

Considering OpenFlights is a well-known open-source dataset, the possibility that we have falsified data points is low. However, we will do checks on airport and make sure each airport and each airline has enough information for us to construct the graph. For example, an airport must have its name, coordinates, code; a route must have its start and destination codes.

## Graph Algorithms

The graph will be stored in an adjacency list considering airport/airline graphs have relatively less edges. This will cost a space consuming of `O(|E|)` (number of edges). The lengths of the flights will be calculated and stored as the weights of the edges.

The traversal we choose is BFS. Breadth-first Search can provide great information on airports you can reach in a certain number of flights.

The first algorithm we are using is Dijkstra's shortest path finder algorithm. This will serve as the core of our project finding shortest routes between two particular airports. The time complexity of Dijkstra is worst case `O(|V|^2)`, which can be reduced to `O((|E|+|V|) * log|V|)` using a minHeap. Its space complexity is `O(|V|+|E|)`.

To approach the blacklist problem, we will simply remove all edges into and out of the blacklisted airports before running Dijkstra's algorithm.

To approach the whitelist problem, we will first calculate the shortest paths between every pair of airports in the whitelist. Then we will create a smaller graph with these whitelisted airports as vertices and the best shortest path distance between each pair as edges. This reduces the problem to a Hamiltonian Path problem: finding a shortest path that passes through all vertices once.

For finding Hamiltonian Paths, there are two alternative algorithms. Bellman, Held, and Karp's 1962 Algorithm solves it in time complexity `O(n^2 * 2^n)` and space complexity `O(n * 2^n)`; Björklund's 2010 Algorithm solved it in time complexity `O*(1.657^n)` and polynomial space. We will be using Bellman-Held-Karp since the other one is more sophisticated and has random outputs, which are not ideal for testing purposes. Note that although the algorithms are of exponential runtime, the actual whitelist (i.e. number of nodes, `n`) will be less than 20 airports. We will enforce a limit to the number of airports in the whitelist for user input.

## Timeline (Each bullet point is one week; both teams are working synchronizely)

#### Group 1: Jizheng (Daniel) & Adarsh
- Writing a basic adjacency list data structure
- Reading dataset into graph (using `Airport` class)
- Read Hamiltonian Path algorithms + make decision

===== Mid-project =====

- Implementing Hamiltonian Path
- Whitelisting

#### Group 2: Neil & Vibhav
- Write a class `Airport` & support creating `Airport` instances from `string`s
- Learn Dijkstra's Algorithm
- Implement Dijkstra's Algorithm + Blacklist

===== Mid-project =====

- Unit Tests for blacklist
- Unit Tests for whitelist
