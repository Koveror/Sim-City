#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <memory> //ptr

#include "edge.hpp"
#include "vehicle.hpp"
#include "vertex.hpp"
#include "graph.hpp"
//#include "dijkstra.hpp"

class Edge;

class Graph;

class Vehicle
{
public:
    ///Constructor
    Vehicle(int max_spd, int l, int w) :
        max_speed(max_spd), length(l), width(w), destination(Pos(0,0)) {}

    ///Destructor
    virtual ~Vehicle() {}

    ///Member functions
    void moveTowards(Pos givenPos);
    void move(Graph& graph);
    void setPosition(Pos givenPos);
    void moveAlong();
    void setNextPosition(Pos givenPos);
    void setPath(std::vector<Edge> givenPath);
    Pos getPosition() const;
    int getLength() const;
    int getWidth() const;
    virtual std::string getType() const {return "(nothing)";}
    Pos getDestination() const;
    bool atDestination() const;

private:
    ///Private members
    std::vector<Edge> path = std::vector<Edge>();
    Pos nextPosition;
    Pos position;
    int max_speed;
    float speed = 0;
    int length;
    int width;
    direction comingFrom = north;
    Pos destination;
};

class Car : public Vehicle
{
public:
    ///Constructor
    Car() : Vehicle(60, 6, 4) { }

    ///Destructor
    virtual ~Car() {}

    ///Member functions
    virtual std::string getType() const { return "Car"; }
};

class Truck : public Vehicle
{
public:
    ///Constructor
    Truck() : Vehicle(40, 8, 4) { }

    ///Destructor
    virtual ~Truck() {}

    ///Member functions
    virtual std::string getType() const { return "Truck"; }
};

class Bike : public Vehicle
{
public:
    ///Constructor
    Bike() : Vehicle(70, 3, 2) { }

    ///Destructor
    virtual ~Bike() {}

    ///Member functions
    virtual std::string getType() const { return "Bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
