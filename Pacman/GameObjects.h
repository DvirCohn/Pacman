#pragma once
#include "Point.h"

enum Directions { STAY, DOWN, LEFT, UP, RIGHT };

class Board;
class GameObjects
{
	
	Point coord, firstpos;
	char figure;
	int direction;
	 
public:
	GameObjects(char figure, int dir)//ctor
	{
		setFigure(figure);
		setDirection(dir);
	}
	int& getDirection() 
	{
		return direction;
	}
	void setDirection(int dir) 
	{
		direction = dir;
	}
	char getFigure() const
	{
		return figure;
	}
	void setFigure(char _figure)
	{
		figure = _figure;
	}
	void setPoint(int xpos, int ypos)
	{
		coord.setPoint(xpos, ypos);
	}
	Point& getPoint()
	{
		return coord;
	}
	void setFirstPoint(int xpos, int ypos)
	{
		firstpos.setPoint(xpos, ypos);
	}
	Point& getFirstPoint()
	{
		return firstpos;
	}
	void move(Board& board);
	virtual void moveObject(Board& board) {}
	void draw(Board& board, int lstX, int lstY); // printing pacman/ghosts on screen, and the changes on board (breadcrumbs which got eaten).
};

