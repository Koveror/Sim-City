#include "vehicle.hpp"
#define PI 3.14159265


//Helper method used for collision checking. Checks every single vehicle to see that p0 doesn't contain a vehicle.
//Returns true if there is a vehicle in front, otherwise returns false.
bool Vehicle::checkFront(Graph& graph) const {

    int length = height + 8; 	//The distance of the front position from the vehicle.
    Pos p0; 	//A position in front of the current vehicle.

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
        int distanceFromVertexCenter = std::max( abs(position.x-nextPosition.x) ,  abs(position.y-nextPosition.y) );
	if(iX == dX && iY == dY && distanceFromVertexCenter > 30 && !v.passable_from[comingFrom]) {	//TODO: figure out current direction
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
                    turningFrom = comingFrom;
                    lastPosition = nextPosition;
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

//Set vehicles position. Call this after making a vehicle to place it somewhere.
void Vehicle::setPosition(Pos givenPos) {
	position = givenPos;
}

//Set the position to where this vehicle tries to move
//when the method move() is called.
void Vehicle::setNextPosition(Pos givenPos) {
	nextPosition = givenPos;
}

//Set a path for this vehicle to move on.
void Vehicle::setPath(std::vector<Edge> givenPath) {
	path = givenPath;
}

void Vehicle::setDestination(Pos dest){
    destination = dest;
}

//Get current position. Used for drawing for example.
Pos Vehicle::getPosition() const{
	return position;
}

//Get next position.
Pos Vehicle::getNextPosition() const{
	return nextPosition;
}

//Get last position.
Pos Vehicle::getLastPosition() const{
	return lastPosition;
}

//Get width variable.
int Vehicle::getWidth() const{
    return width;
}

//Get height variable.
int Vehicle::getHeight() const{
    return height;
}

//Return the path that vehicle is going to take.
const std::vector<Edge>& Vehicle::getPath() {
    return path;
}

//Get destination
Pos Vehicle::getDestination() const{
    return destination;
}

//Check if arrived
bool Vehicle::atDestination() const{
    auto posGrid = Pos(position.x/64, position.y/64);
    auto destGrid = Pos(destination.x/64, destination.y/64);
    
    //Debug
    //auto posGrid = Pos(position.x, position.y);
    //auto destGrid = Pos(destination.x, destination.y);
    //std::cout << "DEBUG position pos: " << position.x << ", " << position.y << std::endl;
    //std::cout << "DEBUG destination pos " << destination.x << ", " << destination.y << std::endl;
    //std::cout << "DEBUG posGrid pos: " << posGrid.x << ", " << posGrid.y << std::endl;
    //std::cout << "DEBUG destGrid pos: " << destGrid.x << ", " << destGrid.y << std::endl;
    //std::cout << "DEBUG path size: " << path.size() << std::endl;

    return posGrid == destGrid;
}

//Get destination
direction Vehicle::getDirection() const{
    return comingFrom;
}

direction Vehicle::turningTo() const{
    if(path.size() > 0) {
        direction dir = noDir;
        Edge e = path.front();
        std::pair<Vertex, Vertex> pair = e.getVertices();
        Pos start = pair.first.getIndex();
        Pos end = pair.second.getIndex();
        if (start.x < end.x) dir = east;
        if (start.x > end.x) dir = west;
        if (start.y < end.y) dir = south;
        if (start.y > end.y) dir = north;
        return dir;
    }
    return noDir;
}

direction Vehicle::getTurningFrom() const{
    return turningFrom;
}

//Return position of vehicle when vehicle is starting to turn left
Pos Vehicle::leftTurnBeginning(Pos position, int distance, direction dir){
    if(dir == north){
        float s = 48.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float y = s * std::sin(alpha*PI/180.0);
        float x = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y - y) );
    }
    if(dir == south){
        float s = 48.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float y = s * std::sin(alpha*PI/180.0);
        float x = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y + y) );
    }
    if(dir == west){
        float s = 48.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float x = s * std::sin(alpha*PI/180.0);
        float y = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y - y) );
    }
    if(dir == east){
        float s = 48.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float x = s * std::sin(alpha*PI/180.0);
        float y = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y + y) );
    }
    else{
        return Pos(100, 100);
    }
    
}

//Return position of vehicle when vehicle has finished turning left
Pos Vehicle::leftTurnEnd(Pos position, int distance, direction dir){
    if(dir == west){
        float s = 48.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float y = s * std::cos(alpha*PI/180.0);
        float x = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y - y) );
    }
    if(dir == east){
        float s = 48.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float y = s * std::cos(alpha*PI/180.0);
        float x = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y + y) );
    }
    if(dir == south){
        float s = 48.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float x = s * std::cos(alpha*PI/180.0);
        float y = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y - y) );
    }
    if(dir == north){
        float s = 48.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float x = s * std::cos(alpha*PI/180.0);
        float y = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y + y) );
    }
    else{
        return Pos(100, 100);
    }
    
}

//Return position of vehicle when vehicle is starting to turn right
Pos Vehicle::rightTurnBeginning(Pos position, int distance, direction dir){

    if(dir == north){
        float s = 16.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float y = s * std::sin(alpha*PI/180.0);
        float x = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y - y) );
    }
    if(dir == south){
        float s = 16.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float y = s * std::sin(alpha*PI/180.0);
        float x = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y + y) );
    }
    if(dir == east){
        float s = 16.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float x = s * std::sin(alpha*PI/180.0);
        float y = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y - y) );
    }
    if(dir == west){
        float s = 16.0;
        float progress = distance/32.0;
        float alpha = progress * 45.0;
        float x = s * std::sin(alpha*PI/180.0);
        float y = s * std::cos(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y + y) );
    }
    else{
        return Pos(100, 100);
    }
    
}

//Return position of vehicle when vehicle has finished turning right
Pos Vehicle::rightTurnEnd(Pos position, int distance, direction dir){

    if(dir == east){
        float s = 16.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float y = s * std::cos(alpha*PI/180.0);
        float x = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y - y) );
    }
    if(dir == west){
        float s = 16.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float y = s * std::cos(alpha*PI/180.0);
        float x = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y + y) );
    }
    if(dir == south){
        float s = 16.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float x = s * std::cos(alpha*PI/180.0);
        float y = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x + x), int(position.y - y) );
    }
    if(dir == north){
        float s = 16.0;
        float progress = (32.0-distance)/32.0;
        float alpha = progress * 45.0;
        float x = s * std::cos(alpha*PI/180.0);
        float y = s * std::sin(alpha*PI/180.0);
        return Pos( int(position.x - x), int(position.y + y) );
    }
    else{
        return Pos(100, 100);
    }
    
}

//Check if next turn is going to be left or right.
bool Vehicle::nextTurnIsLeft(){
    if(comingFrom == north && turningTo() == west) return true;
    if(comingFrom == south && turningTo() == east) return true;
    if(comingFrom == west && turningTo() == north) return true;
    if(comingFrom == east && turningTo() == south) return true;
    return false;
}

//Check if last turn is going to be left or right.
bool Vehicle::lastTurnWasLeft(){
    if(turningFrom == north && comingFrom == east) return true;
    if(turningFrom == south && comingFrom == west) return true;
    if(turningFrom == west && comingFrom == north) return true;
    if(turningFrom == east && comingFrom == south) return true;
    return false;
}


