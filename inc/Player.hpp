#pragma once

# include "Board.hpp"
# include "Tile.hpp"

class Player
{
	public:
		// Constructors and Destructors
		Player();
		Player(const Player& src);
		~Player();

		Player&	operator=(const Player& src);

		// Utils
		void	incrementPoints(int n);
		void	decrementPoints(int n);

		// Getters and setters
		std::string	getLetters() const;
		void		setLetters(char c);
		std::string	getLetter(int n) const;
		void		setLetter(int n, char c);

	private:
		std::string		_letters;
		unsigned int	_points;
};