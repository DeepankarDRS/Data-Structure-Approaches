# Graph Algorithms — A Practical, In‑Depth README

A field guide to picking (and implementing) the right graph technique for interviews, contests, and real projects.

---

## Quick Navigator

| Problem shape                                        | Go‑to technique                    | Why                                                            |
| ---------------------------------------------------- | ---------------------------------- | -------------------------------------------------------------- |
| Unweighted shortest steps / min moves / levels       | **BFS**                            | Expands in waves; first time you reach a node is minimal edges |
| 2‑coloring / “odd cycle?”                            | **BFS or DFS**                     | Level parity (BFS) or color flipping                           |
| Count components / traverse everything               | **DFS**                            | Linear time, simple recursion/stack                            |
| Ordering tasks with prerequisites (DAG)              | **Topological sort (DFS or Kahn)** | Linearize DAG respecting edges                                 |
| Weighted shortest path (all weights ≥ 0)             | **Dijkstra**                       | Greedy with PQ gives optimal distances                         |
| Has negative edges or need to detect negative cycles | **Bellman–Ford**                   | Edge relaxation up to V−1 times + cycle check                  |
| All‑pairs shortest paths (small V, dense)            | **Floyd–Warshall**                 | Triple‑loop dynamic programming                                |
| Subtree queries / LCA prep on trees                  | **Euler Tour**                     | Flatten tree to array intervals; time‑stamps for ancestry      |

---

## Preliminaries: Modeling Graphs

* **Graph representation**: Use adjacency lists for efficiency; adjacency matrices only when the graph is dense or small.
* **Directed vs. Undirected**: Pay attention to edge directionality when modeling.
* **Edge weights**: Handle carefully with appropriate data types to avoid overflow.
* **Disconnected graphs**: Always consider if multiple components exist.

---

## Breadth‑First Search (BFS)

**When to use**: BFS is the go‑to for problems involving unweighted shortest paths, level‑by‑level exploration, bipartite graph checks, flood fill problems on grids, or spreading processes (e.g., multi‑source problems like infection spread).

**Key property**: BFS explores in layers. The first time you reach a node, you have guaranteed the minimum number of edges from the source.

**Complexity**: Runs in `O(V + E)` time, with `O(V)` space.

**Applications**:

* Shortest path in unweighted graphs.
* Level order traversal of trees.
* Checking bipartiteness.
* Multi‑source shortest path (simultaneous spread problems).
* Maze solving and word ladder problems.

**Pitfalls**:

* Cannot be used directly on weighted graphs.
* Requires care with visited marking to avoid duplicates.

---

## Depth‑First Search (DFS)

**When to use**: DFS is suited for exploring connectivity, detecting cycles, topological sorting, backtracking search, and tree processing.

**Key property**: DFS goes as deep as possible before backtracking, which naturally reveals structural properties of the graph.

**Complexity**: Runs in `O(V + E)` time, with recursion or stack space `O(V)`.

**Applications**:

* Counting connected components.
* Detecting cycles in both directed and undirected graphs.
* Generating a topological ordering in a DAG.
* Backtracking search problems (permutations, puzzles).
* Subtree queries, bridges, articulation points.

**Pitfalls**:

* Stack overflow for very deep recursions (iterative DFS may be needed).
* Requires careful handling of visited states in directed graphs (3‑color method).

---

## Dijkstra’s Algorithm (Non‑Negative Weights)

**When to use**: Dijkstra is the standard algorithm for single‑source shortest paths in graphs with non‑negative edge weights.

**Key property**: Greedy selection ensures correctness because distances only decrease monotonically when relaxing edges.

**Complexity**: `O((V + E) log V)` with a priority queue; `O(V^2)` with adjacency matrices.

**Applications**:

* Weighted shortest path queries.
* Network delay, minimum cost routing.

**Limitations**:

* Fails with negative weight edges.
* Special cases: use 0‑1 BFS when weights are only 0 or 1.

---

## Bellman–Ford (Negative Weights & Cycle Detection)

**When to use**: Use Bellman–Ford when the graph contains negative edge weights or when detecting negative cycles is required.

**Key property**: Relaxes edges up to `V−1` times, ensuring shortest paths if no negative cycle exists.

**Complexity**: `O(V·E)`.

**Applications**:

* Shortest paths in graphs with negative weights.
* Detecting arbitrage opportunities (currency exchange problems).

**Limitations**:

* Too slow for dense or very large graphs.

---

## Floyd–Warshall (All‑Pairs Shortest Paths)

**When to use**: For dense graphs with small numbers of vertices, or when you need all‑pairs shortest paths.

**Key property**: Dynamic programming approach considering intermediate vertices step by step.

**Complexity**: `O(V^3)` time, `O(V^2)` memory.

**Applications**:

* All‑pairs shortest path queries.
* Detecting negative cycles.
* Path reconstruction via intermediate tracking.

**Limitations**:

* Impractical for large graphs due to cubic time complexity.

---

## Euler Tour & Tree Flattening

**When to use**: On trees, Euler tour techniques help with subtree queries, ancestor checks, and LCA preprocessing.

**Key property**: DFS traversal timestamps or flattening a tree into an array allows subtree operations to be mapped to array intervals.

**Applications**:

* Checking ancestry with entry/exit times.
* Subtree queries using segment trees or Fenwick trees.
* LCA computation with Euler tour + RMQ or binary lifting.

**Pitfalls**:

* Only valid for tree structures (acyclic connected graphs).
* Care required with timer indices.

---

## Choosing the Right Tool

1. **Tree problems**: Prefer DFS or Euler tour techniques.
2. **Shortest path**:

   * Unweighted → BFS.
   * Non‑negative weights → Dijkstra.
   * Negative edges → Bellman–Ford.
   * All‑pairs → Floyd–Warshall (small graphs).
3. **Cycle detection**: DFS (directed or undirected variants).
4. **Ordering tasks**: Topological sort.
5. **Bipartite checks**: BFS/DFS with two‑coloring.

---

## Complexity Cheatsheet

* BFS / DFS → `O(V + E)`.
* Dijkstra → `O((V + E) log V)`.
* Bellman–Ford → `O(V·E)`.
* Floyd–Warshall → `O(V^3)`.
* Euler Tour → `O(V)` (plus preprocessing for RMQ `O(V log V)`).

---

## Common Problem Patterns

* **BFS**: Word ladder, shortest path in grids, infection/propagation problems.
* **DFS**: Number of islands, course scheduling (cycle detection), articulation points.
* **Dijkstra**: Minimum effort path, routing in networks, flight cost problems.
* **Bellman–Ford**: Arbitrage detection, graphs with negative costs.
* **Floyd–Warshall**: Dense graphs with many shortest path queries, transitive closure.
* **Euler Tour**: LCA preprocessing, subtree queries in trees.

---
