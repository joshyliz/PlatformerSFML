#include "BlockManager.h"
#include <SFML/Graphics.hpp>
#include "ABlock.h"
#include "Block.h"
#include <iostream>

BlockManager::BlockManager(sf::Texture& BlockTexture, sf::Texture& ABlockTexture, sf::Texture& TriggerTexture, sf::Texture& DoorTexture)
{
	for (size_t i = 0; i < BLOCKS_SIZE; i++)
	{
		blocks[i].Bounds.setTexture(&BlockTexture);
	}

	door.Shape.setTexture(&DoorTexture);

	ablocks[Red].Bounds.setFillColor(sf::Color::Red);
	ablocks[Green].Bounds.setFillColor(sf::Color::Green);
	ablocks[Blue].Bounds.setFillColor(sf::Color::Blue);
	triggers[Red].Bounds.setFillColor(sf::Color(255, 0, 0, 255));
	triggers[Green].Bounds.setFillColor(sf::Color(0, 255, 0, 255));
	triggers[Blue].Bounds.setFillColor(sf::Color(0, 0, 255, 255));

	for (size_t i = 0; i < ABLOCK_SIZE; i++)
	{
		ablocks[i].Bounds.setTexture(&ABlockTexture);
	}

	for (size_t i = 0; i < TRIGGER_SIZE; i++)
	{
		triggers[i].Bounds.setTexture(&TriggerTexture);
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

void BlockManager::Draw(sf::RenderWindow& window, sf::Texture& LavaTexture, sf::Shader& shader)
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

	for (size_t i = 0; i < LAVA_SIZE; i++)
	{
		sf::RectangleShape shape;
		sf::FloatRect lava = lavaBlocks[i];

		shape.setPosition(sf::Vector2f(lava.left, lava.top));
		shape.setSize(sf::Vector2f(lava.width, lava.height));
		shape.setTexture(&LavaTexture);

		window.draw(shape, &shader);
	}
	
	window.draw(door.Shape);
	
}
