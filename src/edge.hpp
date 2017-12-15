#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED

#include <utility>
#include <memory>
#include <vector>
#include "vehicle.hpp"
#include "tools.hpp"

class Vehicle;

class Vertex;

class Edge
{
public:
    ///Constructor
    Edge(std::shared_ptr<Vertex> V_start, std::shared_ptr<Vertex> V_end, int w):
    vertex_1(V_start), vertex_2(V_end), weight(w) {}

    ///Member functions
    int getWeight();
    std::pair<Vertex,Vertex> getVertices();
    Pos getMiddlePos();
    direction getDirection();
    void swapVertices();
    bool isFull();
    void addVehicle();
    void removeVehicle();

    ///Operator overloading
    bool operator==(Edge a);

private:
    ///Private members
    std::shared_ptr<Vertex> vertex_1;
    std::shared_ptr<Vertex> vertex_2;
    int weight;
    int vehAmount;
};

#endif // EDGE_HPP_INCLUDED
