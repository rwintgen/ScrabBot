#include "Board.hpp"
#include "Tile.hpp"

// TODO
// work on algo and prompt for validation
// implement UNDO, EXIT commands
// UI/UX improvements

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
				try
				{
					currentState.setPlayerTiles();
					currentState = currentState.findBestMove();
				}
				catch (const std::exception &e)
				{
					std::cerr << e.what() << std::endl;;
					currentState = tmpBoard;
					continue ;
				}
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