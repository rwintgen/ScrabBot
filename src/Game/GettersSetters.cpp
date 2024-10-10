#include "Board.hpp"
#include "Tile.hpp"

// TODO
// add check for playing when no tile of letter is left
void Board::setTile(int x, int y, char c)
{
	if (y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE)
	{
		auto it = _letters.find(c);
		if (it != _letters.end())
		{
			if (_board[x][y].getLetter() == EMPTY && it->second.first > 0)
				decrementBag(c);
			_board[x][y].setLetter(c);
		}
	}
	else
		throw std::out_of_range("Error: invalid board coordinates (" + std::to_string(x) + ", " + std::to_string(y) + ").");
}

const Tile& Board::getTile(int x, int y) const
{
	if (y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE)
		return (_board[x][y]);
	throw std::out_of_range("Error: tile out of bounds");
}

void Board::setTurn(void)
{
	_turn = !_turn;
	std::cout << "DEBUG turn: " << _turn << std::endl;
}

bool Board::getTurn(void) const
{
	return (_turn);
}