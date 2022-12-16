# Meeting Log

## Mar 28 (Monday): Allocation of Work

This meeting will be dividing up and allocating work of the project. For the next few weeks, there is a mid-week progress track in Discord group (also recorded in this file), and there is a weekly meeting on every Monday 19:30.

#### Group 1: Jizheng (Daniel) & Adarsh
- Writing a basic adjacency list data structure
- Reading dataset into graph (using `Airport` class)
- Read Hamiltonian Path algorithms + make decision
===== Mid-project =====
- Implementing Hamiltonian Path
- Whitelisting
- Testing and final fixes

#### Group 2: Neil & Vibhav
- Write a class `Airport` & support creating `Airport` instances from `string`s
- Learn Dijkstra's Algorithm
- Implement Dijkstra's Algorithm + Blacklist
===== Mid-project =====
- Unit Tests for blacklist
- Unit Tests for whitelist
- Testing and final fixes

## Apr 4 (Monday)

#### Meeting Tasks
- Fixed issue in proposal
- Reviewed each other's progress
- Delegated tasks for next week

#### Progress Tracking
- Group 1: Finished adjacency list data structure
- Group 2: Finished Dijkstra's Algorithm research

#### Next Steps
- Group 1: Fix problem in catch2 so that we can write tests; reading dataset into graph + tests
- Group 2: Finish `Airport` class + tests (constructor taking in a string with format of the dataset, calculate distance based on coordinates)

## Apr 12 (Tuesday)

#### Meeting Tasks
- Reviewed each other's progress
- Delegated tasks for next week
- Identified areas that need to be completed before midpoint

#### Progress Tracking
- Group 1: Finished graph class(graph is now directed and weighted), and added tests; looked into file I/O for C++ and wrote structure for file I/O class

- Group 2: Finished `Airport` class and wrote tests

#### Next Steps
- Group 1: Research Hamiltonian Path's algorithms; meet with group 2 to ensure Dijkstra's is fully functional

- Group 2: Implement Dijkstra's algorithm + Blacklist

- Group 1 & 2: Create/review each other's pull requests thus far so that File I/O and `Airport` can be integrated

## Apr 21 (Thursday)

#### Meeting Tasks
- Collaborative Coding session for 3 hours: Solved `Graph` template implementation problems, discussed on `BFS`, almost finished `Dijkstra` implementation and test cases, ready for mid-project checkin

## Apr 22 (Friday): Mid-project checkin

#### Progress Tracking
- Almost finished Dijkstra's algorithm
- Finished data cleansing

#### Next Steps
- Add more edge cases for Dijkstra's: Unreachable, choosing one path among same distanced paths, etc.
- More tests for data cleansing

## Apr 26 (Tuesday)

#### Next Steps
- Adarsh, Jizheng: Hamiltonian Path, testing, and testing for BFS
- Vibhav, Neil: User interaction, tests for data cleansing, blacklist impl

#### Deadline: Finish project by next Wed, work on deliverables on reading day
- Extra meeting Sunday afternoon 4pm

## May 1 (Sunday)

#### Meeting Tasks
- Collaborative coding session: Finished TSP (Hamiltonian Path) algorithm & wrote 2/5 tests; discussed data cleansing testing, worked on user input

#### Next Steps
- Whitelist (Group 1), Blacklist (Group 2)