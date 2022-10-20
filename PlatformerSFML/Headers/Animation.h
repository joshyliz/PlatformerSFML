#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	float timer;
	int fps;
	int amountOfFrames;
	int frameCount = 0;
	int frameWidth;
	sf::Texture spriteSheet;
	sf::RectangleShape drawShape;
	sf::IntRect drawRectangle;

	Animation(sf::Texture& spriteSheet, int fps, int amountOfFrames);

	void Update(float dt, bool playAnimation, sf::Vector2f Position);

	void Draw(sf::RenderWindow& window, bool isFlipped);

};
