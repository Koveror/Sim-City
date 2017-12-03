#include "vertex.hpp"
#include <memory>
#include "graph.hpp"

//Constructor
Vertex::Vertex(int x, int y, tileType type){
  x_loc = x,
  y_loc = y,
  vertex_type = type;
}

bool Vertex::operator==(Vertex a) {
	Pos p1 = getIndex();
	Pos p2 = a.getIndex();
	if(p1 == p2 && getType() == a.getType()) {
		return true;
	} else {
		return false;
	}
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

//Get tiletype defined in tileType enumerator
const tileType& Vertex::getType()
{
	return vertex_type;
}

//Set tileType
void Vertex::setType(tileType t)
{
    vertex_type = t;
    return;
}

void Vertex::addEdge(Pos position, Graph& graph) {
	
	std::vector<std::vector<Vertex>> vertices = graph.getVertices();	
	
	Vertex v1 = *this;
	Vertex v2 = vertices[position.y][position.x];

	std::shared_ptr<Vertex> p1 = std::make_shared<Vertex>(v1);
	std::shared_ptr<Vertex> p2 = std::make_shared<Vertex>(v2);
	int w = 1;
	
	Edge e1(p1, p2, w);

    edges_to.push_back(e1);
	edges_to.unique();
}

void Vertex::removeEdge(Pos position) {
	std::cout << "Calling removeEdge" << std::endl;
    for(auto it = edges_to.begin(); it != edges_to.end(); it++) {
		Edge e = *it;
		Vertex end = e.getVertices().second;
		Pos endPos = end.getIndex();
        if(position.x == endPos.x && position.y == endPos.y){
			std::cout << "Erasing: " << endPos.x << endPos.y << std::endl;
            edges_to.erase(it);	//Calling this calls the destructor of the edge and vertices along with it? -> Segmentation fault
        }
    }
}

std::list<Edge> Vertex::getEdgesTo(){
    return edges_to;
}

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
