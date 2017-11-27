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
            Vertex v1(i,j, grass);
            vertices.push_back(v1);
            //DEBUG:
            std::cout << "Adding: " << "Grass: " << i << ", " << j << std::endl;
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
  for (auto it = vertices.begin(); it != vertices.end(); it++) {
    auto coord = it->getCoord();
    if (coord.first == x && coord.second == y) {
      it->setType(type);
      return;
    }
  }
  return;
}

std::vector<Vertex>& Graph::getVertices(){
    return vertices;
}

bool Graph::addVertex(int x, int y)
{
	for(Vertex vertex : vertices) {
		int mX = vertex.getCoord().first;
		int mY = vertex.getCoord().second;
		if(x == mX && y == mY) {
			return false;
		}
	}
	tileType t = grass;
	vertices.push_back(Vertex(x, y, t));
	return true;
}


