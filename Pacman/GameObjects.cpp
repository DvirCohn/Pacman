
#include"GameObjects.h"
#include "Board.h"


void GameObjects::move(Board& board)
{
	moveObject(board);
}


void GameObjects::draw(Board& board, int lstX, int lstY)
{
	char let;
	int x = coord.getX();
	int y = coord.getY();

	gotoxy(x, y);
	std::cout << figure; // printing creature.

	gotoxy(lstX, lstY);
	let = board.getNote((lstY) * (board.getBoardWidth() + 1) + lstX); // get and print the last letter from board.
	if ((x == lstX && y == lstY) == false)
	{
		std::cout << let;
	}

}