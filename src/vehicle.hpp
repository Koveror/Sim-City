#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <memory> //ptr

#include "edge.hpp"
#include "vehicle.hpp"
#include "vertex.hpp"
#include "graph.hpp"
#include <algorithm>
#include <math.h>

class Edge;

class Graph;

class Vehicle
{
public:
    ///Constructor
    Vehicle(int w, int h) :
        width(w), height(h), destination(Pos(0,0)) {}

    ///Destructor
    virtual ~Vehicle() {}

    ///Copy constructor, Ro3
    Vehicle(const Vehicle& copyFrom) = default;

    ///Copy assignment, Ro3
    Vehicle& operator=(const Vehicle& copyFrom) = default;

    ///Member functions
	bool checkFront(Graph& graph) const;
    void moveTowards(Pos givenPos);
    void move(Graph& graph);
    void moveAlong();
    void setPosition(Pos givenPos);
    void setNextPosition(Pos givenPos);
    void setPath(std::vector<Edge> givenPath);
    void setDestination(Pos dest);
    Pos getPosition() const;
    Pos getNextPosition() const;
    Pos getLastPosition() const;
	int getWidth() const;
    int getHeight() const;
	std::vector<Edge>& getPath() const;
	Pos getDestination() const;
    bool atDestination() const;
	direction getDirection() const;
	direction turningTo() const;
    direction getTurningFrom() const;
    Pos leftTurnBeginning(Pos position, int distance, direction dir);
    Pos leftTurnEnd(Pos position, int distance, direction dir);
    Pos rightTurnBeginning(Pos position, int distance, direction dir);
    Pos rightTurnEnd(Pos position, int distance, direction dir);
	bool nextTurnIsLeft();
    bool lastTurnWasLeft();

	virtual std::string getType() const {return "(nothing)";}

private:
    ///Private members
    std::vector<Edge> path = std::vector<Edge>();
    Pos nextPosition;
    Pos position;
    Pos lastPosition;
    int width;
    int height;
    direction comingFrom = noDir; //Must assign to avoid segfault
    direction turningFrom = noDir; //Must assign to avoid segfault
    Pos destination;
};

class Car : public Vehicle
{
public:
    ///Constructor
    Car() : Vehicle(8, 12) { } // 6, 12

    ///Member functions
    virtual std::string getType() const { return "car"; }
};

class Truck : public Vehicle
{
public:
    ///Constructor
    Truck() : Vehicle(10, 16) { }

    ///Member functions
    virtual std::string getType() const { return "truck"; }
};

class Bike : public Vehicle
{
public:
    ///Constructor
    Bike() : Vehicle(6, 10) { }

    ///Member functions
    virtual std::string getType() const { return "bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
