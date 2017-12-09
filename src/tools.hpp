#ifndef TOOLS_HPP_INCLUDED
#define TOOLS_HPP_INCLUDED


enum direction
{
    north,
    east,
    south,
    west
};

enum tileType
{
	grass,
	building,
	road
};


class Pos {
public:
	Pos(int givenX = 0, int givenY = 0): x(givenX), y(givenY) {};
	int x;
	int y;
	bool operator==(const Pos a) const{
		if(x == a.x && y == a.y) {
			return true;
		} else {
			return false;
		}
	}
};


#endif
