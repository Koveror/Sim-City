#include "vehicle.hpp"


//Helper method used for collision checking. Checks every single vehicle to see that p0 doesn't contain a vehicle.
//Returns true if there is a vehicle in front, otherwise returns false.
//TODO: Performance!!!
//TODO: In turns vehicles can go inside each other
bool Vehicle::checkFront(Graph& graph) const {

    int length = 15;    //The distance of the front position from the vehicle. TODO: Use vehicle width and length
    Pos p0;     //A position in front of the current vehicle.

    //Get current direction and figure out front position.
    direction d0 = getDirection();
    if(d0 == north) {p0 = Pos(position.x, position.y - length);}
    else if(d0 == east) {p0 = Pos(position.x - length, position.y);}
    else if(d0 == south) {p0 = Pos(position.x, position.y + length);}
    else {p0 = Pos(position.x + length, position.y);}

    //Check if the front position is clear by checking through all of the vehicles.
    std::list<std::shared_ptr<Vehicle>> vehicles = graph.getVehicles();
    auto it = std::find_if(vehicles.begin(), vehicles.end(), [p0, d0](std::shared_ptr<Vehicle> x){return x->getPosition() == p0 && x -> getDirection() == d0;});
    if(it == vehicles.end()) {
        return false;
    } else {
        return true;
    }
}

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

        //Check traffic lights
	if(iX == dX && iY == dY && !v.passable_from[comingFrom]) {	//TODO: figure out current direction
            //Wait
        }
        //Check that fron of car is clear
        else if(checkFront(graph)) {
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

direction Vehicle::getDirection() const{
    return comingFrom;
}

bool Vehicle::atDestination() const{
    auto posGrid = Pos(position.x/64, position.y/64);
    auto destGrid = Pos(destination.x/64, destination.y/64);
    //std::cout << "DEBUG position pos: " << position.x << ", " << position.y << std::endl;
    //std::cout << "DEBUG destination pos " << destination.x << ", " << destination.y << std::endl;
    //std::cout << "DEBUG posGrid pos: " << posGrid.x << ", " << posGrid.y << std::endl;
    //std::cout << "DEBUG destGrid pos: " << destGrid.x << ", " << destGrid.y << std::endl;
    
    return posGrid == destGrid;
}
