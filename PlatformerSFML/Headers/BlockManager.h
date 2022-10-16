#pragma once
#include "ABlock.h"
#include "Block.h"


class BlockManager
{
public:
	 Block blocks[1250];
	 ABlock ablocks[10];
	 const short BLOCKS_SIZE = sizeof(blocks) / sizeof(blocks[0]);
	 const short ABLOCK_SIZE = sizeof(ablocks) / sizeof(ablocks[0]);

	 void Update(float dt);

	 void Draw(sf::RenderWindow& window);
};







