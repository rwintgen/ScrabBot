#include "Board.hpp"
#include "Tile.hpp"

// TODO
// for FR and ES, set the appropriate quantity and score for each letter
// check if a word played is overlaying another one
// add points counting system (has to be incremented at each turn)
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
				std::cout << "MY TURN" << std::endl << std::endl;
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
					continue;
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