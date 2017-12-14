#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <memory> //ptr

#include "edge.hpp"
#include "vehicle.hpp"
#include "vertex.hpp"
#include "graph.hpp"

class Edge;

class Graph;

class Vehicle
{
public:
    ///Constructor
    Vehicle(int max_spd, int w, int h) :
        max_speed(max_spd), width(w), height(h), destination(Pos(0,0)) {}

    ///Destructor
    virtual ~Vehicle() {}
    
    ///Copy constructor, Ro3
    Vehicle(const Vehicle& copyFrom) = default;
    
    ///Copy assignment, Ro3
    Vehicle& operator=(const Vehicle& copyFrom) = default;

    ///Member functions
    void moveTowards(Pos givenPos);
    void move(Graph& graph);
    void moveAlong();
    void setPosition(Pos givenPos);
    void setNextPosition(Pos givenPos);
    void setPath(std::vector<Edge> givenPath);
    void setDestination(Pos dest);
    Pos getPosition() const;
    int getWidth() const;
    int getHeight() const;
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
    int width;
    int height;
    direction comingFrom = north; //Must assign to avoid segfault
    Pos destination;
};

class Car : public Vehicle
{
public:
    ///Constructor
    Car() : Vehicle(60, 28, 18) { }

    ///Member functions
    virtual std::string getType() const { return "Car"; }
};

class Truck : public Vehicle
{
public:
    ///Constructor
    Truck() : Vehicle(40, 38, 20) { }

    ///Member functions
    virtual std::string getType() const { return "Truck"; }
};

class Bike : public Vehicle
{
public:
    ///Constructor
    Bike() : Vehicle(70, 14, 6) { }

    ///Member functions
    virtual std::string getType() const { return "Bike"; }
};

#endif // VEHICLE_HPP_INCLUDED
