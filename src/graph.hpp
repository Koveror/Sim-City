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
            //const Vertex& getNeighbor(direction dir);
            //const std::vector<Vertex> getAllNeighbors(); // { return neighbor_vertices; }

        private:
            int x_loc;
            int y_loc;
            std::string vertex_type;
            std::vector<Vertex> neighbor_vertices;
            };
/*
        class Edge
        {
        public:
            int getWeight(); // { return weight;}
            std::pair<Vertex,Vertex> getVertices(); // { return both verticers the edge connects;}
            direction getDirection(); // returns the direction of the edge (dir)

        private:
            Vertex vertex_1;
            Vertex vertex_2;
            direction dir;
            int weight;
            std::vector<Vehicle> vehicles;
        };

        class Vehicle
        {
        public:
            direction getDirection(); // get the direction the car is attempting to move based on vertex and vertices
            std::pair<int,int> getCoordinates(); // returns the exact location basd on private data
            int getSpeed(); //get current speed
            Edge getNextEdge(); // returns the next edge based on destination

        private:
            Vertex last_vertex;
            Vertex next_vertex;
            Vertex destination;
            Edge current_edge;
            int current_position;
            int max_speed;
            int speed;
        };
*/
};

#endif // GRAPH_HPP_INCLUDED
