#include "Board.hpp"
#include "Tile.hpp"

int Board::checkWord(int x, int y, std::string word)
{
	Board tmpBoard = *this;

	bool validRight = false;
	bool validDown = false;

	if (tmpBoard.playWord(x, y, word, RIGHT, TRY))
		validRight = tmpBoard.checkBoard(tmpBoard);
	// std::cout << "DEBUG validRight: " << validRight << std::endl;

	tmpBoard = *this;

	if (tmpBoard.playWord(x, y, word, DOWN, TRY))
		validDown = tmpBoard.checkBoard(tmpBoard);
	// std::cout << "DEBUG validDown: " << validDown << std::endl;
	
	if (validRight && validDown)
		return (BOTH);
	else if (validRight)
		return (RIGHT);
	else if (validDown)
		return (DOWN);
	else
		throw std::invalid_argument("Error: invalid word in this context.");
}

std::string	Board::collectWord(const Board &tmpBoard, int startX, int startY, t_dir dir) const
{
		std::string fullWord;
		int currentY = startY;
		int currentX = startX;

		while (currentY > 0 && dir == DOWN && tmpBoard._board[currentY - 1][currentX].getLetter() != EMPTY)
			currentY--;
		while (currentX > 0 && dir == RIGHT && tmpBoard._board[currentY][currentX - 1].getLetter() != EMPTY)
			currentX--;

		while (currentY < BOARD_SIZE && dir == DOWN && tmpBoard._board[currentY][currentX].getLetter() != EMPTY)
			fullWord += tmpBoard._board[currentY++][currentX].getLetter();
		while (currentX < BOARD_SIZE && dir == RIGHT && tmpBoard._board[currentY][currentX].getLetter() != EMPTY)
			fullWord += tmpBoard._board[currentY][currentX++].getLetter();

		if (fullWord.size() > 1)
			std::cout << "DEBUG fullWord: " << fullWord << std::endl;
		return (fullWord);
}

bool Board::checkFrontiers(int check)
{
	// TODO
	// Implement this function to check that all the tiles
	// are connected to existing tile network.
	return (true);
}

bool Board::checkBoard(const Board &tmpBoard) const
{
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			// Check horizontal words
			if (tmpBoard._board[y][x].getLetter() != EMPTY && (x == 0 || tmpBoard._board[y][x - 1].getLetter() == EMPTY))
			{
				std::string horizontalWord = collectWord(tmpBoard, x, y, RIGHT);
				if (horizontalWord.size() > 1 && _dict.find(horizontalWord) == _dict.end())
				{
					std::cout << "DEBUG Invalid horizontal word found: " << horizontalWord << std::endl;
					return (false);
				}
			}

			// Check vertical words
			if (tmpBoard._board[y][x].getLetter() != EMPTY && (y == 0 || tmpBoard._board[y - 1][x].getLetter() == EMPTY))
			{
				std::string verticalWord = collectWord(tmpBoard, x, y, DOWN);
				if (verticalWord.size() > 1 && _dict.find(verticalWord) == _dict.end())
				{
					std::cout << "DEBUG Invalid vertical word found: " << verticalWord << std::endl;
					return (false);
				}
			}
		}
	}
	return (true);
}

bool Board::checkGameOver(void)
{
	// TODO
	// Implement thif function to check 
	// if the game is over.
	return (false);
}