#include "vertex.hpp"
#include <memory>
#include <algorithm>

//Constructor
Vertex::Vertex(int x, int y, tileType type){
    x_loc = x,
    y_loc = y,
    vertex_type = type;
    passable_from.push_back(true);
    passable_from.push_back(true);
    passable_from.push_back(true);
    passable_from.push_back(true);
    lastTrafficDirection = north;
}

//Boolean operator for comparing two vertices
bool Vertex::operator==(Vertex a) {
    Pos p1 = getIndex();
    Pos p2 = a.getIndex();
    if(p1 == p2 && getType() == a.getType()) {
            return true;
    } else {
            return false;
    }
}

//Set tileType to given type t. Tiletype enumerator found in tools.hpp
void Vertex::setType(tileType t)
{
    vertex_type = t;
    return;
}

//Adds an edge to this vertices edge list.
void Vertex::addEdge(Pos position, Graph& graph, int weight) {

    std::vector<std::vector<Vertex>> vertices = graph.getVertices();

    Vertex v1 = *this;
    Vertex v2 = vertices[position.y][position.x];

    std::shared_ptr<Vertex> p1 = std::make_shared<Vertex>(v1);
    std::shared_ptr<Vertex> p2 = std::make_shared<Vertex>(v2);

    Edge e1(p1, p2, weight);

    //Check not to add same edge twice
    if(edges_to.size() > 0) {
        auto res = std::find(edges_to.begin(), edges_to.end(), e1);
        if(res == edges_to.end()) {
            edges_to.push_back(e1);
        }
    } else {
        edges_to.push_back(e1);
    }
}

//Remove all edges that start from this position.
void Vertex::removeEdge(Pos position) {
    //std::cout << "Calling removeEdge " << position.x << ", " << position.y << std::endl;
    //This vertex
    std::vector<Edge>::iterator newEnd = std::remove_if(edges_to.begin(), edges_to.end(), [position](Edge x){return x.getVertices().first.getIndex() == position;});
    edges_to.erase(newEnd, edges_to.end());
}

//Remove all edges that go to this position in this vertex.
void Vertex::removeEdgesTo(Pos position) {
    //std::cout << "Calling removeEdgeMinor " << position.x << ", " << position.y << std::endl;
    //This vertex
    std::vector<Edge>::iterator newEnd = std::remove_if(edges_to.begin(), edges_to.end(), [position](Edge x){return x.getVertices().second.getIndex() == position;});
    edges_to.erase(newEnd, edges_to.end());
}

//Return true if this vertex has an edge to this index
bool Vertex::hasEdgeTo(int x, int y){
    for (auto it = edges_to.begin(); it != edges_to.end(); it++) {
		Edge e = *it;
		Vertex end = e.getVertices().second;
		Pos endPos = end.getIndex();
        if(x == endPos.x && y == endPos.y){
            return true;
        }
    }
    return false;
}

//Toggle the boolean values of the passable_from vector
void Vertex::togglePassable(bool green) {
    if (this->edges_to.size() < 3) {
        passable_from[0] = true;
        passable_from[1] = true;
        passable_from[2] = true;
        passable_from[3] = true;
    }
    else {
        if(green) {
            if(lastTrafficDirection == north){
                passable_from[0] = false;
                passable_from[1] = true;
                lastTrafficDirection = east;
            }
            else if(lastTrafficDirection == east){
                passable_from[1] = false;
                passable_from[2] = true;
                lastTrafficDirection = south;
            }
            else if(lastTrafficDirection == south){
                passable_from[2] = false;
                passable_from[3] = true;
                lastTrafficDirection = west;
            }
            else {
                passable_from[3] = false;
                passable_from[0] = true;
                lastTrafficDirection = north;
            }
        }
        else {
            passable_from[0] = false;
            passable_from[1] = false;
            passable_from[2] = false;
            passable_from[3] = false;
        }

    }
}

//Get tiletype defined in tileType enumerator
const tileType& Vertex::getType()
{
    return vertex_type;
}

//Get index in vertices data structure
Pos Vertex::getIndex()
{
    return Pos(x_loc, y_loc);
}

//Get position for drawing on the screen
Pos Vertex::getPos()
{
    return Pos(x_loc * 64 + 32, y_loc * 64 + 32);
}

//Return a list of edges that go out from this vertex
const std::vector<Edge>& Vertex::getEdgesTo(){
    return edges_to;
}

//Return a single edge, if such edge exists.
Edge Vertex::getSingleEdge(std::pair<int,int> coordPair) {
    for (auto it = edges_to.begin(); it != edges_to.end(); it++) {
		Edge e = *it;
		Vertex end = e.getVertices().second;
		Pos endPos = end.getIndex();
        if(coordPair.second == endPos.x && coordPair.first == endPos.y){
            return e;
        }
    }
    return edges_to.front(); //suppress warning
}

//Get the texture type, based on the number and direction of edges
const std::string Vertex::getTexture(){
    if (vertex_type == road){
        bool edgeNorth = hasEdgeTo(x_loc, y_loc - 1);
        bool edgeEast  = hasEdgeTo(x_loc + 1, y_loc);
        bool edgeSouth = hasEdgeTo(x_loc, y_loc + 1);
        bool edgeWest  = hasEdgeTo(x_loc - 1, y_loc);

        if (edgeNorth && edgeEast && edgeSouth && edgeWest) {
            return "roadNESW";
        } else if (edgeNorth && edgeEast && edgeSouth) {
            return "roadNES";
        } else if (edgeNorth && edgeEast && edgeWest) {
            return "roadNEW";
        } else if (edgeNorth && edgeSouth && edgeWest) {
            return "roadNSW";
        } else if (edgeEast && edgeSouth && edgeWest) {
            return "roadESW";
        } else if (edgeNorth && edgeEast) {
            return "roadNE";
        } else if (edgeNorth && edgeWest) {
            return "roadNW";
        } else if (edgeEast && edgeSouth) {
            return "roadES";
        } else if (edgeSouth && edgeWest) {
            return "roadSW";
        } else if (edgeNorth || edgeSouth) {
            return "roadNS";
        } else if (edgeEast || edgeWest) {
            return "roadEW";
        } else {
            return "road0";
        }
    } else if (vertex_type == building) {
        return "building";
    } else if (vertex_type == grass) {
        return "grass";
    } else {
        return "grass";
    }

}
