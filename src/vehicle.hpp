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
            int max_spd, int l, int w) :
        last_vertex(V_last), next_vertex(V_next),
        destination(V_destination), current_edge(cur_edge),
        max_speed(max_spd), length(l), width(w) {}
    //direction getDirection(); // get the direction the car is attempting to move based on vertex and vertices
    //std::pair<int,int> getCoordinates(); // returns the exact location based on private data
    int getSpeed() const; //get current speed
    Edge getNextEdge() const; // returns the next edge based on destination
    int getLength() const;
    int getWidth() const;
    virtual std::string getType() const {return "(nothing)";}

private:
    std::shared_ptr<Vertex> last_vertex; //smart pointer?
    std::shared_ptr<Vertex> next_vertex; //smart pointer?
    std::shared_ptr<Vertex> destination;
    std::shared_ptr<Edge> current_edge;
    int max_speed;
    int current_position = 0;
    int speed = 0;
    int length;
    int width;
};

class Car : public Vehicle
{
public:
    Car() : Vehicle(nullptr, nullptr, nullptr, nullptr, 60, 6, 4) { }
    
    virtual std::string getType() const { return "Car"; }
};

class Truck : public Vehicle
{
public:
    Truck() : Vehicle(nullptr, nullptr, nullptr, nullptr, 40, 8, 4) { }
    
    virtual std::string getType() const { return "Truck"; }
};

class Bike : public Vehicle
{
public:
    Bike() : Vehicle(nullptr, nullptr, nullptr, nullptr, 70, 3, 2) { }
    
    virtual std::string getType() const { return "Bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
