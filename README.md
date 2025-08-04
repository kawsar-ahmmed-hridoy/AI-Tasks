# AI Tasks Repository

This repository contains implementations of core Artificial Intelligence algorithms, focusing on search strategies and constraint satisfaction problems. It is designed as an educational resource demonstrating classical uninformed and informed search methods, as well as advanced techniques for solving CSPs.

---

## Repository Structure

### Task1

Classic uninformed search algorithms implemented in C++ for graph traversal and problem solving:

- **BFS.cpp** — Breadth-First Search  
- **DFS.cpp** — Depth-First Search  
- **DLS.cpp** — Depth-Limited Search  
- **IDS.cpp** — Iterative Deepening Search  

### Task2

Advanced algorithms covering Constraint Satisfaction Problems (CSP) and heuristic search:

- **CSP Algorithms/**  
  - `map_coloring_backtracking.cpp` — Backtracking for map coloring problems  
  - `map_coloring_const_prop.cpp` — Constraint Propagation techniques for map coloring  
  - `map_coloring_heuristic.cpp` — Heuristic-enhanced map coloring solver  
  - `n_queen_intelligent_backtracking.cpp` — N-Queens problem solved using intelligent backtracking  

- **a_star_search.cpp** — Implementation of the A* search algorithm for informed pathfinding  

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or higher (e.g., g++, clang++)  
- Basic command-line knowledge to compile and run `.cpp` files

### Running the Code

To compile and run any of the programs, use a command similar to:

```bash
g++ -o program_name source_file.cpp
./program_name
