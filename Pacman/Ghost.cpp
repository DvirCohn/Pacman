#include "Ghost.h"
#include "Point.h"

void Ghost::smartDirMove(Board& board, Point pacPos)
{
    int xPacPos = pacPos.getX(), yPacPOs = pacPos.getY();
    int xGhostPos = getPoint().getX() , yGhostPos = getPoint().getY();

    std::vector<std::vector<bool>> visit(board.getBoardheight() + 1, std::vector<bool>(board.getBoardWidth() + 1, false));
    Point newPos = BFS(board, visit, yPacPOs, xPacPos);

    //newPos is to the left
    if (newPos.getX() == xGhostPos - 1) setDirection(LEFT);

    //newPos is to the right
    else if (newPos.getX() == xGhostPos + 1) setDirection(RIGHT);

    //newPos is to the up
    else if (newPos.getY() == yGhostPos - 1) setDirection(UP);

    //newPos is to the down
    else setDirection(DOWN);
}

bool Ghost::isValidStep(const std::vector<std::vector<bool>> visit, int y, int x, Board& board)
{
	if (x<0 || y<0)
	{
		return false;
	}

	// If cell is bounds
	if (y > board.getBoardheight() || x > board.getBoardWidth())
		return false;

	// If cell is bounds
	if (y == 0 || x == 0 || board.getNote(y * (board.getBoardWidth() + 1) + x) == WALL || board.isTunnel(x, y))
		return false;

	// If cell is already visited
	if (visit[y][x])
	    return false;
	

    // Otherwise
    return true;
}



Point Ghost::BFS(Board& board, std::vector<std::vector<bool>> visit, int row, int col)
{
    int test = 0;
    Point ghostPos = getPoint();
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    // Stores indices of the matrix cells
    std::queue<Point> q;
    int xGhost = getPoint().getX();
    int yGhost = getPoint().getY();
    // Mark the starting cell as visited and push it into the queue
    q.push(Point{ col, row });
    visit[row][col] = true;

    // Iterate while the queue is not empty
    while (!q.empty()) {

        Point cell = q.front();
        int x = cell.getX();
        int y = cell.getY();

        q.pop();

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) 
        {
            int adjy = y + dRow[i];
            int adjx = x + dCol[i];
            Point temp = Point(adjx, adjy);
            if (temp == ghostPos)
                return Point(x, y);
            else if (isValidStep(visit, adjy, adjx, board)) {
                q.push({ adjx, adjy });
                visit[adjy][adjx] = true;
            }
        }
    }

    // if short way has not found - return the curr position
    // the ghost dir will be down
    return getPoint();
}

 void Ghost:: moveObject(Board& board) 
{

	 srand(time(NULL));

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
 }

