#pragma once
#include <SFML/Graphics.hpp>

class Door
{
public:
	sf::Vector2f Position;
	sf::RectangleShape Shape;
	sf::FloatRect Bounds;

	Door(sf::Vector2f Position);

	void OpenDoor(bool open, float dt);
};

