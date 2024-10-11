#include "Board.hpp"
#include "Tile.hpp"

class Player
{
	public:
		// Constructors and Destructors
		Player();
		~Player();

		Player&	operator=(const Player& src);

		// Utils
		void	incrementPoints(int n);
		void	decrementPoints(int n);

		// Getters and setters
		Tile&	getTiles() const;
		void	setTiles(char c);
		Tile&	getTile(int n) const;
		void	setTile(int n, char c);

	private:
		Tile			_tiles[7];
		unsigned int	_points;
};