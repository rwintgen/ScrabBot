#include "Board.hpp"
#include "Tile.hpp"

int Board::countPerpendicularPoints(int x, int y, t_dir perpDir)
{
	unsigned int	points = 0;
	int				startX = x;
	int				startY = y;

	while (startX > 0 && perpDir == DOWN && getTile(startX - 1, y).getLetter() != EMPTY)
		startX--;
	while (startY > 0 && perpDir == RIGHT && getTile(x, startY - 1).getLetter() != EMPTY)
		startY--;

	while ((perpDir == DOWN && startX < BOARD_SIZE && getTile(startX, y).getLetter() != EMPTY && startX != x ) ||
		   (perpDir == RIGHT && startY < BOARD_SIZE && getTile(x, startY).getLetter() != EMPTY && startY != y))
	{
		Tile currentTile = (perpDir == DOWN) ? getTile(startX, y) : getTile(x, startY);
		points += getPoints(currentTile.getLetter());

		if (perpDir == DOWN)
			startX++;
		else
			startY++;
	}

	return (points);
}

int Board::countPoints(int x, int y, std::string word, t_dir dir)
{
	unsigned int	points = 0;
	unsigned int	multiplier = 1;

	for (size_t i = 0; i < word.size(); i++)
	{
		Tile currentTile = getTile(x, y);
		std::cout << "DEBUG currentTile: " << currentTile.getLetter() << \
					" worth: " << getPoints(currentTile.getLetter()) << \
					" type: " << currentTile.getType() << std::endl;

		switch (currentTile.getType())
		{
			case STANDARD:
				points += getPoints(currentTile.getLetter());
				break ;
			case WORD_DOUBLE:
				points += getPoints(currentTile.getLetter());
				multiplier = 2;
				break ;
			case WORD_TRIPLE:
				points += getPoints(currentTile.getLetter());
				multiplier = 3;
				break ;
			case LETTER_DOUBLE:
				points += getPoints(currentTile.getLetter()) * 2;
				break ;
			case LETTER_TRIPLE:
				points += getPoints(currentTile.getLetter()) * 3;
				break ;
			default:
				throw std::logic_error("Error: invalid tile type.");
		}
		_board[x][y].setType(STANDARD);

		if (dir == DOWN)
		{
			points += countPerpendicularPoints(x, y, RIGHT);
			x++;
		}
		else if (dir == RIGHT)
		{
			points += countPerpendicularPoints(x, y, DOWN);
			y++;
		}
		else
			throw std::logic_error("Error: invalid direction.");
	}

	std::cout << "DEBUG points: " << points << std::endl;
	std::cout << "DEBUG multiplier: " << multiplier << std::endl;
	std::cout << "DEBUG total (current): " << points * multiplier << std::endl;

	return (points * multiplier);
}