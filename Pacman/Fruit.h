#pragma once
#include "Board.h"
#include "GameObjects.h"


enum fruitStatus{FRUIT_SPEED = 5,IS_WAKEUP =5, FRUIT_IS_DEAD = 10};

class Fruit : public GameObjects
{
	int isAwake;

public:
	Fruit() : GameObjects('5', 3) { isAwake = 0; };

	void setfigure();
	void randNsetValidpos(const Board& B);
	int getwake() const { return isAwake; }
	void editwake(bool gotEaten = false);
	virtual void moveObject(Board& board);
};

