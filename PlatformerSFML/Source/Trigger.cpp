#include "Triggers.h"
#include <SFML/Graphics.hpp>

Trigger::Trigger()
{
	isTriggered = false;
}

void Trigger::TriggerCheck(sf::RectangleShape box)
{
	if (box.getGlobalBounds().intersects(Bounds.getGlobalBounds()))
		isTriggered = true;
	else isTriggered = false;
}

void Trigger::Draw(sf::RenderWindow& windows, sf::Texture& drawTexture)
{
	windows.draw(Bounds);
}
