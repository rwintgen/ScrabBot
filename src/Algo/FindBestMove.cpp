#include "Board.hpp"
#include "Tile.hpp"

Board& Board::findBestMove(void)
{
	std::cout << "Finding best word with tiles \"" << \
				_player->getLetters() << "\"..." << std::endl;

	Board	tmpBoard(*this);
	Board	bestMoveBoard(*this);

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (getTile(x, y).getLetter() != EMPTY)
			{
				// Check the tile to the left
				if (x > 0 && getTile(x - 1, y).getLetter() == EMPTY)
					_board[x - 1][y].setPlayable(true);

				// Check the tile to the right
				if (x < BOARD_SIZE - 1 && getTile(x + 1, y).getLetter() == EMPTY)
					_board[x + 1][y].setPlayable(true);

				// Check the tile above
				if (y > 0 && getTile(x, y - 1).getLetter() == EMPTY)
					_board[x][y - 1].setPlayable(true);

				// Check the tile below
				if (y < BOARD_SIZE - 1 && getTile(x, y + 1).getLetter() == EMPTY)
					_board[x][y + 1].setPlayable(true);
			}
		}
	}
	return (*this);
}