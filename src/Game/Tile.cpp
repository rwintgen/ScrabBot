#include "Tile.hpp"

Tile::Tile() : _letter(EMPTY), _type(STANDARD)
{
}

Tile::~Tile()
{
}

Tile& Tile::operator=(const Tile &src)
{
	_letter = src._letter;
	_type = src._type;
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