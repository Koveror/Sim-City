#ifndef DIJKSTRA_HPP_INCLUDED
#define DIJKSTRA_HPP_INCLUDED

#include <queue> //priority queue
#include <limits> //numeric limits
#include <unordered_map>
#include "edge.hpp"

class Dijkstra
{
public:
    Dijkstra():
    {}
    
    /*
1  function Dijkstra(Graph, source):
2      dist[source] ← 0                                    // Initialization
3
4      create vertex set Q
5
6      for each vertex v in Graph:           
7          if v ≠ source
8              dist[v] ← INFINITY                          // Unknown distance from source to v
9              prev[v] ← UNDEFINED                         // Predecessor of v
10
11         Q.add_with_priority(v, dist[v])
12
13
14     while Q is not empty:                              // The main loop
15         u ← Q.extract_min()                            // Remove and return best vertex
16         for each neighbor v of u:                      // only v that is still in Q
17             alt ← dist[u] + length(u, v) 
18             if alt < dist[v]
19                 dist[v] ← alt
20                 prev[v] ← u
21                 Q.decrease_priority(v, alt)
22
23     return dist[], prev[]

    */
    
    void getPath(Vertex source, Vertex dest) = {
        auto inf = std::numeric_limits<double>::max();
        auto dist = std::unordered_map<Vertex, double>;
        auto path = std::unordered_map<Vertex, Vertex>;
        auto pq = std::priority_queue
        auto visited = std::vector<std::vector<int>>;
    }

private:
};

#endif // DIJKSTRA_HPP_INCLUDED
