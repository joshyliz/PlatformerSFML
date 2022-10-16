#include "Block.h"
#include <SFML/Graphics.hpp>

Block::Block(sf::Vector2f startPosition, sf::Vector2f width_height)
{
	Position = startPosition;
	Bounds.setPosition(startPosition);
	Bounds.setSize(width_height);
	Top = Position.y;
	Bottom = Position.y + GetHeight();
	Left = Position.x;
	Right = Position.x + GetWidth();
}

Block::Block()
{
	Bounds.setPosition(Position);
}

float Block::GetWidth()
{
	return Bounds.getGlobalBounds().width;
}

float Block::GetHeight()
{
	return Bounds.getGlobalBounds().height;
}

