#include <sstream>
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

#define BOARD_SIZE 3

enum GameResult
{
	None = -1,
	Draw = 0,
	XWon = 1,
	OWon = 2
};

enum Player
{
	Empty = 0,
	X = 1,
	O = 2
};

struct Move
{
	int r;
	int c;

	Move();
	Move(int r, int c);
};

class Board
{
public:
	int** positions;
	Player turn;
	Player computer;

	Board(Player computer);
	~Board();

	Board* clone();

	bool isValidMove(Move m);

	bool isGameOver(GameResult *result);

	void makeMove(Move m);

	void makeRandomMove();

	GameResult playRandomGame();

	void show();
};
