#pragma once
#include "ABlock.h"
#include "Block.h"


class BlockManager
{
public:
	 Block blocks[1250];
	 ABlock ablocks[3];
	 enum ABlockColor
	 {
		 Red = 0,
		 Green = 1,
		 Blue = 2,
	 };

	 BlockManager();

	 const short BLOCKS_SIZE = sizeof(blocks) / sizeof(blocks[0]);
	 const short ABLOCK_SIZE = sizeof(ablocks) / sizeof(ablocks[0]);

	 void Update(float dt);

	 void Draw(sf::RenderWindow& window);
};
