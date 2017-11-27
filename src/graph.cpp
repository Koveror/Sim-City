#include "graph.hpp"

int Graph::getSize()
{
    auto size = longitude * latitude;
    return size;
}

void Graph::addVertices()
{
    for (int j = 0; j < latitude; j++) {
        std::vector<Vertex> row = {};
        vertices.push_back(row);
        for (int i = 0; i < longitude; i++) {
            Vertex v1(i,j, grass);
            std::cout << "--- pushing ---" << std::endl;
            vertices[j].push_back(v1);
            //DEBUG:
            std::cout << "Adding: " << "Grass: " << j << ", " << i << std::endl;
            std::cout << "x: " << vertices[j][i].getCoord().first << std::endl;
            std::cout << "y: " << vertices[j][i].getCoord().second << std::endl;
        }
    }
    return;
}

void Graph::setVertex(int x, int y, tileType type)
{
  /*
  for (auto it = vertices.begin(); it != vertices.end();) {
    auto coord = it->getCoord();
		if (coord.first == x && coord.second == y) {
			it = vertices.erase(it);
			vertices.emplace(it-1, Vertex(x,y,type));
      return;
		}
		else it++;
	}
  return;
    */
    if(y < latitude){
        if(x < longitude){
            vertices[y][x].setType(type);
            return;
        }
    }
    return;
}

std::vector<std::vector<Vertex>>& Graph::getVertices(){
    return vertices;
}

bool Graph::addVertex(int x, int y)
{
	tileType t = grass;
        Vertex new_vertex(x,y, t);
	vertices[y][x] = new_vertex;
	return true;
}


