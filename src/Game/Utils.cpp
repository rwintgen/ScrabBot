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
						break;
					case WORD_TRIPLE:
						std::cout << RED << "W" << RESET;
						break;
					case LETTER_DOUBLE:
						std::cout << LIGHT_BLUE << "L" << RESET;
						break;
					case LETTER_TRIPLE:
						std::cout << DARK_BLUE << "L" << RESET;
						break;
					default:
						std::cout << ".";
						break;
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
