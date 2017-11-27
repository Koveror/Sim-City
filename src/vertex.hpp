#ifndef VERTEX_HPP_INCLUDED
#define VERTEX_HPP_INCLUDED

#include <vector>

/*
enum direction
{
    north,
    east,
    south,
    west
};
*/

enum tileType
{
	grass,
	building,
	road
};

class Vertex
{
public:
    Vertex(int x, int y, tileType type) :
    x_loc(x), y_loc(y), vertex_type(type) {}
    //void addEdge(int x, int y);
    std::pair<int,int> getCoord(); // (x,y)
    const tileType& getType(); // { return vertex_type;}
    //const Vertex& getNeighbor(direction dir);
    //const std::vector<Vertex> getAllNeighbors(); // { return neighbor_vertices; }
    void setType(tileType t);

private:
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Vertex> neighbor_vertices;
};

#endif // VERTEX_HPP_INCLUDED
