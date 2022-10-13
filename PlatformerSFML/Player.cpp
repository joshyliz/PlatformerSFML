#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Global.h"

Player::Player(sf::Vector2f startPosition, sf::Vector2f width_height)
{
	Bounds.setSize(width_height);
	Bounds.setPosition(startPosition);
	Speed = 200;
	Gravity = 50;
	Friction = 7;
}

float Player::GetWidth()
{
	return Bounds.getGlobalBounds().width;
}

float Player::GetHeight()
{
	return Bounds.getGlobalBounds().height;
}

void Player::Update(float dt)
{
	Position = AddVectors(Position, Veloctiy);
	Bounds.setPosition(Position);

	Top = Position.y;
	Bottom = Position.y + GetHeight();
	Left = Position.x;
	Right = Position.x + GetWidth();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Veloctiy.x = -Speed * dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Veloctiy.x = Speed * dt;
	else if (Veloctiy.x != 0)
	{
		Veloctiy.x = Veloctiy.x -= Friction * Veloctiy.x * dt;
	}
	
	/*
	Debug Move Code
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		Veloctiy.y = -Speed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		Veloctiy.y = Speed * dt;
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded == true)
	{
		Veloctiy.y -= 1000 * dt;
		isGrounded = false;
	}

	Veloctiy.y += Gravity * dt;
	
	isGrounded = false;
}
