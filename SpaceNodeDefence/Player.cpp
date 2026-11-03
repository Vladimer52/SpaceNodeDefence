#include "Player.h"
#include <algorithm>

void Player::moveLeft()
{
	x--;
	x = std::clamp(x, 1, screen_width_ - 1);
}

void Player::moveRight()
{
	x++;
	x = std::clamp(x, 1, screen_width_ - 1);
}
void Player::update()
{
}

std::string Player::getSymbol() const
{
	return "^";
}

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}

bool Player::isDead() const
{
	return is_dead;
}

void Player::onCollision()
{
	is_dead = true;
}

