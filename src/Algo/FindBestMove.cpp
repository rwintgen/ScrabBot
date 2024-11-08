#include "Board.hpp"
#include "Tile.hpp"

Board& Board::findBestMove(void)
{
	std::cout << "Finding best word with tiles \"" << \
				_player->getLetters() << "\"..." << std::endl;

	// Implement this function to find the best move
	// based on the current state of the board.
	// The function should return the next move.
	return (*this);
}