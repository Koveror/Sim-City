#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <queue> //Priority queue
#include <memory> //unique ptr?
#include <utility>
#include <iostream>
#include <vector>
#include "vehicle.hpp"

enum direction
{
    North,
    East,
    South,
    West
};

class Graph
{
public:
	Graph(int n, int m) :
	longitude(n), latitude(m) { }

	int getSize(); // { return longitude * latitude; }
	void addVertices();
	void setVertex(int x, int y, std::string type); //Might change type from std::string to enum

private:
	int longitude; //x
	int latitude; //y

	std::vector<Vertex> vertices;
};

//

class Vertex
{
public:
    Vertex(int x, int y, std::string type) :
    x_loc(x), y_loc(y), vertex_type(type) {}
    //void addEdge(int x, int y);
    std::pair<int,int> getCoord(); // (x,y)
    const std::string& getType() const; // { return vertex_type;}
    //const Vertex& getNeighbor(direction dir);
    //const std::vector<Vertex> getAllNeighbors(); // { return neighbor_vertices; }

private:
    int x_loc;
    int y_loc;
    std::string vertex_type;
    std::vector<Vertex> neighbor_vertices;
};

//

class Edge
{
public:
    Edge(std::shared_ptr<Vertex> V_start, std::shared_ptr<Vertex> V_end, int w):
    vertex_1(V_start), vertex_2(V_end), weight(w) {}

    int getWeight(); // { return weight;}
    std::pair<Vertex,Vertex> getVertices(); // { return both verticers the edge connects;}

private:
    std::shared_ptr<Vertex> vertex_1; //smart pointer?
    std::shared_ptr<Vertex> vertex_2; //smart pointer?
    int weight;
    //std::vector<Vehicle> vehicles;
};

#endif // GRAPH_HPP_INCLUDED
