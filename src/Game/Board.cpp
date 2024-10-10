#include "Board.hpp"
#include "Tile.hpp"

static std::string getInput(void)
{
	std::string	input;
	std::regex	pattern(R"(^[A-O](1[0-5]|[1-9])\s[a-zA-Z]+)");

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

	int		check = checkWord(x, y, word);

	while (std::cin && check == BOTH && word.size() > 1)
	{
		std::cout << "How did your opponent play? (RIGHT/DOWN): ";
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "RIGHT")
			check = RIGHT;
		else if (input == "DOWN")
			check = DOWN;
	}

	if (checkFrontiers(check) == false)
		throw std::logic_error("Error: word must be connected to existing tiles.");

	if (check == RIGHT)
		playWord(x, y, word, RIGHT, PLAY);
	else if (check == DOWN)
		playWord(x, y, word, DOWN, PLAY);
	else
		throw std::logic_error("Error: invalid move.");
}

bool Board::playWord(int x, int y, std::string word, t_dir direction, t_mode mode)
{
	Tile	tmpTile;
	bool	isCenter = false;

	for (size_t i = 0; i < word.size(); i++)
	{
		if (x >= BOARD_SIZE || y >= BOARD_SIZE)
			return (false);
		
		tmpTile = getTile(x, y);
		// std::cout << "DEBUG word[i]: " << word[i] << std::endl;
		// std::cout << "DEBUG tile: " << tmpTile.getLetter() << std::endl;
		if (tmpTile.getLetter() != EMPTY && tmpTile.getLetter() != word[i])
			return (false);

		if (mode == PLAY)
			setTile(x, y, word[i]);

		if (y == 7 && x == 7)
			isCenter = true;
		
		if (direction == DOWN)
			x++;
		else if (direction == RIGHT)
			y++;
	}

	if (_firstTurn && !isCenter)
		return (false);
	
	if (mode == PLAY)
		_firstTurn = false;

	return (true);
}
