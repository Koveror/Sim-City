#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED

#include <utility>
#include <memory> //shared_ptr
#include "vertex.hpp"

class Vertex;

class Edge
{
public:
    ///Constructor
    Edge(std::shared_ptr<Vertex> V_start, std::shared_ptr<Vertex> V_end, int w):
    vertex_1(V_start), vertex_2(V_end), weight(w) {}

    ///Member functions
    int getWeight(); // { return weight;}
    std::pair<Vertex,Vertex> getVertices(); // { return both verticers the edge connects;}
	Pos getMiddlePos();
	direction getDirection();

	///Operator overloading
	bool operator==(Edge a);

private:
    ///Private members
    std::shared_ptr<Vertex> vertex_1;
    std::shared_ptr<Vertex> vertex_2;
    int weight;
};

#endif // EDGE_HPP_INCLUDED
