#ifndef DIJKSTRA_HPP_INCLUDED
#define DIJKSTRA_HPP_INCLUDED

#include <queue> //priority queue
#include <limits> //numeric limits
#include <utility> //pair
#include <unordered_map>
#include "graph.hpp"

#define INF std::numeric_limits<int>::max()


class CompareWeight
{
public:
    bool operator()(std::pair<Vertex,int> n1,std::pair<Vertex,int> n2) { // (pair: vertex, int)
        return n1.second>n2.second;
    }
};

std::vector<std::pair<int,int>> getPath(Graph g, Vertex source, Vertex target) {
    int Y = g.getSizeY();
    int X = g.getSizeX();
    std::vector<std::vector<int>> dist(Y, std::vector<int>(X, INF)); //set all dist values to INF
    std::vector<std::vector<std::pair<int,int>>> prev(Y, std::vector<std::pair<int,int>>(X, std::make_pair(-1, -1)));
    Pos s = source.getIndex();
    dist[s.y][s.x] = 0;

    std::priority_queue<std::pair<Vertex,int>,std::vector<std::pair<Vertex,int>>,CompareWeight> Q;

    for (auto &rows : g.getVertices()) {
        for (auto &v: rows) {
            //std::cout << "DIJKSTRA debug: " << v.getIndex().x << ", " << v.getIndex().y << std::endl;
            if (v.getType() == road ||v.getType() == building) {
                Q.push(std::make_pair(v, dist[v.getIndex().y][v.getIndex().x]));
            }
        }
    }

    std::cout << "DIJKSTRA debug source index: " << source.getIndex().x << ", " << source.getIndex().y << ", dist: " << dist[s.y][s.x] << std::endl;
    std::cout << "DIJKSTRA debug target index: " << target.getIndex().x << ", " << target.getIndex().y << std::endl;

    //Q.push(std::make_pair(source, dist[source.getIndex().y][source.getIndex().x]));
    //std::cout << "DIJKSTRA debug Q size (start): " << Q.size() << std::endl;

    while (!Q.empty()) {
        Vertex u = Q.top().first;
        //std::cout << "Now at: " << u.getIndex().x << ", " << u.getIndex().y << std::endl;
        Q.pop();
        if (u == target) {
            std::cout << "Found target" << std::endl;
            break;
        }

        std::vector<Edge> neighbors = u.getEdgesTo();
        //std::cout << "DIJKSTRA debug neighbors size: " << neighbors.size() << std::endl;
        for (Edge &edge : neighbors) {
            Vertex v = edge.getVertices().second; ///Bug here?
            //std::cout << "edge weight: " << edge.getWeight() << std::endl;
            int alt = dist[u.getIndex().y][u.getIndex().x] + edge.getWeight();
            if (alt < dist[v.getIndex().y][v.getIndex().x]) {
                dist[v.getIndex().y][v.getIndex().x] = alt;
                prev[v.getIndex().y][v.getIndex().x] = std::make_pair(u.getIndex().y,u.getIndex().x);
                //std::cout << "prev[x]: " << v.getIndex().x << "; prev[y]: " << v.getIndex().y << std::endl;
                //std::cout << "u [x]: " << u.getIndex().x << "; u [y]: " << u.getIndex().y << std::endl;
            }
            Q.push(std::make_pair(v, dist[v.getIndex().y][v.getIndex().x]));
        }
        //std::cout << "DIJKSTRA debug Q size: " << Q.size() << std::endl;
    }

    ///DIST
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            std::cout << dist[i][j] << "; ";
        }
        std::cout << std::endl;
    }

    ///PREV
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            std::cout << "(" << prev[i][j].first << "," << prev[i][j].second << ")\t";
        }
        std::cout << std::endl;
    }

    std::cout << "Printing path..." << std::endl;

    /*
    1  S ← empty sequence
    2  u ← target
    3  while prev[u] is defined:                  // Construct the shortest path with a stack S
    4      insert u at the beginning of S         // Push the vertex onto the stack
    5      u ← prev[u]                            // Traverse from target to source
    6  insert u at the beginning of S             // Push the source onto the stack
    */

    auto route = std::vector<std::pair<int,int>>();
    std::pair<int,int> u = std::make_pair(target.getIndex().y, target.getIndex().x);
    //std::cout << "bool begin: " << (prev[u.first][u.second] != std::pair<int,int>(-1,-1)) << std::endl;
    int i = 0;
    while (prev[u.first][u.second] != std::pair<int,int>(-1,-1) && i < 10) {
        std::cout << "Route: " << u.first << ", " << u.second << std::endl;
        route.push_back(u);
        u = prev[u.first][u.second];
        //std::cout << "bool: " << (prev[u.first][u.second] != std::pair<int,int>(-1,-1)) << std::endl;
        i++;
    }
    route.push_back(u);
    std::cout << "Route last: " << u.first << ", " << u.second << std::endl;

    return route;
}

#endif // DIJKSTRA_HPP_INCLUDED
