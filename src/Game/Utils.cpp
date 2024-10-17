#include "Board.hpp"

void Board::printBoard()
{
	std::cout << "   ";
	for (char column = 'A'; column <= 'O'; column++)
	{
		std::cout << column << " ";
	}
	std::cout << std::endl;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		std::cout << std::setw(2) << (x + 1) << " ";
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (_board[x][y].getLetter() != EMPTY)
				std::cout << BROWN_BG << _board[x][y].getLetter() << RESET;
			else
			{
				switch (_board[x][y].getType())
				{
					case WORD_DOUBLE:
						std::cout << PINK << "W" << RESET;
						break ;
					case WORD_TRIPLE:
						std::cout << RED << "W" << RESET;
						break ;
					case LETTER_DOUBLE:
						std::cout << LIGHT_BLUE << "L" << RESET;
						break ;
					case LETTER_TRIPLE:
						std::cout << DARK_BLUE << "L" << RESET;
						break ;
					default:
						std::cout << ".";
						break ;
				}
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::decrementBag(char c)
{
	auto it = _letters.find(c);
	if (it != _letters.end() && it->second.first > 0)
		(it->second.first)--;
}

void Board::incrementBag(char c)
{
	auto it = _letters.find(c);
	if (it != _letters.end() && it->second.first > 0)
		(it->second.first)++;
}

std::string	Board::collectWord(const Board &tmpBoard, int x, int y, t_dir dir) const
{
		std::string fullWord;
		int currentY = y;
		int currentX = x;

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

bool Board::tileCompletesWord(int x, int y, t_dir dir) const
{
	std::cout << "DEBUG direction" << dir << std::endl;

	if (dir == DOWN)
	{
		if ((x > 0 && getTile(x - 1, y).getLetter() != EMPTY) && \
			(x >= BOARD_SIZE - 1 || getTile(x + 1, y).getLetter() == EMPTY))
			return (true);
		if ((x < BOARD_SIZE - 1 && getTile(x + 1, y).getLetter() != EMPTY) && \
			(x <= 0 || getTile(x - 1, y).getLetter() == EMPTY))
			return (true);
	}
	else if (dir == RIGHT)
	{
		if ((y > 0 && getTile(x, y - 1).getLetter() != EMPTY) && \
			(y >= BOARD_SIZE - 1 || getTile(x, y + 1).getLetter() == EMPTY))
			return (true);
		if ((y < BOARD_SIZE - 1 && getTile(x, y + 1).getLetter() != EMPTY) && \
			(y <= 0 || getTile(x, y - 1).getLetter() == EMPTY))
			return (true);
	}
	return (false);
}
