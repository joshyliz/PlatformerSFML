#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture& spriteSheet, float fps, int amountOfFrames)
{
	this->spriteSheet = spriteSheet;
	this->fps = fps;
	this->amountOfFrames = amountOfFrames;
	timer = 0;
	frameWidth = spriteSheet.getSize().x / amountOfFrames;
	drawRectangle.width = frameWidth;
	drawRectangle.height = spriteSheet.getSize().y;
	drawRectangle.left = 0;
	drawRectangle.top = 0;
	drawShape.setTexture(&spriteSheet);
	drawShape.setSize(sf::Vector2f(drawRectangle.width, drawRectangle.height));
}

void Animation::Update(float dt, bool playerAnimation, sf::Vector2f Position)
{
	timer -= dt;
	
	if (timer < 0 && playerAnimation == true)
	{
		if (drawRectangle.left == (frameWidth * amountOfFrames) - frameWidth)
			drawRectangle.left = 0;
		else drawRectangle.left += frameWidth;

		timer = fps;
	}
	else if (playerAnimation == false)
	{
		drawRectangle.left = 0;	
	}

	
	drawShape.setTextureRect(drawRectangle);
	drawShape.setPosition(Position);
	canDraw = playerAnimation;
}

void Animation::Draw(sf::RenderWindow& window, bool isFlipped)
{
	if (isFlipped == true)
	{
		drawShape.setScale(sf::Vector2f(-1, 1));
		drawShape.setPosition(sf::Vector2f(drawShape.getPosition().x + frameWidth, drawShape.getPosition().y));
	}
	else drawShape.setScale(sf::Vector2f(1, 1));
	
	if(canDraw == true)
		window.draw(drawShape);
}

