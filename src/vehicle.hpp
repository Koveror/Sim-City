#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <memory> //ptr
#include "vertex.hpp"
#include "edge.hpp"
#include "tools.hpp"

class Vehicle
{
public:
    Vehicle(std::shared_ptr<Vertex> V_last, std::shared_ptr<Vertex> V_next,
            std::shared_ptr<Vertex> V_destination, std::shared_ptr<Edge> cur_edge,
            int max_spd, int l, int w) :
        last_vertex(V_last), next_vertex(V_next),
        destination(V_destination), current_edge(cur_edge),
        max_speed(max_spd), length(l), width(w) {}
	
	void moveTowards(Pos givenPos);
	
	void setPosition(Pos givenPos);

	void moveAlong();

	void setPath(std::vector<Edge> givenPath);

    Pos getPosition();
    
	Edge getNextEdge() const; // returns the next edge based on destination
    int getLength() const;
    int getWidth() const;
    virtual std::string getType() const {return "(nothing)";}

private:
    std::shared_ptr<Vertex> last_vertex; //smart pointer?
    std::shared_ptr<Vertex> next_vertex; //smart pointer?
    std::shared_ptr<Vertex> destination;
    std::shared_ptr<Edge> current_edge;
	std::vector<Edge> path = std::vector<Edge>();
	Pos position;
    int max_speed;
    float speed = 0;
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
