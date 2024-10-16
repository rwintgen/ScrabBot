#pragma once

# include "Board.hpp"

# define EMPTY '.'

typedef struct s_coord
{
	int x;
	int y;
}				t_coord;

typedef enum e_type
{
	STANDARD,
	LETTER_DOUBLE,
	LETTER_TRIPLE,
	WORD_DOUBLE,
	WORD_TRIPLE
}				t_type;

class Tile
{
	public:
		// Constructors and destructors
		Tile();
		Tile(Tile const &src);
		~Tile();

		// Copy assignment operator
		Tile&	operator=(const Tile &src);

		// Getters and setters
		void	setLetter(char c);
		char	getLetter() const;
		void	setType(t_type type);
		t_type	getType() const;
		void	setCompletesWord(bool completesWord);
		bool	getCompletesWord() const;

	private:
		char	_letter;
		t_type	_type;
		bool	_completesWord;
};