#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	sf::RectangleShape Bounds;
	sf::Vector2f Position;

	float Top;
	float Bottom;
	float Right;
	float Left;

	Block(sf::Vector2f startPosition, sf::Vector2f width_height);

	Block();

	float GetWidth();
	float GetHeight();
};
