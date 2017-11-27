#include "vertex.hpp"

std::pair<int,int> Vertex::getCoord()
{
    return std::make_pair(x_loc, y_loc);
}

const tileType Vertex::getType()
{
	const tileType ret = vertex_type;
	return ret;
	//return vertex_type;
}
