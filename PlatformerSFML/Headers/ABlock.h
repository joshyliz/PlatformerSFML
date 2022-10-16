#pragma once
#include <SFML/Graphics.hpp>

class ABlock
{
public:
	sf::RectangleShape Bounds;
	sf::Vector2f Position;
	sf::Vector2f Veloctiy;
	float Speed;
	float Gravity;
	float Friction;
	bool isGrounded;

	float Top;
	float Bottom;
	float Right;
	float Left;

	ABlock(sf::Vector2f startPosition, sf::Vector2f width_height);
	ABlock();

	float GetWidth();
	float GetHeight();

	void Update(float dt);
};

