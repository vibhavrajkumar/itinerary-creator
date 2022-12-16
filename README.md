# Itinerary Creator Project
CS225 Final Project

## Location

* All code is in `/src` folder
* Tests are in the `/tests` folder
* Data is in the `/data` folder
* [Report](./results.md)

## Running Instructions

Clone the repository

### Running the main executable

1. Run `make` and then `./main` in the command line terminal in the root folder
2. Follow the instructions in the terminal to input airports you would like to visit and not visit
3. The travel path will be printed out for you to enjoy your trip!


### Running Tests

1. Run `make test` and then `./test` in the command line terminal in the root folder
2. All tests that test major components of the code will run and pass
    - **Airport** - Tests for functions of `Airport`, nodes of the graph
        - Successfully initialize Airport using a line from dataset;
        - Aborts when the line misses crucial information (city, wrong coordinates, missing coordinates, missing code, etc.); [Used in Data Cleansing]
        - Correctly calculates the distance between two Airports using coordinates.
    - **Graph Class** - Tests all graph functions to construct and edit graph
        - Adding/Removing nodes and edges;
        - Checking edge cases where node or edge doesn't exist; [Used in Data Cleansing]
        - Gets edges and nodes of graph;
        - Gets edges from specific node.
    - **BFS** - Tests BFS traversal on multiple graphs
        - Small and large sized graphs;
        - Disconnected graph that has multiple connected components;
        - Graphs that have unreachable nodes;
        - Empty graphs;
        - Passing in invalid Nodes.
    - **Dijkstra** - Tests Dijkstra's algorithim on multiple graphs
        - Small and large sized graphs;
        - Graph with multiple best paths, returns best path with least amount of nodes;
        - Graph where no path exists;
        - Passing in invalid nodes.
    - **TSP** - Tests Hamiltonian Path algorithim on multiple graphs
        - Normal and large sized graphs;
        - Really small graphs with only 1 or 2 nodes;
        - Empty graph;
        - Since it is not realistic for the actual world to have two Hamiltonian paths with the same length (unit is in kilometers), no such tests are given.
    - **FileIO** - Tests if the helper class of file input works
        - Delimiting a string with respect to a delimiter character;
        - Getting lines one by one of an file;
        - Properly closes and opens a file;
        - Throws an exception when trying to open an invalid file.

