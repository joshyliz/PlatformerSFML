#include "ABlock.h"
#include "Global.h"
#include <SFML/Graphics.hpp>

ABlock::ABlock(sf::Vector2f startPosition, sf::Vector2f width_height)
{
	Position = startPosition;
	Bounds.setSize(width_height);
	Bounds.setPosition(Position);
	Speed = 200;
	Gravity = 50;
	Friction = 7;
}

float ABlock::GetWidth()
{
	return Bounds.getGlobalBounds().width;
}

float ABlock::GetHeight()
{
	return Bounds.getGlobalBounds().height;
}

void ABlock::Update(float dt)
{
	Position = AddVectors(Position, Veloctiy);
	Bounds.setPosition(Position);

	Top = Position.y;
	Bottom = Position.y + GetHeight();
	Left = Position.x;
	Right = Position.x + GetWidth();

	if (Veloctiy.x != 0)
	{
		Veloctiy.x = Veloctiy.x -= Friction * Veloctiy.x * dt;
	}

	Veloctiy.y += Gravity * dt;
}


