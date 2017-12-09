#include "graph.hpp"

int Graph::getSize()
{
    auto size = longitude * latitude;
    return size;
}

int Graph::getSizeX()
{
    return longitude;
}

int Graph::getSizeY()
{
    return latitude;
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
            std::cout << "x: " << vertices[j][i].getPos().x << std::endl;
            std::cout << "y: " << vertices[j][i].getPos().y << std::endl;
        }
    }
    return;
}


void Graph::setVertex(int x, int y, tileType type)
{
	Graph& graph = *this;
    if(y < latitude){
        if(x < longitude){
            vertices[y][x].setType(type);
            if(type == road){
                if(y > 0 && vertices[y-1][x].getType() == road){
                    Pos position1(x,y);
                    Pos position2(x,y-1);
                    vertices[y-1][x].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == road){
                    Pos position1(x,y);
                    Pos position2(x,y+1);
                    vertices[y+1][x].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(x > 0 && vertices[y][x-1].getType() == road){
                    Pos position1(x,y);
                    Pos position2(x-1,y);
                    vertices[y][x-1].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == road){
                    Pos position1(x,y);
                    Pos position2(x+1,y);
                    vertices[y][x+1].addEdge(position1, graph, 1);
                    vertices[y][x].addEdge(position2, graph, 1);
                }
            } else {
                if(y > 0 && vertices[y-1][x].getType() == road){
                    Pos position1(x,y);
                    vertices[y-1][x].removeEdgesTo(position1);
                    vertices[y][x].removeEdge(position1);
                }
                if(y < latitude-1 && vertices[y+1][x].getType() == road){
                    Pos position1(x,y);
                    vertices[y+1][x].removeEdgesTo(position1);
                    vertices[y][x].removeEdge(position1);
                }
                if(x > 0 && vertices[y][x-1].getType() == road){
                    Pos position1(x,y);
                    vertices[y][x-1].removeEdgesTo(position1);
                    vertices[y][x].removeEdge(position1);
                }
                if(x < longitude-1 && vertices[y][x+1].getType() == road){
                    Pos position1(x,y);
                    vertices[y][x+1].removeEdgesTo(position1);
                    vertices[y][x].removeEdge(position1);
                }
            }
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


