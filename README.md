# Smart Memory-Based Graph Navigator

A C++ mini project that demonstrates the practical implementation of Graph Data Structures, Design and Analysis of Algorithms (DAA), Object-Oriented Programming (OOP), Dynamic Memory Management, and File Handling.

The system models cities as nodes and roads as weighted edges, allowing users to perform route navigation, graph traversal, shortest path analysis, minimum spanning tree generation, and graph persistence through file storage.

---

## Features

### Graph Operations

* Add Location (Node)
* Add Road (Weighted Edge)
* Remove Location
* Remove Road
* Display Complete Graph

### DAA Algorithms

* Dijkstra's Algorithm (Shortest Path)
* Breadth First Search (BFS)
* Depth First Search (DFS)
* Backtracking (Find All Paths)
* Prim's Algorithm (Minimum Spanning Tree)
* Algorithm Performance Comparison

### File Handling

* Save Graph to Text File
* Load Graph from Text File
* Load Sample City Dataset

### Memory Management

* Dynamic Memory Allocation using `new`
* Proper Cleanup using Destructors
* Memory Usage Reporting
* Leak-Free Resource Management

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Standard Template Library (STL)
* Graph Data Structures
* Design and Analysis of Algorithms (DAA)
* File Handling
* Dynamic Memory Management

---

## Project Architecture

```text
GraphEntity (Abstract Base Class)
        ↑
      Node
        ↑
      Graph
        ↑
   PathFinder
        ↑
   FileManager
```

---

## Algorithms Implemented

### 1. Dijkstra's Algorithm

Used to find the shortest path between two locations.

**Time Complexity:** O(E log V)

---

### 2. Breadth First Search (BFS)

Traverses the graph level by level.

**Time Complexity:** O(V + E)

---

### 3. Depth First Search (DFS)

Traverses the graph deeply before backtracking.

**Time Complexity:** O(V + E)

---

### 4. Backtracking

Finds all possible paths between source and destination nodes.

**Time Complexity:** Exponential (Worst Case)

---

### 5. Prim's Algorithm

Constructs a Minimum Spanning Tree (MST) with minimum total cost.

**Time Complexity:** O(V²)

---

## Sample City Network

```text
Delhi -------- Chandigarh -------- Shimla
  |                |
  |                |
Jaipur          Amritsar
  |
  |
Mumbai
  |
Lucknow
  |
Agra
```

---

## Sample Operations

### Add a Location

```cpp
navigator.addNode("Delhi");
```

### Add a Road

```cpp
navigator.addEdge("Delhi", "Chandigarh", 250);
```

### Find Shortest Path

```cpp
navigator.dijkstra("Delhi", "Shimla");
```

### Perform BFS

```cpp
navigator.bfs("Delhi");
```

### Perform DFS

```cpp
navigator.dfs("Delhi");
```

### Generate MST

```cpp
navigator.primsMST();
```

---

## OOP Concepts Demonstrated

### Abstraction

Implemented using the abstract base class:

```cpp
class GraphEntity
```

### Inheritance

```cpp
GraphEntity
   ↓
Node
   ↓
Graph
   ↓
PathFinder
   ↓
FileManager
```

### Polymorphism

```cpp
virtual void display() const;
```

### Encapsulation

Data members are protected within classes.

### Operator Overloading

```cpp
Graph& operator+=(const string& nodeName);
friend ostream& operator<<(ostream&, const Graph&);
```

---

## File Structure

```text
Project
│
├── main.cpp
├── GraphEntity.h
├── Node.h
├── Graph.h
├── PathFinder.h
├── FileManager.h
├── graph.txt
└── README.md
```

---

## Learning Outcomes

This project helped in understanding:

* Graph Data Structures
* Dynamic Memory Allocation
* File Handling
* STL Containers
* DAA Algorithms
* Object-Oriented Programming
* Performance Analysis of Algorithms

---

## Future Enhancements

* GUI Interface
* Real Map Integration
* A* Pathfinding Algorithm
* GPS Navigation Support
* Visualization of Graph Traversals
* Database Connectivity

---

## Author

**Gurudutt Tiwari**

C++ | DSA | Database Management | Software Development

---

## License

This project is developed for educational and academic purposes.
