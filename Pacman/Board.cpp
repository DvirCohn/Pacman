#include"Board.h"
#include<iostream>
#include "io_utils.h"
#include <fstream>
#include <string>




Board::Board()
{
	Boardheight = 0;
	BoardWidth = 0;
	clearBoard();
}



void Board::clearBoard()
{
	for (char& i : board)
	{
		i = ' ';
	}
}


void Board::importBoard(std::vector<GameObjects*>& creaturesArr,const std::string& screenName)
{
	

	std::ifstream myBoardFile;
	myBoardFile.open(screenName);
	
	if (!myBoardFile)
	{
		std::cout << "file hasn't opened";
	}

	int index = 0, countRows = 0;
	char charTemp;
	int countBreadCrumbs =0;

	// Discover The First Row Length Of The Board:
	std::string tempStr;
	getline(myBoardFile, tempStr);
	BoardWidth = tempStr.length();


	myBoardFile.seekg(0, SEEK_SET);


	while (!myBoardFile.eof())
	{
		charTemp = myBoardFile.get();


		if (charTemp == '$')
		{
			charTemp = ' ';
			creaturesArr.push_back(new Ghost());
			(creaturesArr[creaturesArr.size()-1])->setPoint((index - countRows) % BoardWidth, countRows);
			(creaturesArr[creaturesArr.size() - 1])->setFirstPoint((index - countRows) % BoardWidth, countRows);
		}
		else if (charTemp == '@')
		{
			charTemp = ' ';
			(creaturesArr[0])->setPoint((index - countRows) % BoardWidth, countRows);
			(creaturesArr[0])->setFirstPoint((index - countRows) % BoardWidth, countRows);
		}
		else if (charTemp == '%')
		{
			charTemp = ' ';
		}
		else if (charTemp == ' ')
		{
			charTemp = '*';
			countBreadCrumbs++;
		}
		else if (charTemp == '&')
		{
			legend.setPoint((index - countRows) % (BoardWidth), countRows);
			charTemp = ' ';
		}

		if (charTemp == '\n')
			countRows++;

		if (charTemp == '#')
		{
			charTemp = WALL;
		}

		board[index] = charTemp;
		index++;

	}
	Boardheight = countRows;
	breadCrumbs = countBreadCrumbs;
}


char Board::getNote(int pos)const
{
	return board[pos];


}

 const void  Board::  printBoard ()
{

	 for (char i : board)
		 std::cout << i;

}

void Board::editBoard(int pos)
{
	board[pos] = ' ';
}

bool Board::isTunnel(int x,int y)const
{

	if (x == 0 && board[(BoardWidth-1)+y*(BoardWidth+1)]!= WALL)// left to right
	{
		return true;
	}
	if (y == (Boardheight - 1) && board[x] != WALL)//down to up
		return true;
	if ( y == 0 &&  board[(Boardheight - 1) * (BoardWidth + 1) + x] != WALL)//up to down
		return true;
	if ( x == (BoardWidth - 1) &&  board[(BoardWidth+1)*y] != WALL) // right to left
		return true;
	return false;
}
