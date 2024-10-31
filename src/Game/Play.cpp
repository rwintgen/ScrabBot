#include "Board.hpp"
#include "Tile.hpp"

static std::string getInput(void)
{
	std::string	input;
	std::regex	pattern(R"(^[A-O](1[0-5]|[1-9])\s[a-zA-Z_]+)");

	while (std::cin)
	{
		std::cout << "Enter opponent's move: ";
		std::getline(std::cin, input);
		std::cout << std::endl;

		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (std::regex_match(input, pattern))
			break ;
		else
		{
			std::cout << "Error: invalid format." << std::endl;
			std::cout << "Usage: [A-O][1-15] [word]" << std::endl;
			continue ;
		}
	}
	return (input);
}

void Board::opponentPlay(void)
{
	std::string				input = getInput();
	std::string::size_type	space = input.find(" ");
	std::string				coords = input.substr(0, space);
	std::string				word = input.substr(space + 1);

	unsigned int	y = coords[0] - 'A';
	unsigned int	x = std::stoi(coords.substr(1)) - 1;
	// std::cout << "DEBUG y: " << y << std::endl;
	// std::cout << "DEBUG x: " << x << std::endl;

	t_dir	checkW = checkWord(x, y, word);
	// std::cout << "DEBUG checkW: " << checkW << std::endl;
	t_dir	checkF = checkFrontiers(x, y, word, checkW);
	// std::cout << "DEBUG checkF: " << checkF << std::endl;

	t_dir	finalCheck;

	if (checkW == checkF)
		finalCheck = checkW;
	else if (checkW == BOTH || checkF == BOTH)
		finalCheck = (checkW < checkF) ? checkW : checkF;
	// std::cout << "DEBUG finalCheck: " << checkF << std::endl;

	while (std::cin && finalCheck == BOTH && word.size() > 1)
	{
		std::cout << "How did your opponent play? (RIGHT/DOWN): ";
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "RIGHT")
			finalCheck = RIGHT;
		else if (input == "DOWN")
			finalCheck = DOWN;
	}

	if (finalCheck == RIGHT || finalCheck == DOWN)
		playWord(x, y, word, finalCheck);
	else
		throw std::logic_error("Error: invalid move.");

	int	points = countPoints(x, y, word, finalCheck);
	_opponent->incrementPoints(points);
}

// TODO debug this function for wildcards
// edit: does the issue come ffrom this function?
bool Board::playWord(int x, int y, std::string word, t_dir direction)
{
	Tile	currentTile;
	bool	isCenter = false;
	bool	placedATile = false;

	for (size_t i = 0; i < word.size(); i++)
	{
		bool	isWildcard = false;

		if (x >= BOARD_SIZE || y >= BOARD_SIZE)
			return (false);

		if (i < word.size() - 1 && word[i] == '_')
		{
			word.erase(i, 1);
			isWildcard = true;
		}

		currentTile = getTile(x, y);
		if (currentTile.getLetter() != EMPTY && currentTile.getLetter() != word[i])
			return (false);

		setTile(x, y, word[i]);
		_board[x][y].setWildcard(isWildcard);
		if (placedATile == false && currentTile.getLetter() != word[i])
			placedATile = true;

		if (/*placedATile && */currentTile.getLetter() == EMPTY && tileCompletesWord(x, y, direction))
			_board[x][y].setCompletesWord(true);

		if (y == 7 && x == 7)
			isCenter = true;
		
		if (direction == DOWN)
			x++;
		else if (direction == RIGHT)
			y++;
		else
			throw std::logic_error("Error: invalid direction.");
	}

	if (checkAvailableLetters() == false)
		throw std::logic_error("Error: missing tile(s) for word: " + word);

	if ((_firstTurn && !isCenter) || placedATile == false)
		return (false);

	_firstTurn = false;

	return (true);
}
