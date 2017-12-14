#ifndef VERTEX_HPP_INCLUDED
#define VERTEX_HPP_INCLUDED

#include <list>
#include "tools.hpp"
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "edge.hpp"
#include "vehicle.hpp"

//Forward declarations
class Edge;
class Graph;

class Vertex
{
public:

    ///Constructor
    Vertex(int x, int y, tileType type);

    ///Member functions
    Pos getPos();
    Pos getIndex();
    const tileType& getType();
    void setType(tileType t);
    void addEdge(Pos position, Graph& graph, int weight);
    void removeEdge(Pos position);
    void removeEdgesTo(Pos position);
    const std::vector<Edge>& getEdgesTo();
    const std::string getTexture();
    bool hasEdgeTo(int x, int y);
    Edge getSingleEdge(std::pair<int,int> coordPair);
    void togglePassable();
    void sendVehicle();

    ///Operator overloading
    bool operator==(Vertex a);

    std::vector<bool> passable_from;

private:
    ///Private members
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Edge> edges_to;
    int sendVehicleTime;
};

#endif // VERTEX_HPP_INCLUDED
