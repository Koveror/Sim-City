#include "vertex.hpp"

Vertex::Vertex(int x, int y, tileType type){
  x_loc = x,
  y_loc = y,
  vertex_type = type;
}

Pos Vertex::getPos()
{
    return Pos(x_loc, y_loc);
}

const tileType& Vertex::getType()
{
	//const tileType ret = vertex_type;
	//return ret;
	return vertex_type;
}

void Vertex::setType(tileType t)
{
    vertex_type = t;
    return;
}

void Vertex::addEdge(Pos position){
    edges_to.push_back(position);
}

void Vertex::removeEdge(Pos position){
    for(unsigned int i = 0; i < edges_to.size(); i++){
        if(position.x == edges_to[i].x && position.y == edges_to[i].y){
            edges_to.erase(edges_to.begin()+i);
        }
    }
}

std::vector<Pos> Vertex::getEdgesTo(){
    return edges_to;
}

bool Vertex::hasEdgeTo(int x, int y){
    for (unsigned int i = 0; i < edges_to.size(); i++){
        if(x == edges_to[i].x && y == edges_to[i].y){
            return true;
          }
    }
    return false;
}

std::string Vertex::getTexture(){
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
    }

}
