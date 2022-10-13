#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	sf::RectangleShape Bounds;
	sf::Vector2f Position;
	sf::Vector2f Veloctiy;
	float Speed;
	float Gravity;
	float Friction;
	float JumpHeight;
	bool isGrounded;

	float Top;
	float Bottom;
	float Right;
	float Left;

	Player(sf::Vector2f startPosition, sf::Vector2f width_height);

	float GetWidth();
	float GetHeight();

	void Update(float dt);

};

