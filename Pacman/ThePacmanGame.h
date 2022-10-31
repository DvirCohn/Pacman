#pragma once
#include "Pacman.h"
#include"io_utils.h"
#include "Board.h"
#include "Ghost.h"
#include "Fruit.h"

enum LEVEL { BEST = 1, GOOD, NOVICE };
enum MENU { PLAY = 1, SINGLE_BOARD = 1,MULTI_BOARDS = 2,INSTRUCTIONS = 8,EXIT = 9 };

class ThePacmanGame
{

	Board B;
	std::vector<std::string> filenames;
	std::vector<GameObjects*> creaturesArr;
	int gameLevel;
	enum { ESC = 27 };

public:

	ThePacmanGame()
	{
		creaturesArr.push_back(new Pacman);
		creaturesArr.push_back(new Fruit);
	};
	void init(); // initializing the pacman coord and keys and the coord of the ghosts. 
	void run(); // manage the course of the gmae.	
	void checkCollision(); // check if there was a collision between pacman and one of the ghosts.	
	void menu(bool& isFinish,int& choose, int& boardNumber);
	void printWinLose(bool flag)const;
	void printLive(int countLive);
	void getFilesNames();
	bool checkIfGameEnded(int& screenIndex, bool isSingleBoard);
	bool checkWorL(bool isSingleBoard)const;
	void printLegend();
	void resetGame(int& screenindex, bool newgame = true); // reset overall score and ghost vector.
	int chooseLevel();
	void setLevel(int _level) { gameLevel = _level; };
	int getLevel()const { return gameLevel; };
	void ghostChangeDirRandomly(Ghost& G);
	void ClearGhosts();
	void printPacManLogo()const;
	void betweenBoards( bool stillPlay)const;
	void printInstructions()const;
};

