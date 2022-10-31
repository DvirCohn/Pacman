#pragma once

#include <iostream>
#include "io_utils.h"


class Board;

class Point
{
	int x, y;

public:
	Point(int _x=1, int _y=1) : x(_x), y(_y) {}//ctor

	void setPoint(int _x , int _y ) 
	{
		x = _x; y = _y;	
	}
	
	int& getX() { return x; };
	int& getY() { return y; };
	bool operator ==(const Point& p2)
	{
		if (x == p2.x && y == p2.y)
			return true;
		else
			return false;
	}


};
