#include "edge.hpp"

std::pair<Vertex,Vertex> Edge::getVertices(){
    return std::make_pair(*vertex_1, *vertex_2);
}

Pos Edge::getMiddle() {
	std::pair<Vertex, Vertex> v = getVertices();
	Vertex v1 = v.first;
	Vertex v2 = v.second;
	Pos p1 = v1.getPos();
	Pos p2 = v2.getPos();
	Pos p3 = Pos((p1.x + p2.x) * 64, (p1.y + p2.y) * 64);
	return p3;
}

direction Edge::getDirection() {
	std::pair<Vertex, Vertex> v = getVertices();
	Vertex v1 = v.first;
	Vertex v2 = v.second;
	return south;
}
