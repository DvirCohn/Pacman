#pragma once

#include "GameObjects.h"
#include "Board.h"
#include <vector>
#include <queue>


class Board;

class Ghost : public GameObjects
{

public:
	Ghost() : GameObjects('M', 3){}
	void smartDirMove(Board& board, Point pacPos);
	bool isValidStep(const std::vector<std::vector<bool>> visit, int row, int col, Board& board);
	Point BFS(Board& board, std::vector<std::vector<bool>> visit, int row, int col);
	virtual void moveObject(Board& board);// calls point move's func.

};



