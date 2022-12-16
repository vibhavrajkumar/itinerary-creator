# Project Report

## Dijkstra’s Algorithm

#### Description: 

Our implementation of Dijkstra’s algorithm takes in two graph node pointers, one for the intended start point, and one for the intended end point. A min-priority queue created with the std::priority_queue data structure is initialized, as is a vector of booleans tracking visited nodes, a vector of integers tracking the distances of each node from the start, and a vector of Edge pointers that tracks the edge leading from a node to its “parent” node (aka the node that was traversed before it). These vectors are assigned with default values at the size of the graph (the default distance value is the maximum integer value [INT_MAX], the default visited value is false [because no node has been visited yet], and the default parent value is NULL). Initially, the start node is pushed onto the queue, its value in the distance vector is set to 0, and the loop starts, only terminating once the queue is empty. 

In the loop, the top node is popped off and set to visited, and all its neighbors are stored in a vector. Looping through the neighbors vector, the program checks first if the given node is visited. If not, the current distance value for the neighbor node is compared with the distance value of the parent node plus the weight of the edge connecting the two nodes. If it is larger (which it will be if unvisited, as the default distance value is INT_MAX), the distance of the neighbor is updated to be the distance of the parent plus the edge weight. The neighbor is then pushed onto the queue, and its parent is set (the Edge between the neighbor and the node that was initially popped off the queue). This continues until all nodes are processed. 

After this, the program sets a temporary iterating variable to the endNode and loops, traversing through each parent until it reaches the start node. These parents are sequentially pushed into a vector, which is then reversed (since the loop creates a path from end to start), and then returned. In the loop, if a parent node is null and the node is not the startNode, an empty vector is returned immediately as this signifies unconnected components. 

At the end, the return value of our implementation of Dijkstra's algorithm will be a vector of Edges which traces the path from the intended start point to the end point. 


#### Testing: 

We ran several tests on Dijkstra’s algorithm, including general tests verifying the correct path, tests on smaller and larger graphs, a case where there are two correct paths with the same weight but the one with the fewest nodes is returned, a case where no path exists and an empty vector is returned, and an invalid node is passed in. 

#### Complexity: 

The algorithm runs in Time `O( |E| + |V| log(|V|) )` thanks to our usage of `std::priority_queue`, which creates a min heap. 

## TSP/Hamiltonian Cycle Algorithm: Bellman-Held-Karp

#### Description:

1. **Hamiltonian Cycle**: Given a directed, weighted graph, find a shortest cycle that passes through all nodes exactly once.
2. **How to transform the whitelisting problem into a Hamiltonian Path problem**: All the nodes in the whitelist will be added to a "subgraph". For each node `i` and node `j` in the whitelist (`i != j`), a Dijkstra run will be issued to find the shortest path from `i` to `j`, and the path’s weight will be the weight of the edge from `i` to `j` in the subgraph. The subgraph will be then used to calculate the Hamiltonian Path. In total, if the whitelist has `k` nodes, there will be `k*(k-1)` runs of Dijkstra. (Not hand-shaking lemma, since every edge is directed!)
3. **Using Dijkstra instead of Floyed-Warshall**: Although we are running Dijkstra multiple times in order to construct such a "subgraph", the total number of runs is really small since `k` is limited to no more then `10`. `|V|` of our dataset has thousands of valid airports after data cleansing, much larger than `k*(k-1)`.
4. **When one of the edges in the subgraph is not valid**: Sometimes we cannot go from airport `i` to airport `j` considering the flaws of our dataset and the choices of the user's blacklist. In such circumstances we will still add an edge from `i` to `j` in our subgraph with a huge weight (but not as big as `INT_MAX` to avoid overflow). Our TSP Algorithm requires an edge from every node to every other node, and if the final path contains one of these invalid edges, we know that such a path does not exist in real life.
5. **Actual Algorithm**: The algorithm uses dynamic programming and memoization. The memoization term is `g(S, v)`, defined as "the min distance of a path started from vertex `0`, passed all vertices in `S`, and ended at vertex `v`". The dynamic programming equation is thus `g(S, v) = min( g(S\{S_i}, S_i) + d(S_i, v))`, looping from smaller to larger sets of `S` and finding the best node in already memoized distances as the predecessor node to `v`. This is very similar to Dijkstra's distance update. Notice that all possible combinations of `1 ~ k`-sized subsets of `V` will be looped (and the final result is `g(V, 0)`, a path that starts from `0`, passed through all nodes in `V`, and ends at `0`), hence the factor of `2^n` in the time complexity. The code in this project is derived from the pseudocode in the [Wikipedia page of the algorithm](https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm).
6. **Restraints**: `k`, the size of the whitelist (also the size of vertices in the subgraph) is set to be no more than 10, considering both the time and space complexities.

#### Testing:

The testing phase is fairly simple, since 1) the constructor makes sure there exists an edge from any node to any node; and 2) even if there isn’t a valid path from airport A to airport B, an edge with a huge weight will be constructed between A and B. The only edge cases would be TSP for really small graphs. Our test cases contain a basic graph test case, an enlarged graph test case, zero-node graph (throws exception), 1-node graph (throws exception), and 2-nodes graph.

#### Complexity:

The time complexity is `O(n^2 * 2^n)`, and the space complexity is `O(n * 2^n)`.

## BFS Traversal

#### Description: 

This is a fairly straightforward implementation of the BFS traversal on a graph where it returns a 2D vector of the path of the traversal. First we can start at the user defined starting node or a random one in our map to start our BFS traversal. 

Then we call our helper function, `_BFS()`, to then run the standard BFS where the current node is marked as visited by inserting it into a map and then also pushed to the return vector. Afterwards, all neighbors are added to a queue. Then, until the queue is empty, each node is popped off and then marked as visited and pushed to the return vector while all its neighbors are added to the queue. 

When the helper `_BFS()` is done, we check if all the nodes in the graph were visited and if so, we return the path vector. If not, that means there are disconnected components or unreachable nodes in the graph. To compensate for this, we loop through each node in the graph and push its `_BFS()` path to the 2D path vector if it’s not visited. This runs until all nodes are visited and then finally returns the 2D path vector - where each vector is a seperate BFS path run on the graph.

#### Testing:

To cover all test cases of BFS we made sure it ran on small and large graphs correctly by making sure the path vector it returns follows the correct BFS path. Then we tried to cover all edge cases by checking if its path for graphs with disconnected components and/or unreachable nodes matched the correct path vector. Then we checked if it returned an empty vector on an empty graph and also to throw an error if an invalid node is passed in.

## Conclusion

Leading question: Given a blacklist of airports that should not be visited, and a whitelist of destinations that are intended to be in the trip, what is the shortest round trip by distance given the starting point?

Through using the Bellman-Held-Karp TSP/Hamiltonian cycle algorithm, which uses Dijkstra’s in its implementation to find the shortest path between the starting point and each whitelist point, we were able to generate a list of airports and a total distance to represent the shortest round trip. Some discoveries we made about testing were that testing Dijkstra’s on numbers does not pass all the edge cases when testing with airports. Along the way, we ran into problems with Dijkstra’s and generating the whitelist subgraph due to a few insufficient tests. Furthermore, we discovered the usefulness of templated classes to achieve some of our functionality as well as a deeper understanding of const qualifiers. Our algorithm proved to be useful for one of our group members' purposes: Adarsh was able to plan his trip from Chicago, with stops at Cancun and New Delhi! 
