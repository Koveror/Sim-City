#ifndef VERTEX_HPP_INCLUDED
#define VERTEX_HPP_INCLUDED

#include <list>
#include "tools.hpp"
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "edge.hpp"

class Edge;

class Graph;

class Vertex
{
public:
    Vertex(int x, int y, tileType type);
    Pos getPos();
	Pos getIndex();
    const tileType& getType();
    void setType(tileType t);
    void addEdge(Pos position, Graph& graph, int weight);
    void removeEdge(Pos position);
	void removeEdgesTo(Pos position);
    std::vector<Edge> getEdgesTo();
    std::string getTexture();
    bool hasEdgeTo(int x, int y);
	bool operator==(Vertex a);

private:
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Edge> edges_to;
};

#endif // VERTEX_HPP_INCLUDED
