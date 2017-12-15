#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <utility>
#include <iostream>
#include <list>
#include "tools.hpp"
#include <algorithm>
#include <string>
#include <fstream>
#include <exception>
#include <random>

#include <queue> //priority queue
#include <limits> //numeric limits
#include <utility> //pair

#include "vertex.hpp"

class Vehicle;
class Vertex;
class Edge; /// HUOM

class Graph
{
public:
    ///Constructor
    Graph(int n, int m) :
    longitude(n), latitude(m) { }

    ///Destructor
    //~Graph();

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
    std::list<std::shared_ptr<Vehicle>>& getVehicles();
    void sendVehicle(Pos position, int multipler, float rate);
    bool saveGraph(std::string filename);
    bool loadGraph(std::string filename);
    std::vector<Edge> getPath(Vertex source, Vertex target);
    void setRoutes();
    void update();

private:
    ///Private members
    int longitude; //x
    int latitude; //y

    std::vector<std::vector<Vertex>> vertices;
    std::list<std::shared_ptr<Vehicle>> vehicles;
};

#endif // GRAPH_HPP_INCLUDED
