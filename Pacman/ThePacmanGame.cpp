#include"ThePacmanGame.h"
#include<filesystem>
#include <fstream>
#include <string>



void ThePacmanGame::init()
{
	(*creaturesArr[0]).setPoint((*creaturesArr[0]).getFirstPoint().getX(), (*creaturesArr[0]).getFirstPoint().getY()); // initial pac pos to first position
	(*creaturesArr[0]).setDirection(STAY);
	if (creaturesArr.size()>2)
	{
		for (int i = 2; i < creaturesArr.size(); i++)
		{
			(*creaturesArr[i]).setPoint((*creaturesArr[i]).getFirstPoint().getX(), (*creaturesArr[i]).getFirstPoint().getY());// initial ghost pos to first position
			(*creaturesArr[i]).setDirection(UP);
		}
	}
	
}

void ThePacmanGame::run()
{
	srand(time(NULL));

	bool finish = false;
	char key = 0;
	int dir;
	int speed = 0;
	int flag = 1, screenIndex=0;
	bool newgame = true;
	int choose, boardNumber;
	while(true)
	{

	if(newgame)
	{ 
	menu(finish, choose, boardNumber);
	if (finish)
	return;
	newgame = false;
	screenIndex = 0;
	}
	//---------Choosing if play on single board or all boards---------

	if (choose == SINGLE_BOARD) // single board
	{
	B.importBoard(creaturesArr, filenames[boardNumber-1]);
	}
	else if(choose == MULTI_BOARDS)
	{
	B.importBoard(creaturesArr, filenames[screenIndex]); 
	}

	//--------------------------------------------------------------

	Pacman* pac;
	pac = dynamic_cast<Pacman*>(creaturesArr[0]);

	gotoxy(0, 0);
	B.printBoard();
	do {
		hideCursor();
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)// PAUSE
			{
				clear_screen();
				do
				{
					while (flag ==1)
					{
						std::cout << "Game paused, press ESC again to continue...";
						flag++;
					}
				} while (!_kbhit() && _getch() != ESC);

				flag--;
				clear_screen();
				B.printBoard();
				Sleep(350);

			}
			
			if ((dir = pac->CheckDirection(key)) != -1)
				(*creaturesArr[0]).setDirection(dir);
		}
		
		creaturesArr[0]->move(B);
		checkCollision();
		
		printLegend();

		if (speed % 2 == 0)// speed of ghosts.
		{
			for( int i = 2; i< creaturesArr.size(); i++)
			{
				Ghost* G;
				G = dynamic_cast<Ghost*>(creaturesArr[i]);

				if (gameLevel == BEST || (gameLevel == GOOD && speed <=15))
				{
					G->smartDirMove(B, pac->getPoint());
					if (speed == 10) { ghostChangeDirRandomly(*G); }; // TO TAKE CARE OF IF THE GHOSTS ARE WALKING TOGETHER AND NEVER GET APART.
				}
				if (speed == 16 && gameLevel == GOOD) {ghostChangeDirRandomly(*G);}
				
				creaturesArr[i]->move(B);

 			}
			checkCollision();
			if (speed%FRUIT_SPEED==0)// speed of fruit.
			{
				creaturesArr[1]->move(B); // move fruity if is a wake.
			}
		}
		speed++;
		if (speed == 20) { speed = 0; }
		checkCollision();
		
		Sleep(150);
		
	} while (pac->getLive()>0 && pac->getcurscore()<B.getBreadCrumbs());
	

	newgame = checkIfGameEnded(screenIndex, choose == SINGLE_BOARD); // return true if game ended.
	
	if (newgame) // if game ended, check if W or L.
	{
		printWinLose(checkWorL(choose == SINGLE_BOARD));
	}
	betweenBoards(newgame);
	resetGame(screenIndex, newgame); // if new game, reset overall score. anyway reset curscore, cls, scrnindx++ and reset ghost vec.

	}
}

void ThePacmanGame::resetGame(int& screenindex, bool newgame)
{
	Pacman* pac;
	pac = dynamic_cast<Pacman*>(creaturesArr[0]);
	if (newgame)
	{
		pac->editScore(newgame); // reset score to 0.
	}
	pac->resetcurscore();
	clear_screen();
	ClearGhosts(); // eliminate all ghosts in creaturesArr.
	B.clearBoard();
	if (screenindex == filenames.size()) //in case of playing with all boards reset the screen index.
		screenindex = 0;
}
void ThePacmanGame::ClearGhosts()
{
	for (int i = 2; i < creaturesArr.size(); i++)
	{
		creaturesArr.pop_back();
	}
}


void ThePacmanGame::printLegend()
{
	Pacman* pac;
	pac = dynamic_cast<Pacman*>(creaturesArr[0]);

	gotoxy(B.getlegend().getX(), B.getlegend().getY()); 
	std::cout << "score : " << pac->getScore();
	gotoxy(B.getlegend().getX(), B.getlegend().getY() + 1);
	std::cout << "lives : ";  printLive(pac->getLive());
}

void ThePacmanGame :: checkCollision()
{

	for (int i = 1; i < creaturesArr.size(); i++)// checking collision between pac-ghost,pac-fruit.
	{                                          
		if (creaturesArr[0]->getPoint() == creaturesArr[i]->getPoint()) 
		{
			if (typeid(*(creaturesArr[i])) == typeid(Ghost)) 
			{
				dynamic_cast<Pacman*>(creaturesArr[0])->editLives();
				clear_screen();
				gotoxy(0, 0);
				B.printBoard();
				init();
				Sleep(400);
				return;
			}
			else if (typeid(*(creaturesArr[i])) == typeid(Fruit))
			{
				Fruit* fruity;
				fruity = dynamic_cast<Fruit*>(creaturesArr[i]);

				if (fruity->getwake() >= 5)
				{
					fruity->editwake(true);// fruit go to sleep
					
					dynamic_cast<Pacman*>(creaturesArr[0])->editScore(false, fruity->getFigure() - '0');
				}
			}
				
		}

		if (i > 1)// checking fruit-ghost collision
		{
			if (creaturesArr[1]->getPoint() == creaturesArr[i]->getPoint())

				dynamic_cast<Fruit*>(creaturesArr[1])->editwake(true);// fruit go to sleep
		}
		
	}
}

 
void ThePacmanGame::menu(bool& isFinish,int& choose, int& boardNumber)
{
	int choise;
	printPacManLogo();
	if (filenames.size() == 0)// in case of 0 boards files in the project folder
	{
		std::cout << "There are no available Board files in folder.\n"
			"Please insert files and come back to play." << std::endl;
		
		isFinish = true;
		return;
	}

	do
	{
		std::cout << "(1) Start a new game\n";
		std::cout << "(8) Present instructionsand keys\n";
		std::cout << "(9) EXIT\n";
		std::cin >> choise;
		if (choise == INSTRUCTIONS)
		{
			printInstructions();
			while(!_kbhit()){}
		}
		clear_screen();
		gotoxy(0, 0);
		
	} while (choise != PLAY && choise != EXIT);


		if (choise == PLAY)
		{
			do {

				clear_screen();
				std::cout << "Would you like to play with single board or multiple boards?\n";
				std::cout << "1. Single Board\n2. Multiple boards\n";

				std::cin >> choose;

				clear_screen();

				if (choose == SINGLE_BOARD)
				{
					
					do
					{ 
					std::cout << "Please choose your board\n";
					for (int i = 0; i < filenames.size(); i++)
					{
						std::cout << i + 1 << ". " << filenames[i] << ".\n";
					}
					std::cin >> boardNumber;
					clear_screen();
					} while (boardNumber > filenames.size() || boardNumber < 1);

				}

			} while (choose != SINGLE_BOARD && choose != MULTI_BOARDS);

				gameLevel = chooseLevel();
				clear_screen();
				
				dynamic_cast<Pacman*>(creaturesArr[0])->editLives(choise);// lives initial to 3 again.
		}
		if (choise == EXIT)
		{
			isFinish = true;
		}

	
}


bool ThePacmanGame::checkIfGameEnded(int& screenIndex, bool isSingleBoard)
{
	screenIndex++;
	if (screenIndex == filenames.size()) // no more screen available.
		return true;
	if (isSingleBoard) // one board game.
		return true;
	if (dynamic_cast<Pacman*>(creaturesArr[0])->getLive() == 0) // no more lives :(
		return true;
	else
		return false;
}
void ThePacmanGame::printWinLose(bool flag)const
{
	clear_screen();

	if (flag)
	{
		gotoxy(0,0);

		std::cout <<
			"*******************************************\n"
			"*                                         *\n"
			"*       *         *  ***    *     *       *\n"
			"*        *   *   *    *     * *   *       *\n"
			"*         * * * *     *     *   * *       *\n"
			"*          *   *     ***    *     *       *\n"
			"*                                         *\n"
			"*                                         *\n"
			"*        !!!!!!!!!!!!!!!!!!!!!!!!!!!      *\n"
			"*                                         *\n"
			"*                                         *\n"
			"*                                         *\n"
			"*******************************************\n"<< std::endl;

	}
	else
	{
		gotoxy(0,0);

		std::cout <<
			"********************************************\n"
			"*  ******   ******   *        *   ******   *\n"
			"*  *        *    *   * *    * *   *        *\n"
			"*  *  * *   ******   *    *   *   ******   *\n"
			"*  *    *   *    *   *        *   *        *\n"
			"*  ******   *    *   *        *   ******   *\n"
			"*                                          *\n"
			"*  ******   *      *   ******    ******    *\n"
			"*  *    *   *      *   *         *    *    *\n"
			"*  *    *   *      *   ******    *****     *\n"
			"*  *    *     *   *    *         *   *     *\n"
			"*  ******       *      ******    *    *    *\n"
			"*                                          *\n"
			"********************************************\n"<< std::endl;
	}

	gotoxy(0,15);
	std::cout << "Press any key to continue..";
	while (!_kbhit()) {}
	int temp = _getch();
}

void ThePacmanGame::printLive(int countLive)
{
	int i;
	for ( i = 0; i < countLive; i++)
	{
		std::cout << " <3";
	}
}

void ThePacmanGame:: getFilesNames()
{
	std::string temp;

	for (const auto& p :std::filesystem::directory_iterator("."))
	{
		if (p.path().string().ends_with(".screen"))
		{
			temp = p.path().string();
			temp.erase(0, 2);
			filenames.push_back(temp);
		}


	}
	
	std::sort(filenames.begin(), filenames.end());
}

bool ThePacmanGame::checkWorL(bool isSingleBoard)const
{
	if (isSingleBoard && dynamic_cast<Pacman*>(creaturesArr[0])->getLive() > 0)
		return true;
	if (!isSingleBoard && dynamic_cast<Pacman*>(creaturesArr[0])->getLive() > 0)
		return true;

	return false;
	
}

int ThePacmanGame::chooseLevel()
{
	int elect;
	do
	{
		std::cout << "Please select game level :\n"
			<< "(1) BEST.\n"
			<< "(2) GOOD.\n"
			<< "(3) NOVICE.\n" << std::endl;

		std::cin >> elect;
		clear_screen();
	} while (elect != BEST && elect != GOOD && elect != NOVICE);
	return elect;
	
}

void ThePacmanGame:: ghostChangeDirRandomly(Ghost &G)
{
	int dir;
	dir = rand() % 4 + 1;
	while (dir == G.getDirection())
	{
		dir = rand() % 4 + 1;
	}
	G.setDirection(dir);

}

void ThePacmanGame::printPacManLogo()const
{
	
	std::ifstream pacLogoFile;
	pacLogoFile.open("pacmanlogo.txt");
	std::string tempStr;



	while (!pacLogoFile.eof())
	{
		getline(pacLogoFile, tempStr);
		std::cout << tempStr;
		std::cout << std::endl;
	}


	pacLogoFile.close();
	std::cout << "Press any key to continue..";
	while (!_kbhit()) {}
	int temp = _getch();

	clear_screen();

}

void ThePacmanGame::betweenBoards(bool stillPlay)const
{
	clear_screen();
	gotoxy(10, 3);
	if (!stillPlay)
	{
		std::cout << "Well done !!\n Get ready for the next board\n";
		std::cout << "Press any key to continue..";
		while (!_kbhit()) {}
		int temp = _getch();

		clear_screen();
	}
	
	
}

void ThePacmanGame::printInstructions()const
{
	clear_screen();
	gotoxy(0, 0);
	std::cout << "    Key-list:     " << std::endl << std::endl
		<< " KEY      Direction" << std::endl
		<< " ---      -----------" << std::endl
		<< " 'D/w'          UP  " << std::endl
		<< " 'X/x'           Down" << std::endl
		<< " 'D/d'         Right" << std::endl
		<< " 'A/a'          Left" << std::endl
		<< " 'S/s'          Stay" << std::endl << std::endl << std::endl
		<< " Game instruction:" << std::endl
		<< "The player controls Pac-Man ('C'),"
		"who must eat all the breadcrumbs ('*')\ninside an enclosed maze while avoiding two ghosts('M').\nThe game has 3 difficulty levels:\n" <<
		"(1) BEST - Ghosts are chasing the Pacman all game long.\n"
		"(2) GOOD - Ghosts are chasing the Pacman for ~20 moves.\n"
		"(3) NOVICE - Ghosts move randomlay on board." << std::endl
		<< "PRESS ANY KEY TO GET BACK TO MENU" << std::endl;
}