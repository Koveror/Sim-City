#ifndef TOOLS_HPP_INCLUDED
#define TOOLS_HPP_INCLUDED

//enumerations for directions
typedef enum
{
    north,
    east,
    south,
    west,
    noDir
} direction;

//enumerations for different tiles (vertices)
typedef enum
{
    grass,
    building,
    road
} tileType;

//helper class Pos to determine both grid locations and exact locations of vertices and vehicles
class Pos {
public:
    Pos(int givenX = 0, int givenY = 0): x(givenX), y(givenY) {};
    bool operator==(const Pos a) const{
        return (x == a.x && y == a.y);
    }

    ///Public members
    int x;
    int y;
};


#endif
