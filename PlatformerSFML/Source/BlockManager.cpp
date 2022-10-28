#include "BlockManager.h"
#include <SFML/Graphics.hpp>
#include "ABlock.h"
#include "Block.h"
#include <iostream>

BlockManager::BlockManager(sf::Texture& BlockTexture, sf::Texture& ABlockTexture)
{
	for (size_t i = 0; i < BLOCKS_SIZE; i++)
	{
		blocks[i].Bounds.setTexture(&BlockTexture);
	}

	ablocks[Red].Bounds.setFillColor(sf::Color::Red);
	ablocks[Green].Bounds.setFillColor(sf::Color::Green);
	ablocks[Blue].Bounds.setFillColor(sf::Color::Blue);
	triggers[Red].Bounds.setFillColor(sf::Color(255, 0, 0, 100));
	triggers[Green].Bounds.setFillColor(sf::Color(0, 255, 0, 100));
	triggers[Blue].Bounds.setFillColor(sf::Color(0, 0, 255, 100));

	for (size_t i = 0; i < ABLOCK_SIZE; i++)
	{
		ablocks[i].Bounds.setTexture(&ABlockTexture);
	}


}

void BlockManager::Update(float dt)
{
	for (size_t i = 0; i < ABLOCK_SIZE; i++)
	{
		ablocks[i].Update(dt);
	}

	triggers[Red].TriggerCheck(ablocks[Red].Bounds);
	triggers[Green].TriggerCheck(ablocks[Green].Bounds);
	triggers[Blue].TriggerCheck(ablocks[Blue].Bounds);
}

void BlockManager::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < ABLOCK_SIZE; i++)
	{
		window.draw(ablocks[i].Bounds);
	}

	for (size_t i = 0; i < BLOCKS_SIZE; i++)
	{
		window.draw(blocks[i].Bounds);
	}

	for (size_t i = 0; i < TRIGGER_SIZE; i++)
	{
		window.draw(triggers[i].Bounds);
	}
	
}
