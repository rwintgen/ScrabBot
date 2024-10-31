#include "Board.hpp"
#include "Tile.hpp"

static unsigned int	getWordMultiplier(const Tile &currentTile)
{
	switch (currentTile.getType())
	{

		case WORD_DOUBLE:
			return (2);
		case WORD_TRIPLE:
			return (3);
		default:
			return (1);
	}
}

static unsigned int	getLetterMultiplier(const Tile &currentTile)
{
	switch (currentTile.getType())
	{
		case LETTER_DOUBLE:
			return (2);
		case LETTER_TRIPLE:
			return (3);
		default:
			return (1);
	}
}

int Board::countPerpendicularPoints(int x, int y, t_dir perpDir)
{
	unsigned int	points = 0;
	unsigned int	multiplier = 1;
	int				startX = x;
	int				startY = y;

	while (startX > 0 && perpDir == DOWN && getTile(startX - 1, y).getLetter() != EMPTY)
		startX--;
	while (startY > 0 && perpDir == RIGHT && getTile(x, startY - 1).getLetter() != EMPTY)
		startY--;

	while ((perpDir == DOWN && startX < BOARD_SIZE && getTile(startX, y).getLetter() != EMPTY /*&& startX != x + 1 */ ) ||
		   (perpDir == RIGHT && startY < BOARD_SIZE && getTile(x, startY).getLetter() != EMPTY /*&& startY != y + 1 */ ))
	{
		Tile currentTile = (perpDir == DOWN) ? getTile(startX, y) : getTile(x, startY);
		points += getPoints(currentTile.getLetter()) * getLetterMultiplier(currentTile);
		multiplier = (getWordMultiplier(currentTile) > multiplier) ? getWordMultiplier(currentTile) : multiplier;

		/*
		std::cout << "DEBUG currentTile: " << currentTile.getLetter() << \
					" worth: " << getPoints(currentTile.getLetter()) << \
					" type: " << currentTile.getType()<< \
					" completes a word: " << currentTile.getCompletesWord() << std::endl;
		*/

		if (perpDir == DOWN)
			startX++;
		else
			startY++;
	}

	return (points /* * multiplier */);
}

int Board::countPoints(int x, int y, std::string word, t_dir dir)
{
	unsigned int	points = 0;
	unsigned int	perpPoints = 0;
	unsigned int	multiplier = 1;

	for (size_t i = 0; i < word.size(); i++)
	{
		Tile currentTile = getTile(x, y);

		if (i < word.size() - 1 && word[i] == '_')
			word.erase(i, 1);


		std::cout << "DEBUG currentTile: " << currentTile.getLetter() << \
					" worth: " << getPoints(currentTile.getLetter()) << \
					" type: " << currentTile.getType()<< \
					" completes a word: " << currentTile.getCompletesWord() << std::endl;


		points += getPoints(currentTile.getLetter()) * getLetterMultiplier(currentTile);
		multiplier = (getWordMultiplier(currentTile) > multiplier) ? \
						getWordMultiplier(currentTile) : multiplier;

		t_dir	oppDir = (dir == RIGHT) ? DOWN : RIGHT;

		if (currentTile.getCompletesWord())
			perpPoints += countPerpendicularPoints(x, y, oppDir);
		_board[x][y].setType(STANDARD);
		_board[x][y].setCompletesWord(false);
		(dir == RIGHT) ? y++ : x++;
	}

	std::cout << "DEBUG points scored at this round: " << points * multiplier + perpPoints << std::endl;

	return (points * multiplier + perpPoints);
}