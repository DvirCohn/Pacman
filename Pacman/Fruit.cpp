#include "Fruit.h"
#include <time.h>





void Fruit::setfigure()
{
	char fig;
	fig = '0' + (rand() % 5 + 5);
	GameObjects::setFigure(fig);
}

void Fruit::randNsetValidpos(const Board& B)
{
	int x, y;
	bool isvalid = false;

	while (!isvalid)
	{
		x = rand() % B.getBoardWidth();
		y = rand() % B.getBoardheight();

		if (!(x >= B.getlegend().getX() && x<=(B.getlegend().getX() + 19) && y >= B.getlegend().getY() && y <= B.getlegend().getY() + 2)) // checking if the rand point is not in the legend scope
		{
			if (B.getNote(y*(B.getBoardWidth()+1)+x) != WALL)
			{
				isvalid = true;
			}
		}
	}
	setPoint(x, y);
}

void Fruit::editwake(bool gotEaten)
{
	if (gotEaten)
	{
		isAwake = 0;
		return;
	}

	isAwake++;
}



void Fruit::moveObject(Board& board)
{



	editwake(); // isawake++;

	if (isAwake < IS_WAKEUP) { return;} //if fruit is < (not) wakeup, Dont move.


	if (isAwake == IS_WAKEUP) // //if fruit is == (true) wakeup, get random position.

	{
		randNsetValidpos(board);
		setfigure();
	}


	int& x = getPoint().getX();
	int& y = getPoint().getY();
	int& dir = getDirection();
	int lstX = x, lstY = y;

	switch (dir)
	{
		

	case UP:
	{

		if (board.getNote((y - 1) * (board.getBoardWidth() + 1) + x) != WALL)
		{
			if (y == 0)
			{
				dir = DOWN;
			}
			else
				y--;
		}
		else
		{
			while (dir == UP)
			{
				dir = rand() % 4 + 1;
			}
		}


		break;

	}
	case DOWN:
	{
		if (board.getNote((y + 1) * (board.getBoardWidth() + 1) + x) != WALL)
		{
			if (y == (board.getBoardheight() - 1))
			{
				dir = UP;
			}
			else
				y++;
		}
		else
		{
			while (dir == DOWN)
			{
				dir = rand() % 4 + 1;
			}
		}


		break;

	}
	case LEFT:
	{
		if (board.getNote(y * (board.getBoardWidth() + 1) + (x - 1)) != WALL)
		{
			if (x == 0)
			{
				dir = RIGHT;
			}
			else
			{
				x--;
			}
		}
		else
		{
			while (dir == LEFT)
			{
				dir = rand() % 4 + 1;
			}
		}

		break;
	}


	case RIGHT:
	{
		if (board.getNote(y * (board.getBoardWidth() + 1) + (x + 1)) != WALL)
		{
			if (x == (board.getBoardWidth() - 1))
			{
				dir = LEFT;

			}
			else
			{
				x++;
			}
		}
		else
		{
			while (dir == RIGHT)
			{
				dir = rand() % 4 + 1;
			}
		}

		break;

	}
	

	}


	draw(board, lstX, lstY);

	if (isAwake == FRUIT_IS_DEAD) // fruit disappeard and we print the letter that supposed to be on board instead of fruit.
	{
		int x = getPoint().getX();
		int y = getPoint().getY();
		gotoxy(x, y);
		std::cout << board.getNote((board.getBoardWidth() + 1) * y + x);
		editwake(true); // if is 10, reset and go to sleep for 10 rounds;
	}
}


