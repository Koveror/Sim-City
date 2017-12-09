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
    ///Constructor
    Vehicle(int max_spd, int l, int w) :
        max_speed(max_spd), length(l), width(w) {};

    ///Member functions
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
    ///Private members
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
    ///Constructor
    Car() : Vehicle(60, 6, 4) { }

    ///Member functions
    virtual std::string getType() const { return "Car"; }
};

class Truck : public Vehicle
{
public:
    ///Constructor
    Truck() : Vehicle(40, 8, 4) { }

    ///Member functions
    virtual std::string getType() const { return "Truck"; }
};

class Bike : public Vehicle
{
public:
    ///Constructor
    Bike() : Vehicle(70, 3, 2) { }

    ///Member functions
    virtual std::string getType() const { return "Bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
