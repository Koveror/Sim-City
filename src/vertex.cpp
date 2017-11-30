#include "vertex.hpp"

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

