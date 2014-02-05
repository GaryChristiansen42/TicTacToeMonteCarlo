#include "TicTacToe.h"

Move::Move()
{
	this->r = 0;
	this->c = 0;
}

Move::Move(int r, int c)
{
	this->r = r;
	this->c = c;
}

Board::Board(Player computer)
{
	positions = new int*[BOARD_SIZE];
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		positions[r] = new int[BOARD_SIZE];
		memset(positions[r], 0, BOARD_SIZE*sizeof(int));
	}

	turn = X;
	this->computer = computer;
}

Board::~Board()
{
	for(int r = 0; r < BOARD_SIZE; r++)
		delete[] positions[r];
	delete[] positions;
}

Board* Board::clone()
{
	Board* b = new Board(this->computer);
	b->positions = new int*[BOARD_SIZE];
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		b->positions[r] = new int[BOARD_SIZE];
		memcpy(b->positions[r], positions[r], BOARD_SIZE*sizeof(int));
	}

	b->turn = turn;
	b->computer = computer;
	return b;
}

bool Board::isValidMove(Move m)
{
	if(m.c >= BOARD_SIZE || m.r >= BOARD_SIZE || m.r < 0 || m.c < 0)
		return false;
	else if(positions[m.r][m.c] != 0)
		return false;
	return true;
}

bool Board::isGameOver(GameResult *result)
{
	//any horizontal wins	
	for(int row = 0; row < BOARD_SIZE; row++)
	{
		Player firstPos = (Player)positions[row][0];
		if(firstPos == Empty)
			continue;
	
		bool allSame = true;
		for(int column = 1; column < BOARD_SIZE; column++)
			if(positions[row][column] != firstPos)
				allSame = false;
	
		if(allSame)
		{
			(*result) = (firstPos == X ? XWon : OWon);
			return true;
		}
	}

	//any vertical wins	
	for(int column = 0; column < BOARD_SIZE; column++)
	{
		int firstPos = positions[0][column];
		if(firstPos == 0)
			continue;
	
		bool allSame = true;
		for(int row = 1; row < BOARD_SIZE; row++)
			if(positions[row][column] != firstPos)
				allSame = false;
	
		if(allSame)
		{
			(*result) = (firstPos == X ? XWon : OWon);
			return true;
		}
	}

	//any diagonal wins - top left to bottom right
	int firstPos = positions[0][0];
	if(firstPos != 0)
	{
	
		bool allSame = true;
		for(int row = 1, column = 1; row < BOARD_SIZE; row++, column++)
			if(positions[row][column] != firstPos)
				allSame = false;
			
		if(allSame)
		{
			(*result) = (firstPos == X ? XWon : OWon);
			return true;
		}
	}

	//any diagonal wins - top right to bottom left
	firstPos = positions[0][BOARD_SIZE-1];
	if(firstPos != 0)
	{
		bool allSame = true;
		for(int row = 1, column = BOARD_SIZE-2; row < BOARD_SIZE; row++, column--)
			if(positions[row][column] != firstPos)
				allSame = false;
			
		if(allSame)
		{
			(*result) = (firstPos == X ? XWon : OWon);
			return true;
		}
	}

	bool moveLeft = false;
	for(int row = 0; row < BOARD_SIZE; row++)
		for(int column = 0; column < BOARD_SIZE; column++)
			if(positions[row][column] == 0)
				moveLeft = true;
			
	if(!moveLeft)
	{
		(*result) = Draw;
		return true;
	}
	(*result) = None;
	return false;
}

void Board::makeMove(Move m)
{
	positions[m.r][m.c] = turn;
	turn = (turn == X ? O : X);
}

void Board::makeRandomMove()
{
	Move m(-1, -1);
	do
	{
		m.r = rand() % BOARD_SIZE;
		m.c = rand() % BOARD_SIZE;
	} while(!isValidMove(m));

	makeMove(m);
}

GameResult Board::playRandomGame()
{
	GameResult result;
	while(!isGameOver(&result))
	{
		makeRandomMove();
	}

	return result;
}

void Board::show()
{
	stringstream boardString;

	for(int row = 0; row < BOARD_SIZE+1; row++)
	{
		for(int column = 0; column < BOARD_SIZE+1; column++)
		{
			if(row == BOARD_SIZE && column == BOARD_SIZE)
			{
				boardString << "  ";
			}
			else if(row == BOARD_SIZE)
				boardString << column << " ";
			else if(column == BOARD_SIZE)
				boardString << row << " ";	
			else
			{
				switch(positions[row][column])
				{
				case 0:
					boardString << "- ";
					break;
				case 1:
					boardString << "X ";
					break;
				case 2:
					boardString << "O ";
					break;
				}
			}
		}
	
		boardString << "\n";
	}

	cout << boardString.str();
}