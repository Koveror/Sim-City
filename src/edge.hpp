#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED

#include <utility>
#include <memory> //ptr
#include "vertex.hpp"

class Vertex;

class Edge
{
public:
    Edge(std::shared_ptr<Vertex> V_start, std::shared_ptr<Vertex> V_end, int w):
    vertex_1(V_start), vertex_2(V_end), weight(w) {}
    int getWeight(); // { return weight;}
    std::pair<Vertex,Vertex> getVertices(); // { return both verticers the edge connects;}
	Pos getMiddlePos();
	direction getDirection();
	bool operator==(Edge a);

private:
    std::shared_ptr<Vertex> vertex_1; //smart pointer?
    std::shared_ptr<Vertex> vertex_2; //smart pointer?
    int weight;
    //std::vector<Vehicle> vehicles;
};

#endif // EDGE_HPP_INCLUDED
