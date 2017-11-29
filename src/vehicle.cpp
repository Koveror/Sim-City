#include "vehicle.hpp"
#include "tools.hpp"

// Graph::Vehicle

//direction Graph::Vehicle::getDirection(){
//    return current_edge.getDirection();
//}

void Vehicle::moveTowards() {

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
