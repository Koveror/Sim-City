#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include "graph.hpp"

class Vertex; //forward decl
class Edge; //forward decl

class Vehicle
{
public:
    Vehicle(std::shared_ptr<Vertex> V_last, std::shared_ptr<Vertex> V_next,
            std::shared_ptr<Vertex> V_destination, std::shared_ptr<Edge> cur_edge,
            int max_spd, std::string veh_type):
        last_vertex(V_last), next_vertex(V_next),
        destination(V_destination), current_edge(cur_edge),
        max_speed(max_spd), vehType(veh_type) {}
    //direction getDirection(); // get the direction the car is attempting to move based on vertex and vertices
    std::pair<int,int> getCoordinates(); // returns the exact location based on private data
    int getSpeed(); //get current speed
    Edge getNextEdge(); // returns the next edge based on destination
    const std::string& getType();

private:
    std::shared_ptr<Vertex> last_vertex; //smart pointer?
    std::shared_ptr<Vertex> next_vertex; //smart pointer?
    std::shared_ptr<Vertex> destination;
    std::shared_ptr<Edge> current_edge;
    int max_speed;
    int current_position = 0;
    int speed = 0;
    std::string vehType;
};

#endif // VEHICLE_HPP_INCLUDED
