#include "vehicle.hpp"

//Set the position to where this vehicle tries to move
//when the method move() is called.
void Vehicle::setNextPosition(Pos givenPos) {
	nextPosition = givenPos;
}

//Move the vehicle on the graph. This is the main move method that calls
//all of the other methods. It is called on every tick on every car.
void Vehicle::move(Graph& graph) {
	int iX = position.x / 64;
	int iY = position.y / 64;
	int dX = nextPosition.x / 64;
	int dY = nextPosition.y / 64;
        Vertex v = graph.getVertices()[iY][iX];		//Get current vertex from the graph
	Vertex nextV = graph.getVertices()[dY][dX];		//Get current vertex from the graph
	//std::cout << "Current position: (" << position.x << ", " << position.y << ")" << std::endl;
	//std::cout << "Next position: (" << nextPosition.x << ", " << nextPosition.y << ")" << std::endl;

	if(iX == dX && iY == dY && !v.passable_from[comingFrom]) {	//TODO: figure out current direction
            //Wait
	} 
	else if(position.x == nextPosition.x && position.y == nextPosition.y) {
            std::vector<Edge> edges = v.getEdgesTo();
            if(edges.size() < 1) {
                //std::cout << "Getting new" << std::endl;
            } else {
                if(path.size() > 0){
                    nextPosition = path.front().getVertices().second.getPos();
                    path.erase(path.begin());
                }
                else{
                    nextPosition = position;
                }
                //reset comingFrom -direction 
                if(position.x < nextPosition.x){
                    comingFrom = west;
                } else if(position.x > nextPosition.x){
                    comingFrom = east;
                } else if(position.y < nextPosition.y){
                    comingFrom = south;
                } else if(position.y > nextPosition.y){
                    comingFrom = north;
                }
            }
        } else {
		//std::cout << "Calling move towards" << std::endl;
		moveTowards(nextPosition);	//If we aren't where we are supposed to, move towards it
	}
}

//Set a path for this vehicle to move on.
void Vehicle::setPath(std::vector<Edge> givenPath) {
	path = givenPath;
}

//Move along an edge.
void Vehicle::moveAlong() {
	if(path.size() > 0) {
		Edge e = path.front();
		std::pair<Vertex, Vertex> pair = e.getVertices();
		Vertex start = pair.first;
		Vertex end = pair.second;
		moveTowards(end.getPos());
	}
}

//Move towards a given position. Called by other move methods.
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

//Set vehicles position. Call this after making a vehicle to place it somewhere.
void Vehicle::setPosition(Pos givenPos) {
	position = givenPos;
}

void Vehicle::setDestination(Pos dest){
    destination = dest;
}

//Get current position. Used for drawing for example.
Pos Vehicle::getPosition() const{
	return position;
}

//Get length variable. Currently not used.
int Vehicle::getWidth() const{
    return width;
}

//Get width. Currently not in use.
int Vehicle::getHeight() const{
    return height;
}

// get destination
Pos Vehicle::getDestination() const{
    return destination;
}

bool Vehicle::atDestination() const{
    auto temp = Pos(position.x/64, position.y/64);
    //std::cout << "DEBUG temp pos: " << temp.x << ", " << temp.y << std::endl;
    //std::cout << "DEBUG destination pos " << destination.x << ", " << destination.y << std::endl;
    
    return temp == destination;
}
