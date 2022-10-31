#pragma once
#include  "GameObjects.h"


class Pacman : public GameObjects
{

	char arrowKeys[5];
	int lives;
	int score;
	int curScore;

public:

	Pacman() : GameObjects('C', 0)//ctor
	{
		lives = 3;
		score = 0;
		curScore = 0;
		setArrowKeys("sxawd");

	}
	virtual void moveObject(Board& board); // calls point move's func.
	void setArrowKeys(const char* keys); // for initializing the pacman keys.
	int CheckDirection(char key)const; // connect the key, which was enters by player, the right direction.
	void setDirection(int dir) { GameObjects::setDirection(dir);} // edits dir.
	void setPoint(int xpos, int ypos)
	{
		GameObjects::setPoint(xpos, ypos);	
	}
	void editScore(bool isNewGame = false, int fruit = 0);
	void resetcurscore() { curScore = 0; }
	int getcurscore() { return curScore; }
	int getScore()const
	{
		return score;
	}
	void editLives(int newGame = 0) // func being called each collision between pacman and ghost.
	{ 
	lives--;

	if (newGame != 0) // in case of new game, lives reset to 3.
		lives =3;

	
	}
	int getLive()const { return lives; }

};
