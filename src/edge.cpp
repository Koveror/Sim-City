#include "edge.hpp"

std::pair<Vertex,Vertex> Edge::getVertices(){
    return std::make_pair(*vertex_1, *vertex_2);
}
