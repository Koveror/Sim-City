#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <utility>
#include <iostream>
#include <vector>
#include "tools.hpp"
#include <algorithm>

#include "vertex.hpp"

class Vertex;

class Graph
{
public:
    ///Constructor
	Graph(int n, int m) :
	longitude(n), latitude(m) { }

	///Member functions
	bool addVertex(int x, int y);
	int getSize();
	int getSizeX();
	int getSizeY();
	void addVertices();
    void addEdge();
	void setVertex(int x, int y, tileType type);
    std::vector<std::vector<Vertex>>& getVertices();

private:
    ///Private members
	int longitude; //x
	int latitude; //y

	std::vector<std::vector<Vertex>> vertices;
};

#endif // GRAPH_HPP_INCLUDED
