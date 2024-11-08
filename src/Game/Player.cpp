#include "Player.hpp"
#include "Board.hpp"

Player::Player() : _letters(""), _points(0)
{
}

Player::Player(const Player& src)
{
	if (this != &src)
		*this = src;
}

Player::~Player()
{
}

Player& Player::operator=(const Player& src)
{
	if (this != &src)
	{
		_points = src._points;
		_letters = src._letters;
	}
	return (*this);
}

void Player::incrementPoints(int n)
{
	_points += n;
}

void Player::decrementPoints(int n)
{
	_points -= n;
}

std::string Player::getLetters() const
{
	return (_letters);
}

void Player::setLetters(std::string letters)
{
	_letters = letters;
}

std::string Player::getLetter(int n) const
{
	return (std::string(1, _letters[n]));
}

void Player::setLetter(int n, char c)
{
	_letters[n] = c;
}
