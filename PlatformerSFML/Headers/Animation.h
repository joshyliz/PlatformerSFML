#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	float timer;
	float fps;
	int amountOfFrames;
	int frameCount = 0;
	int frameWidth;
	bool canDraw;
	sf::Texture spriteSheet;
	sf::RectangleShape drawShape;
	sf::IntRect drawRectangle;

	Animation(sf::Texture& spriteSheet, float fps, int amountOfFrames);

	void Update(float dt, bool playAnimation, sf::Vector2f Position);

	void Draw(sf::RenderWindow& window, bool isFlipped);

};
