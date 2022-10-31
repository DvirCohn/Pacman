#include "Pacman.h"
#include "Board.h"


void Pacman::setArrowKeys(const char* keys) // need that other func call this func
{ // "wzasd"
	arrowKeys[0] = keys[0];//w
	arrowKeys[1] = keys[1];//z
	arrowKeys[2] = keys[2];//a
	arrowKeys[3] = keys[3];//s
	arrowKeys[4] = keys[4];//d
}

int Pacman::CheckDirection(char key)const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i]|| key == (arrowKeys[i]- ('a' -'A')))
			return i;
	}
	return -1;
}

void Pacman::moveObject(Board& board)
{
	
	int& x = getPoint().getX();
	int& y = getPoint().getY();
	int lstX = x, lstY = y;
	char let;

	let = board.getNote((y) * (board.getBoardWidth() + 1) + x);
	if (let == '*')
	{
		editScore();
	}

	board.editBoard((y) * (board.getBoardWidth() + 1) + x); //editing the board in case of pacman with ' '.


	switch (getDirection())
	{

	case UP:
	{
		if (board.getNote((y - 1) * (board.getBoardWidth() + 1) + x) != WALL)
			
				if (y == 0)
				{
					if (board.isTunnel(x, y))
					{
						y = board.getBoardheight() - 1;
					}
				}
				else
				{
					y--;
				}

		break;

	}
	case DOWN:
	{
		if (board.getNote((y + 1) * (board.getBoardWidth() + 1) + x) != WALL)

			if (y == (board.getBoardheight() - 1))
			{
				if (board.isTunnel(x, y))
				{
					y = 0;
				}
			}
			else
			{
				y++;

			}	
		break;

	}
	case LEFT:
	{
		if (board.getNote(y * (board.getBoardWidth() + 1) + (x - 1)) != WALL)

			if (x == 0)
			{
				if (board.isTunnel(x, y))
					x = board.getBoardWidth() - 1;
			}
			else
				x--;
			
		break;
	}


	case RIGHT:
	{
		if (board.getNote(y * (board.getBoardWidth() + 1) + (x + 1)) != WALL)
			
				if (x == (board.getBoardWidth() - 1))
				{
					if (board.isTunnel(x, y))
						x = 0;
				}
				else
					x++;
		
		break;
	}

	}

	draw(board, lstX, lstY);

}

void Pacman::editScore(bool isNewGame, int fruit)
{
	if (fruit == 0) // generally if eat breadcrumbs.
	{
		score++;
		curScore++;
	}
	else // if eat fruit, only score gained, because curscore only count breadcrumbs.
	{
		score += fruit;
	}

	if (isNewGame)
	{
		score = 0;
	}
} // func being called each time pacman eats a breadcrumbs.