#pragma once
#include <iostream>
#include <vector>
#include "Pacman.h"
#include "Ghost.h"


class Ghost;

const char WALL = 219;

class Board 
{
	Point legend;
	char board[81*25];
	int BoardWidth;
	int Boardheight;
	int breadCrumbs;
	

public:
	
	Board();

	char  getNote(int pos) const; // func that get location on board and returned you the letter in that position on board.
	void const printBoard ();
	void editBoard(int pos); // get location on board and puts there 'Space'.

	void importBoard(std::vector<GameObjects*>& creaturesArr, const std::string& screenName);
	void clearBoard();
	void setBoardWidth(int width) { BoardWidth = width; }
	int getBoardWidth() const { return BoardWidth; }
	void setBoardheight(int height) { Boardheight = height; }
	int getBoardheight() const{ return Boardheight; }
	Point getlegend()const { return legend; }
	int getBreadCrumbs()const { return breadCrumbs; }
	bool isTunnel(int x, int y) const;
};
//