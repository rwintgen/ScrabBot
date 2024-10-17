#include "Board.hpp"
#include "Tile.hpp"

// TODO
// add points counting system (has to be incremented at each turn)
// add tile drawing and move checking according to available tiles
// work on algo and prompt for validation
// implement UNDO command
// UI/UX improvements

// BUG
// fix tileCompletesWord() function
// fix player objects not being copied to currentState
/*
   A B C D E F G H I J K L M N O 
 1 W . . L . . . W . . . L . . W 
 2 . W . . . L . . . L . . . W . 
 3 . . W . . . L . L . . . W . . 
 4 L . . W . . . L . . . W . . L 
 5 . . . . W . . T . . W . . . . 
 6 . L . . . L . E . L . . . L . 
 7 . . L . . . L S L . . . L . . 
 8 W . . L . . . T . . . L . . W 
 9 . . L . . . L . L . . . L . . 
10 . L . . . L . . . L . . . L . 
11 . . . . W . . . . . W . . . . 
12 L . . W . . . L . . . W . . L 
13 . . W . . . L . L . . . W . . 
14 . W . . . L . . . L . . . W . 
15 W . . L . . . W . . . L . . W 

Enter opponent's move: g9 ashamed
*/

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