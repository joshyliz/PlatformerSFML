#pragma once
#include "ABlock.h"
#include "Block.h"
#include "Triggers.h"
#include "Door.h"

class BlockManager
{
public:
	 Block blocks[1250];
	 ABlock ablocks[3];
	 Trigger triggers[3];
	 Door door;
	 sf::FloatRect lavaBlocks[250];
	 enum ABlockColor
	 {
		 Red = 0,
		 Green = 1,
		 Blue = 2,
	 };

	 BlockManager(sf::Texture& BlockTexture, sf::Texture& ABlockTexture, sf::Texture& TriggerTexture);

	 const short BLOCKS_SIZE = sizeof(blocks) / sizeof(blocks[0]);
	 const short ABLOCK_SIZE = sizeof(ablocks) / sizeof(ablocks[0]);
	 const short TRIGGER_SIZE = sizeof(triggers) / sizeof(triggers[0]);
	 const short LAVA_SIZE = sizeof(lavaBlocks) / sizeof(lavaBlocks[0]);

	 void Update(float dt);

	 void Draw(sf::RenderWindow& window);
};
