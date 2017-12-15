#ifndef TOOLS_HPP_INCLUDED
#define TOOLS_HPP_INCLUDED

//Force coordinates to a grid
/*int forceToGrid(int a) {
    return a / 64;
}*/

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
