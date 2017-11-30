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

std::vector<Pos> Vertex::getEdgesTo(){
    return edges_to;
}

