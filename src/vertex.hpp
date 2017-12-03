#ifndef VERTEX_HPP_INCLUDED
#define VERTEX_HPP_INCLUDED

#include <vector>
#include "tools.hpp"
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Vertex
{
public:
    Vertex(int x, int y, tileType type);
    Pos getPos();
	Pos getIndex();
    const tileType& getType();
    void setType(tileType t);
    void addEdge(Pos position);
    void removeEdge(Pos position);
    std::vector<Pos> getEdgesTo();
    std::string getTexture();
    bool hasEdgeTo(int x, int y);

private:
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Pos> edges_to;
};

#endif // VERTEX_HPP_INCLUDED
