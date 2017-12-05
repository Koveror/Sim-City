#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <memory> //ptr
#include "vertex.hpp"
#include "edge.hpp"
#include "tools.hpp"
#include "graph.hpp"

class Vehicle
{
public:
    Vehicle(int max_spd, int l, int w) :
        max_speed(max_spd), length(l), width(w) {}
	
	void moveTowards(Pos givenPos);

	void move(Graph& graph);
	
	void setPosition(Pos givenPos);

	void moveAlong();

	void setNextPosition(Pos givenPos);

	void setPath(std::vector<Edge> givenPath);

    Pos getPosition();
    
    int getLength() const;

    int getWidth() const;

    virtual std::string getType() const {return "(nothing)";}

private:
    std::shared_ptr<Vertex> last_vertex; //smart pointer?
    std::shared_ptr<Vertex> next_vertex; //smart pointer?
    std::shared_ptr<Vertex> destination;
    std::shared_ptr<Edge> current_edge;
	std::vector<Edge> path = std::vector<Edge>();
	Pos nextPosition;
	Pos position;
    int max_speed;
    float speed = 0;
    int length;
    int width;
};

class Car : public Vehicle
{
public:
    Car() : Vehicle(60, 6, 4) { }

    virtual std::string getType() const { return "Car"; }
};

class Truck : public Vehicle
{
public:
    Truck() : Vehicle(40, 8, 4) { }

    virtual std::string getType() const { return "Truck"; }
};

class Bike : public Vehicle
{
public:
    Bike() : Vehicle(70, 3, 2) { }

    virtual std::string getType() const { return "Bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
