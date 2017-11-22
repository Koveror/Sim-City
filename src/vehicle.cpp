#include "vehicle.hpp"

// Graph::Vehicle

//direction Graph::Vehicle::getDirection(){
//    return current_edge.getDirection();
//}

const std::string& Vehicle::getType()
{
    return vehType;
}

/// WORK IN PROGRESS
/*std::pair<int,int> Vehicle::getCoordinates(){

    int x = 0;
    int y = 0;
    direction dir = getDirection();

    switch(dir){
    case North:
        x = lastVertex.getCoord().first;
        y = lastVertex.getCoord().second + current_position;
    case South:
        x = lastVertex.getCoord().first;
        y = lastVertex.getCoord().second - current_position;
    case East:
        x = lastVertex.getCoord().first - current_position;
        y = lastVertex.getCoord().second;
    case West:
        x = lastVertex.getCoord().first + current_position;
        y = lastVertex.getCoord().second;
    }
    return std::make_pair(x, y);
}
*/

int Vehicle::getSpeed(){
    return max_speed;
}

Edge Vehicle::getNextEdge(){
    //TODO. insert some algorithm magic here to decide where the car is of to from the next vertex
    return *current_edge;
}
