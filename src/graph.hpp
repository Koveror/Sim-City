#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <queue> //Priority queue
#include <utility>
#include <iostream>
#include <vector>
#include "vehicle.hpp"
#include "vertex.hpp"
#include "edge.hpp"

class Graph
{
public:
	Graph(int n, int m) :
	longitude(n), latitude(m) { }
	bool addVertex(int x, int y);
	int getSize(); // { return longitude * latitude; }
	void addVertices();
	void setVertex(int x, int y, tileType type);
    std::vector<Vertex>& getVertices();

private:
	int longitude; //x
	int latitude; //y

	std::vector<Vertex> vertices;
};

#endif // GRAPH_HPP_INCLUDED
