#include "vehicle.hpp"
#include "tools.hpp"

// Graph::Vehicle

//direction Graph::Vehicle::getDirection(){
//    return current_edge.getDirection();
//}

void Vehicle::setPath(std::vector<Edge> givenPath) {
	path = givenPath;
}

void Vehicle::moveAlong() {
	if(path.size() > 0) {
		Edge e = path.front();
		std::pair<Vertex, Vertex> pair = e.getVertices();
		Vertex start = pair.first;
		Vertex end = pair.second;
		moveTowards(end.getPos());
	}
}

void Vehicle::moveTowards(Pos givenPos) {
	int newX = 0;
	int newY = 0;	
	
	if(givenPos.y > position.y) {
		newY = position.y + 1;
	} else if(givenPos.y == position.y){
		newY = position.y;
	} else {
		newY = position.y - 1;
	}

	if(givenPos.x > position.x) {
		newX = position.x + 1;
	} else if(givenPos.x == position.x) {
		newX = position.x;
	} else {
		newX = position.x - 1;
	}
	position = Pos(newX, newY);
}

void Vehicle::setPosition(Pos givenPos) {
	position = givenPos;
}

Pos Vehicle::getPosition() {
	return position;
}


int Vehicle::getLength() const{
    return length;
}

int Vehicle::getWidth() const{
    return width;
}

Edge Vehicle::getNextEdge() const{
    //TODO. insert some algorithm magic here to decide where the car is of to from the next vertex
    return *current_edge;
}
