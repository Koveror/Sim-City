#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <utility>
#include <iostream>
#include <vector>
#include "tools.hpp"
#include <algorithm>

#include "vertex.hpp"

class Vehicle;
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
    void addCar(Pos p);
    void setVertex(int x, int y, tileType type);
    std::vector<std::vector<Vertex>>& getVertices();
    std::vector<Vehicle*>& getVehicles();
    void sendVehicle(Pos position);

private:
    ///Private members
    int longitude; //x
    int latitude; //y

    std::vector<std::vector<Vertex>> vertices;
    std::vector<Vehicle*> vehicles;
};

#endif // GRAPH_HPP_INCLUDED
