#include "graph.hpp"

int Graph::getSize()
{
    auto size = longitude * latitude;
    return size;
}

void Graph::addVertices()
{
    for (int i = 0; i < longitude; i++) {
        for (int j = 0; j < latitude; j++) {
            vertices.push_back(Vertex(i,j, "Grass"));
            //DEBUG:
            std::cout << "Adding: " << "Grass: " << i << ", " << j << std::endl;
        }
    }
    return;
}

void Graph::setVertex(int x, int y, std::string type)
{
    for (auto it = vertices.begin(); it != vertices.end();) {
        auto coord = it->getCoord();
		if (coord.first == x && coord.second == y) {
			it = vertices.erase(it);
			vertices.emplace(it-1, Vertex(x,y,type));
		}
		else it++;
	}
    return;
}



// Graph::Vertex

std::pair<int,int> Vertex::getCoord()
{
    return std::make_pair(x_loc, y_loc);
}

const std::string& Vertex::getType() const
{
    return vertex_type;
}



// Graph::Edge

std::pair<Vertex,Vertex> Edge::getVertices(){
    return std::make_pair(*vertex_1, *vertex_2);
}



