#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <utility>
#include <iostream>
#include <list>
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

    ///Destructor
    ~Graph();

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
    std::list<Vehicle*>& getVehicles();
    void sendVehicle(Pos position);

private:
    ///Private members
    int longitude; //x
    int latitude; //y

    std::vector<std::vector<Vertex>> vertices;
    std::list<Vehicle*> vehicles;
};

#endif // GRAPH_HPP_INCLUDED
