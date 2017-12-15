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

class Edge;

class Graph;

class Vertex
{
public:

    ///Constructor
    Vertex(int x, int y, tileType type);

    ///Member functions
    void setType(tileType t);
    void addEdge(Pos position, Graph& graph, int weight);
    void removeEdge(Pos position);
    void removeEdgesTo(Pos position);
    bool hasEdgeTo(int x, int y);
    void togglePassable(bool green);
	const tileType& getType();
    const Pos& getIndex();
    const Pos& getPos();
    const std::vector<Edge>& getEdgesTo();
    const Edge& getSingleEdge(std::pair<int,int> coordPair);
    const std::string getTexture();


    ///Operator overloading
    bool operator==(Vertex a);
	
	///Public member
    std::vector<bool> passable_from;

private:
    ///Private members
    int x_loc;
    int y_loc;
    tileType vertex_type;
    std::vector<Edge> edges_to;
    int sendVehicleTime;
    direction lastTrafficDirection;
};

#endif // VERTEX_HPP_INCLUDED
