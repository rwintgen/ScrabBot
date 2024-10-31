#pragma once

# include <fstream>
# include <iostream>
# include <iomanip>
# include <vector>
# include <unordered_set>
# include <map>
# include <regex>
# include "Tile.hpp"
# include "Player.hpp"

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define PINK		"\033[38;5;218m"
# define LIGHT_BLUE	"\033[36m"
# define DARK_BLUE	"\033[34m"
# define BROWN_BG	"\033[48;5;94m"
# define WHITE		"\033[37m"

# define BOARD_SIZE 15

class Tile;
class Player;

typedef enum e_dir
{
	RIGHT,
	DOWN,
	BOTH
}				t_dir;

typedef enum e_lang
{
	ENGLISH,
	FRENCH
	// SPANISH
}				t_lang;

class Board
{
	public:
		// Constructors and destructors
		Board();
		Board(const Board &src);
		~Board();

		Board&	operator=(const Board &src);

		// Utils
		void		printBoard();
		void		decrementBag(char c);
		void		incrementBag(char c);
		std::string	collectWord(const Board &tmpBoard, int startY, int startX, t_dir dir) const;
		bool		tileCompletesWord(int x, int y, t_dir dir) const;

		// Game manipulation
		void		opponentPlay();
		bool		playWord(int x, int y, std::string word, t_dir direction);

		// Game logic
		int		countPoints(int x, int y, std::string word, t_dir dir);
		int		countPerpendicularPoints(int x, int y, t_dir perpDir);
		t_dir	checkWord(int x, int y, std::string word);
		bool	checkBoard(const Board &tmpBoard) const;
		t_dir	checkFrontiers(int x, int y, std::string word, t_dir dir);
		bool	checkAvailableLetters();
		bool	checkGameOver();

		// Getters and setters
		void		setTile(int x, int y, char c);
		const Tile&	getTile(int x, int y) const;
		void		setTurn();
		bool		getTurn() const;
		void		setLang(t_lang lang);
		t_lang		getLang() const;
		int			getPoints(char c) const;

		// Algorithm
		Board&	findBestMove();

	private:
		std::vector<std::vector<Tile> >			_board;
		std::map<char, std::pair<int, int> >	_letters;
		std::unordered_set<std::string>			_dict;

		Player*	_opponent;
		Player*	_player;

		bool	_turn;
		bool	_firstTurn;

		int	_gameLanguage;

		// Init
		void	initBoard();
		void	initLanguage();
		void	initTurn();
		void	initDict();
};