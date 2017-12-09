#ifndef TOOLS_HPP_INCLUDED
#define TOOLS_HPP_INCLUDED

//enumerations for directions
typedef enum
{
    north,
    east,
    south,
    west
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
		if(x == a.x && y == a.y) {
			return true;
		} else {
			return false;
		}
	}

	///Public members
    int x;
	int y;
};


#endif
