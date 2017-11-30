#ifndef VERTEX_HPP_INCLUDED
#define VERTEX_HPP_INCLUDED

#include <vector>
#include "tools.hpp"

class Vertex
{
public:
    Vertex(int x, int y, tileType type) :
    x_loc(x), y_loc(y), vertex_type(type) {}
    //void addEdge(int x, int y);
    Pos getPos(); // (x,y)
    const tileType& getType(); // { return vertex_type;}
    //const Vertex& getNeighbor(direction dir);
    //const std::vector<Vertex> getAllNeighbors(); // { return neighbor_vertices; }
    void setType(tileType t);
    void addEdge(Pos position);
    std::vector<Pos> getEdgesTo();

private:
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Pos> edges_to;
};

#endif // VERTEX_HPP_INCLUDED
