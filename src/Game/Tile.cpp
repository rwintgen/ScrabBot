#include "Tile.hpp"

Tile::Tile() : _letter(EMPTY), _type(STANDARD), _completesWord(false)
{
}

Tile::~Tile()
{
}

Tile::Tile(Tile const &src)
{
	*this = src;
}

Tile& Tile::operator=(const Tile &src)
{
	_letter = src._letter;
	_type = src._type;
	_completesWord = src._completesWord;
	return (*this);
}

void Tile::setLetter(char c)
{
	_letter = c;
}

char Tile::getLetter() const
{
	return (_letter);
}

void Tile::setType(t_type type)
{
	_type = type;
}

t_type Tile::getType() const
{
	return (_type);
}

void Tile::setCompletesWord(bool completesWord)
{
	_completesWord = completesWord;
}

bool Tile::getCompletesWord() const
{
	return (_completesWord);
}