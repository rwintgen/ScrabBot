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
// fix player objects not being freed (valgrind) : 
/*

HEAP SUMMARY:
==6107==     in use at exit: 1,200 bytes in 30 blocks
==6107==   total heap usage: 514,368 allocs, 514,338 frees, 29,003,925 bytes allocated
==6107== 
==6107== 40 bytes in 1 blocks are definitely lost in loss record 1 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F56B: Board::Board() (Init.cpp:40)
==6107==    by 0x10DF48: main (main.cpp:39)
==6107== 
==6107== 40 bytes in 1 blocks are definitely lost in loss record 2 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F594: Board::Board() (Init.cpp:41)
==6107==    by 0x10DF48: main (main.cpp:39)
==6107== 
==6107== 40 bytes in 1 blocks are definitely lost in loss record 3 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F865: Board::operator=(Board const&) (Init.cpp:63)
==6107==    by 0x13F72D: Board::Board(Board const&) (Init.cpp:47)
==6107==    by 0x10DF61: main (main.cpp:40)
==6107== 
==6107== 40 bytes in 1 blocks are definitely lost in loss record 4 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F899: Board::operator=(Board const&) (Init.cpp:64)
==6107==    by 0x13F72D: Board::Board(Board const&) (Init.cpp:47)
==6107==    by 0x10DF61: main (main.cpp:40)
==6107== 
==6107== 160 bytes in 4 blocks are definitely lost in loss record 5 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F865: Board::operator=(Board const&) (Init.cpp:63)
==6107==    by 0x10DFF2: main (main.cpp:49)
==6107== 
==6107== 160 bytes in 4 blocks are definitely lost in loss record 6 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F899: Board::operator=(Board const&) (Init.cpp:64)
==6107==    by 0x10DFF2: main (main.cpp:49)
==6107== 
==6107== 160 bytes in 4 blocks are definitely lost in loss record 7 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F865: Board::operator=(Board const&) (Init.cpp:63)
==6107==    by 0x13F72D: Board::Board(Board const&) (Init.cpp:47)
==6107==    by 0x148D0B: Board::checkWord(int, int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (WordCheck.cpp:6)
==6107==    by 0x10E57B: Board::opponentPlay() (Board.cpp:40)
==6107==    by 0x10E01C: main (main.cpp:56)
==6107== 
==6107== 160 bytes in 4 blocks are definitely lost in loss record 8 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F899: Board::operator=(Board const&) (Init.cpp:64)
==6107==    by 0x13F72D: Board::Board(Board const&) (Init.cpp:47)
==6107==    by 0x148D0B: Board::checkWord(int, int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (WordCheck.cpp:6)
==6107==    by 0x10E57B: Board::opponentPlay() (Board.cpp:40)
==6107==    by 0x10E01C: main (main.cpp:56)
==6107== 
==6107== 200 bytes in 5 blocks are definitely lost in loss record 9 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F865: Board::operator=(Board const&) (Init.cpp:63)
==6107==    by 0x10E00B: main (main.cpp:50)
==6107== 
==6107== 200 bytes in 5 blocks are definitely lost in loss record 10 of 10
==6107==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==6107==    by 0x13F899: Board::operator=(Board const&) (Init.cpp:64)
==6107==    by 0x10E00B: main (main.cpp:50)
==6107== 
==6107== LEAK SUMMARY:
==6107==    definitely lost: 1,200 bytes in 30 blocks
==6107==    indirectly lost: 0 bytes in 0 blocks
==6107==      possibly lost: 0 bytes in 0 blocks
==6107==    still reachable: 0 bytes in 0 blocks
==6107==         suppressed: 0 bytes in 0 blocks

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