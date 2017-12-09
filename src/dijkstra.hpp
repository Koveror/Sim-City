#ifndef DIJKSTRA_HPP_INCLUDED
#define DIJKSTRA_HPP_INCLUDED

#include <queue> //priority queue
#include <limits> //numeric limits
#include <utility> //pair
#include <unordered_map>
#include "graph.hpp"

#define INF INT_MAX

class CompareWeight
{
public:
    bool operator()(std::pair<Vertex,int> n1,std::pair<Vertex,int> n2) { // (pair: vertex, int)
        return n1.second>n2.second;
    }
};

std::vector<Vertex> getPath(Graph g, Vertex source, Vertex target){
    int Y = g.getSizeY();
    int X = g.getSizeX();
    std::vector<std::vector<int>> dist(Y, std::vector<int>(X, INF)); //set all dist values to INF
    //std::vector<std::vector<Vertex*>> prev(Y, std::vector<Vertex*>(X, nullptr));
    Pos s = source.getIndex();
    dist[s.y][s.x] = 0;

    std::priority_queue<std::pair<Vertex,int>,std::vector<std::pair<Vertex,int>>,CompareWeight> Q;

    for (auto &rows : g.getVertices()) {
        for (auto &v: rows) {
            //std::cout << "DIJKSTRA debug: " << v.getIndex().x << ", " << v.getIndex().y << std::endl;
            if (v.getType() == road) {
                Q.push(std::make_pair(v, dist[v.getIndex().y][v.getIndex().x]));
            }
        }
    }

    std::cout << "DIJKSTRA debug target index: " << target.getIndex().x << ", " << target.getIndex().y << std::endl;

    //Q.push(std::make_pair(source, dist[source.getIndex().y][source.getIndex().x]));
    //std::cout << "DIJKSTRA debug Q size (start): " << Q.size() << std::endl;

    while (!Q.empty()) {
        Vertex u = Q.top().first;
        std::cout << "Now at: " << u.getIndex().x << ", " << u.getIndex().y << std::endl;
        Q.pop();
        if (u == target) {
            std::cout << "Found target" << std::endl;
            break;
        }

        std::vector<Edge> neighbors = u.getEdgesTo();
        //std::cout << "DIJKSTRA debug neighbors size: " << neighbors.size() << std::endl;
        for (Edge &edge : neighbors) {
            Vertex v = edge.getVertices().second;
            std::cout << "edge weight: " << edge.getWeight() << std::endl;
            int alt = dist[u.getIndex().y][u.getIndex().x] + edge.getWeight();
            if (alt < dist[v.getIndex().y][v.getIndex().x]) {
                dist[v.getIndex().y][v.getIndex().x] = alt;
                //prev[v.getIndex().y][v.getIndex().x] = &u;
                Q.push(std::make_pair(v, dist[v.getIndex().y][v.getIndex().x]));
            }
        }
        std::cout << "DIJKSTRA debug Q size: " << Q.size() << std::endl;
    }

    /*
    1  S ← empty sequence
    2  u ← target
    3  while prev[u] is defined:                  // Construct the shortest path with a stack S
    4      insert u at the beginning of S         // Push the vertex onto the stack
    5      u ← prev[u]                            // Traverse from target to source
    6  insert u at the beginning of S             // Push the source onto the stack
    */

    auto route = std::vector<Vertex>();
    Vertex u = target;
    //while (!(u == source)) {
        //std::cout << u.getIndex().x << ", " << u.getIndex().y << std::endl;
        route.push_back(u);
        //u = *(prev[u.getIndex().y][u.getIndex().x]);
    //}

    return route;
}

#endif // DIJKSTRA_HPP_INCLUDED
