#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <limits>
#include <utility>
#include <iostream>
#include <vector>

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
	~Graph();

	int getSize(); // { return longitude * latitude; }
	void addVertices();
	void setVertex(int x, int y, std::string type, int w); //Might change type from std::string to enum
	void setVertexNeighbors(); //addEdges: Init the Map grid by adding default
	//std::vector<std::pair<Int>> GetAllVertices() const;

private:
	int longitude; //x
	int latitude; //y

	class Vertex; // forward decl.
	std::vector<Vertex> vertices;

	class Vertex
	{
    public:
        Vertex(int x, int y, std::string type, int w) :
        x_loc(x), y_loc(y), vertex_type(type), weight(w) {}
        //void addEdge(int x, int y);
        std::pair<int,int> getCoord();
        const std::string& getType(); // { return vertex_type;}
        int getWeight(); // { return weight;}
        //const Vertex& getNeighbor(direction dir);
        //const std::vector<Vertex> getAllNeighbors(); // { return neighbor_vertices; }

    private:
        int x_loc;
        int y_loc;
        std::string vertex_type;
        int weight;
        std::vector<Vertex> neighbor_vertices;
	};

};

#endif // GRAPH_HPP_INCLUDED
