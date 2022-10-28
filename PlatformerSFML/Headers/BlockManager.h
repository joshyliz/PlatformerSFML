#pragma once
#include "ABlock.h"
#include "Block.h"
#include "Triggers.h"


class BlockManager
{
public:
	 Block blocks[1250];
	 ABlock ablocks[3];
	 Trigger triggers[3];
	 enum ABlockColor
	 {
		 Red = 0,
		 Green = 1,
		 Blue = 2,
	 };

	 BlockManager(sf::Texture& BlockTexture, sf::Texture& ABlockTexture);

	 const short BLOCKS_SIZE = sizeof(blocks) / sizeof(blocks[0]);
	 const short ABLOCK_SIZE = sizeof(ablocks) / sizeof(ablocks[0]);
	 const short TRIGGER_SIZE = sizeof(triggers) / sizeof(triggers[0]);

	 void Update(float dt);

	 void Draw(sf::RenderWindow& window);
};
