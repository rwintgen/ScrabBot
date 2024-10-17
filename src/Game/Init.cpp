#include "Board.hpp"
#include "Tile.hpp"

// TODO init Player objects
Board::Board() : _board(BOARD_SIZE, std::vector<Tile>(BOARD_SIZE))
{
	initLanguage();
	initDict();
	initBoard();
	initTurn();

	switch (_gameLanguage)
	{
	case ENGLISH:
		_letters =
		{
			{'A', {9, 1}}, {'B', {2, 3}}, {'C', {2, 3}}, {'D', {4, 2}}, {'E', {12, 1}},
			{'F', {2, 4}}, {'G', {3, 2}}, {'H', {2, 4}}, {'I', {9, 1}}, {'J', {1, 8}},
			{'K', {1, 5}}, {'L', {4, 1}}, {'M', {2, 3}}, {'N', {6, 1}}, {'O', {8, 1}},
			{'P', {2, 3}}, {'Q', {1, 10}}, {'R', {6, 1}}, {'S', {4, 1}}, {'T', {6, 1}},
			{'U', {4, 1}}, {'V', {2, 4}}, {'W', {2, 4}}, {'X', {1, 8}}, {'Y', {2, 4}},
			{'Z', {1, 10}}, {'_', {2, 0}}
		};
		break ;
	case FRENCH:
		_letters =
		{
			{'A', {9, 1}}, {'B', {2, 3}}, {'C', {2, 3}}, {'D', {3, 2}}, {'E', {15, 1}},
			{'F', {2, 4}}, {'G', {2, 2}}, {'H', {2, 4}}, {'I', {8, 1}}, {'J', {1, 8}},
			{'K', {1, 10}}, {'L', {5, 1}}, {'M', {3, 2}}, {'N', {6, 1}}, {'O', {6, 1}},
			{'P', {2, 3}}, {'Q', {1, 8}}, {'R', {6, 1}}, {'S', {6, 1}}, {'T', {6, 1}},
			{'U', {6, 1}}, {'V', {2, 4}}, {'W', {1, 10}}, {'X', {1, 10}}, {'Y', {1, 10}},
			{'Z', {1, 10}}, {'_', {2, 0}}
		};
		break ;	
	default:
		break ;
	}

	_player = new(Player);
	_opponent = new(Player);
}

Board::Board(const Board &src)
{
	if (this != &src)
		*this = src;
}

Board::~Board()
{
	delete _opponent;
	delete _player;
}

Board& Board::operator=(const Board &src)
{
	_board = src._board;
	_letters = src._letters;
	_dict = src._dict;

	// TODO make a deep copy of the players
	_opponent = new Player(src._opponent);
	_player = new Player(src._player);

	_turn = src._turn;
	_firstTurn = src._firstTurn;

	return (*this);
}

void Board::initLanguage()
{
	std::string	input;

	while (std::cin && input != "EN" && input != "FR"/* && input != "ES"*/)
	{
		std::cout << "Select language (EN/fr): ";
		std::getline(std::cin, input);
		if (!input.empty())
			std::transform(input.begin(), input.end(), input.begin(), ::toupper);

		if (input == "EN" || input.empty())
			_gameLanguage = ENGLISH;
		else if (input == "FR")
			_gameLanguage = FRENCH;
		// else if (input == "ES")
		// 	_gameLanguage = SPANISH;
		else
			continue ;
		
		return ;
	}
}

void Board::initDict(void)
{
	std::ifstream	file;
	std::string		word;

	switch (_gameLanguage)
	{
		case ENGLISH:
			file.open("dicts/EN_dict.txt");
			break ;
		case FRENCH:
			file.open("dicts/FR_dict.txt");
			break ;
		// case SPANISH:
		// 	file.open("dicts/ES_dict.txt");
		// 	break ;
		default:
			throw std::logic_error("Error: invalid language.");
			break ;
	}

	if (file.is_open())
	{
		while (std::getline(file, word))
			_dict.insert(word);
		file.close();
		std::cout << "Stored valid words in memory." << std::endl;
	}
	else
		throw std::logic_error("Error: unable to open dict.");
}

void Board::initBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i][j].setLetter(EMPTY);
			_board[i][j].setType(STANDARD);
			_board[i][j].setCompletesWord(false);
		}
	}

	_board[7][7].setType(WORD_DOUBLE);
	_board[0][0].setType(WORD_TRIPLE);
	_board[0][7].setType(WORD_TRIPLE);
	_board[0][14].setType(WORD_TRIPLE);
	_board[7][0].setType(WORD_TRIPLE);
	_board[7][14].setType(WORD_TRIPLE);
	_board[14][0].setType(WORD_TRIPLE);
	_board[14][7].setType(WORD_TRIPLE);
	_board[14][14].setType(WORD_TRIPLE);
	_board[1][1].setType(WORD_DOUBLE);
	_board[2][2].setType(WORD_DOUBLE);
	_board[3][3].setType(WORD_DOUBLE);
	_board[4][4].setType(WORD_DOUBLE);
	_board[10][10].setType(WORD_DOUBLE);
	_board[11][11].setType(WORD_DOUBLE);
	_board[12][12].setType(WORD_DOUBLE);
	_board[13][13].setType(WORD_DOUBLE);
	_board[1][13].setType(WORD_DOUBLE);
	_board[2][12].setType(WORD_DOUBLE);
	_board[3][11].setType(WORD_DOUBLE);
	_board[4][10].setType(WORD_DOUBLE);
	_board[10][4].setType(WORD_DOUBLE);
	_board[11][3].setType(WORD_DOUBLE);
	_board[12][2].setType(WORD_DOUBLE);
	_board[13][1].setType(WORD_DOUBLE);
	_board[5][1].setType(LETTER_TRIPLE);
	_board[9][1].setType(LETTER_TRIPLE);
	_board[1][5].setType(LETTER_TRIPLE);
	_board[5][5].setType(LETTER_TRIPLE);
	_board[9][5].setType(LETTER_TRIPLE);
	_board[13][5].setType(LETTER_TRIPLE);
	_board[1][9].setType(LETTER_TRIPLE);
	_board[5][9].setType(LETTER_TRIPLE);
	_board[9][9].setType(LETTER_TRIPLE);
	_board[13][9].setType(LETTER_TRIPLE);
	_board[5][13].setType(LETTER_TRIPLE);
	_board[9][13].setType(LETTER_TRIPLE);
	_board[0][3].setType(LETTER_DOUBLE);
	_board[0][11].setType(LETTER_DOUBLE);
	_board[2][6].setType(LETTER_DOUBLE);
	_board[2][8].setType(LETTER_DOUBLE);
	_board[3][0].setType(LETTER_DOUBLE);
	_board[3][7].setType(LETTER_DOUBLE);
	_board[3][14].setType(LETTER_DOUBLE);
	_board[6][2].setType(LETTER_DOUBLE);
	_board[6][6].setType(LETTER_DOUBLE);
	_board[6][8].setType(LETTER_DOUBLE);
	_board[6][12].setType(LETTER_DOUBLE);
	_board[7][3].setType(LETTER_DOUBLE);
	_board[7][11].setType(LETTER_DOUBLE);
	_board[8][2].setType(LETTER_DOUBLE);
	_board[8][6].setType(LETTER_DOUBLE);
	_board[8][8].setType(LETTER_DOUBLE);
	_board[8][12].setType(LETTER_DOUBLE);
	_board[11][0].setType(LETTER_DOUBLE);
	_board[11][7].setType(LETTER_DOUBLE);
	_board[11][14].setType(LETTER_DOUBLE);
	_board[12][6].setType(LETTER_DOUBLE);
	_board[12][8].setType(LETTER_DOUBLE);
	_board[14][3].setType(LETTER_DOUBLE);
	_board[14][11].setType(LETTER_DOUBLE);
}

void Board::initTurn(void)
{
	std::string	input;

	_firstTurn = true;
	while (std::cin && input != "Y" && input != "N")
	{
		std::cout << "Are you making the first move? (Y/n): "; 
		std::getline(std::cin, input);
		if (!input.empty())
			input[0] = std::toupper(input[0]);

		if (input == "Y" || input.empty())
			_turn = true;
		else if (input == "N")
			_turn = false;
		else
			continue ;

		std::cout << std::endl;
		return ;
	}
}
