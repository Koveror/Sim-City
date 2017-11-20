#include "graph.hpp"

Graph::~Graph()
{
}

int Graph::getSize()
{
    auto size = longitude * latitude;
    return size;
}

void Graph::addVertices()
{
    for (int i = 0; i < longitude; i++) {
        for (int j = 0; j < latitude; j++) {
            vertices.push_back(Vertex(i,j, "Grass", INT_MAX));
            //DEBUG:
            std::cout << "Adding: " << "Grass: " << i << ", " << j << std::endl;
        }
    }
    return;
}

void Graph::setVertex(int x, int y, std::string type, int w)
{
    for (auto it = vertices.begin(); it != vertices.end();) {
        auto coord = it->getCoord();
		if (coord.first == x && coord.second == y) {
			it = vertices.erase(it);
			vertices.emplace(it-1, Vertex(x,y,type,w));
		}
		else it++;
	}
    return;
}

void Graph::setVertexNeighbors()
{
    for (int i = 0; i < longitude; i++) {
        for (int j = 0; j < latitude; j++) {
            if (i == 0 && j == 0) {

            }
        }
    }
    return;
}

// Graph::Vertex...

std::pair<int,int> Graph::Vertex::getCoord()
{
    return std::make_pair(x_loc, y_loc);
}

const std::string& Graph::Vertex::getType()
{
    return vertex_type;
}

int Graph::Vertex::getWeight()
{
    return weight;
}

// WORK IN PROGRESS:

/*const Vertex& Graph::Vertex::getNeighbor(direction dir)
{
    if (dir == North) {
        //
    } else if (dir == East) {
        //
    } else if (dir == South) {
        //
    } else if (dir == West) {
        //
    }
}*/

