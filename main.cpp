#include "Board.hpp"
#include "Tile.hpp"

// TODO
// add tile drawing and move checking according to available tiles
// work on algo and prompt for validation
// implement UNDO command
// UI/UX improvements

// BUG
// cannot just put an 's' at end of word
int main(void)
{
	try
	{
		Board currentState;
		Board tmpBoard(currentState);

		std::cout << "Board created:" << std::endl << std::endl;
		currentState.printBoard();

		while (std::cin && currentState.checkGameOver() == false)
		{
			if (currentState.getTurn() == true)
			{
				tmpBoard = currentState.findBestMove();
				currentState = tmpBoard;
			}
			else
			{
				try
				{
					currentState.opponentPlay();
					currentState.printBoard();
				}
				catch (const std::exception &e)
				{
					std::cerr << e.what() << std::endl;;
					currentState = tmpBoard;
					continue ;
				}
			}
			currentState.setTurn();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}