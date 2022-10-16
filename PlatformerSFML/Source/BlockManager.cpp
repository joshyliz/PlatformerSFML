#include "BlockManager.h"
#include <SFML/Graphics.hpp>
#include "ABlock.h"
#include "Block.h"

void BlockManager::Update(float dt)
{
	for (size_t i = 0; i < ABLOCK_SIZE; i++)
	{
		ablocks[i].Update(dt);
	}
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
}
