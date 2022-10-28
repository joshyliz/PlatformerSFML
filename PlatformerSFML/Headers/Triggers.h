#pragma once
#include <SFML/Graphics.hpp>


class Trigger
{
public:
	bool isTriggered;
	int color;
	sf::Vector2f Position;
	sf::RectangleShape Bounds;
	
	Trigger();
	
	void TriggerCheck(sf::RectangleShape box);

	void Draw(sf::RenderWindow& windows, sf::Texture& drawTexture);
};