#pragma once
#include "Door.h"
#include <SFML/Graphics.hpp>

Door::Door()
{
	Bounds.width = 64;
	Bounds.height = 64*3;
	Shape.setSize(sf::Vector2f(Bounds.width, Bounds.height));
}

void Door::OpenDoor(bool open, float dt)
{
	if (open == true && Bounds.height > 0)
	{
		Bounds.height -= 10 * dt;
		Shape.setSize(sf::Vector2f(Bounds.width, Bounds.height));
	}
}