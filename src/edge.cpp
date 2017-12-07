#include "edge.hpp"

bool Edge::operator==(Edge a) {
	Vertex tv1 = getVertices().first;
	Vertex tv2 = getVertices().second;
	Vertex av1 = a.getVertices().first;
	Vertex av2 = a.getVertices().second;
	if(tv1 == av1 && tv2 == av2) {
		return true;
	} else {
		return false;
	}
}


std::pair<Vertex,Vertex> Edge::getVertices(){
    return std::make_pair(*vertex_1, *vertex_2);
}

//Return the middle position of the nodes
Pos Edge::getMiddlePos() {
	std::pair<Vertex, Vertex> v = getVertices();
	Vertex v1 = v.first;
	Vertex v2 = v.second;
	Pos p1 = v1.getPos();
	Pos p2 = v2.getPos();
	Pos p3 = Pos((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
	return p3;
}

//Returns the direction of this edge, calculated from the endpoints
direction Edge::getDirection() {
	std::pair<Vertex, Vertex> v = getVertices();
	Pos v1 = v.first.getIndex();
	Pos v2 = v.second.getIndex();
	if(v1.x > v2.x && v1.y == v2.y) {
		return west;
	} else if(v1.x < v2.x && v1.y == v2.y) {
		return east;
	} else if(v1.y > v2.y && v1.x == v2.x) {
		return south;
	} else {
		return north;	//Assumed to be north
	}
}
