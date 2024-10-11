#include "Board.hpp"
#include "Tile.hpp"

// TODO
// add check for same word played twice at same place
// and check for same word played twice?
t_dir Board::checkWord(int x, int y, std::string word)
{
	Board tmpBoard = *this;

	bool validRight = false;
	bool validDown = false;

	if (tmpBoard.playWord(x, y, word, RIGHT, PLAY))
		validRight = tmpBoard.checkBoard(tmpBoard);
	std::cout << "DEBUG validRight: " << validRight << std::endl;

	tmpBoard = *this;

	if (tmpBoard.playWord(x, y, word, DOWN, PLAY))
		validDown = tmpBoard.checkBoard(tmpBoard);
	std::cout << "DEBUG validDown: " << validDown << std::endl;
	
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

		// if (fullWord.size() > 1)
			// std::cout << "DEBUG fullWord: " << fullWord << std::endl;
		return (fullWord);
}

// TODO check that it works on edges
t_dir Board::checkFrontiers(int x, int y, std::string word, t_dir dir)
{
	Tile	currentTile;
	bool 	right = false;
	bool 	down = false;
	int		currentX = x;
	int		currentY = y;

	if (_firstTurn)
		return (BOTH);

	if (dir == RIGHT || dir == BOTH)
	{
		for (size_t i = 0; i < word.size(); i++)
		{
			currentTile = getTile(currentX, currentY);

			// std::cout << "DEBUG RIGHT current letter: " << word[i] << std::endl;

			if (i >= 0 && i <= word.size() - 1 && \
				(getTile(currentX - 1, currentY).getLetter() != EMPTY || \
				getTile(currentX + 1, currentY).getLetter() != EMPTY))
			// {
				right = true;
			// 	std::cout << "DEBUG condition 1" << std::endl;
			// 	std::cout << "DEBUG tile above: " << getTile(currentX - 1, currentY).getLetter() << std::endl;
			// 	std::cout << "DEBUG tile below: " << getTile(currentX + 1, currentY).getLetter() << std::endl;
			// }

			if (i == 0 && currentX > 0 && getTile(currentX, currentY - 1).getLetter() != EMPTY)
			// {
				right = true;
			// 	std::cout << "DEBUG condition 2" << std::endl;
			// 	std::cout << "DEBUG prefix: " << getTile(currentX, currentY - 1).getLetter() << std::endl;
			// }
			if (i == word.size() - 1 && currentY < BOARD_SIZE - 1 && getTile(currentX, currentY + 1).getLetter() != EMPTY) 
			// {
				right = true;
			// 	std::cout << "DEBUG condition 3" << std::endl;
			// 	std::cout << "DEBUG suffix: " << getTile(currentX, currentY + 1).getLetter() << std::endl;
			// }
			currentY++;
		}
		// if (right == false)
		// 	std::cout << "DEBUG right: word is not connected" << std::endl;
	}

	currentX = x;
	currentY = y;

	if (dir == DOWN || dir == BOTH)
	{
		for (size_t i = 0; i < word.size(); i++)
		{
			currentTile = getTile(currentX, currentY);

			// std::cout << "DEBUG DOWN current letter: " << word[i] << std::endl;

			if (i >= 0 && i <= word.size() - 1 && \
				(getTile(currentX, currentY - 1).getLetter() != EMPTY || \
				getTile(currentX, currentY + 1).getLetter() != EMPTY))
			// {
				down = true;
			// 	std::cout << "DEBUG condition 4" << std::endl;
			// 	std::cout << "DEBUG tile left: " << getTile(currentX, currentY - 1).getLetter() << std::endl;
			// 	std::cout << "DEBUG tile right: " << getTile(currentX, currentY + 1).getLetter() << std::endl;
			// }
			if (i == 0 && currentY > 0 && getTile(currentX - 1, currentY).getLetter() != EMPTY)
			// {
				down = true;
			// 	std::cout << "DEBUG prefix: " << getTile(currentX - 1, currentY).getLetter() << std::endl;
			// }
			if (i == word.size() - 1 && currentY < BOARD_SIZE - 1 && getTile(currentX + 1, currentY).getLetter() != EMPTY) 
			// {
				down = true;
			// 	std::cout << "DEBUG suffix: " << getTile(currentX + 1, currentY).getLetter() << std::endl;
			// }
			currentX++;
		}
		// if (down == false)
		// 	std::cout << "DEBUG down: word is not connected" << std::endl;
	}

	// std::cout << "DEBUG right: " << right << std::endl;
	// std::cout << "DEBUG down: " << down << std::endl;
	if (right && down)
		return (BOTH);
	else if (right)
		return (RIGHT);
	else if (down)
		return (DOWN);
	else
		throw std::logic_error("Error: word must be connected to existing tiles.");
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