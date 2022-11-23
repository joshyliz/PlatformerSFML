#include "Global.h"
#include "Block.h"
#include "ABlock.h"
#include "BlockManager.h"
#include "Triggers.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Vector2f AddVectors(sf::Vector2f vector1, sf::Vector2f vector2)
{
    vector1.x += vector2.x;
    vector1.y += vector2.y;

    return vector1;
}

sf::Vector2f VectorZero()
{
    return sf::Vector2f(0, 0);
}

//Player Collision Detection

bool PlayerTouchingTop(Player player, sf::RectangleShape shape)
{
    float Top = shape.getPosition().y;
    float Bottom = shape.getPosition().y + shape.getGlobalBounds().height;
    float Left = shape.getPosition().x;
    float Right = shape.getPosition().x + shape.getGlobalBounds().width;

    if (player.Bottom + player.Veloctiy.y > Top && player.Right > Left && player.Left < Right
        && player.Top <= Top)
        return true;
    else return false;
}

bool PlayerTouchingBottom(Player player, sf::RectangleShape shape)
{
    float Top = shape.getPosition().y;
    float Bottom = shape.getPosition().y + shape.getGlobalBounds().height;
    float Left = shape.getPosition().x;
    float Right = shape.getPosition().x + shape.getGlobalBounds().width;

    if (player.Top + player.Veloctiy.y < Bottom && player.Bottom > Bottom
        && player.Right > Left && player.Left < Right)
        return true;
    else return false;
}

bool PlayerTouchingLeft(Player player, sf::RectangleShape shape)
{
    float Top = shape.getPosition().y;
    float Bottom = shape.getPosition().y + shape.getGlobalBounds().height;
    float Left = shape.getPosition().x;
    float Right = shape.getPosition().x + shape.getGlobalBounds().width;

    if (player.Right + player.Veloctiy.x > Left && player.Left < Left
        && player.Bottom > Top && player.Top < Bottom)
        return true;
    else return false;
}

bool PlayerTouchingRight(Player player, sf::RectangleShape shape)
{
    float Top = shape.getPosition().y;
    float Bottom = shape.getPosition().y + shape.getGlobalBounds().height;
    float Left = shape.getPosition().x;
    float Right = shape.getPosition().x + shape.getGlobalBounds().width;

    if (player.Left + player.Veloctiy.x < Right && player.Right > Right
        && player.Bottom > Top && player.Top < Bottom)
        return true;
    else return false;
}

bool ObjectTouchingTop(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2)
{
    float Top1 = shape1.getPosition().y;
    float Bottom1 = shape1.getPosition().y + shape1.getGlobalBounds().height;
    float Left1 = shape1.getPosition().x;
    float Right1 = shape1.getPosition().x + shape1.getGlobalBounds().width;

    float Top2 = shape2.getPosition().y;
    float Bottom2 = shape2.getPosition().y + shape2.getGlobalBounds().height;
    float Left2 = shape2.getPosition().x;
    float Right2 = shape2.getPosition().x + shape2.getGlobalBounds().width;

    if (Bottom1 + shape1Velocity.y > Top2 && Right1 > Left2 && Left1 < Right2
        && Top1 <= Top2)
        return true;
    else return false;
}

//Object Collsion Detection

bool ObjectTouchingBottom(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2)
{
    float Top1 = shape1.getPosition().y;
    float Bottom1 = shape1.getPosition().y + shape1.getGlobalBounds().height;
    float Left1 = shape1.getPosition().x;
    float Right1 = shape1.getPosition().x + shape1.getGlobalBounds().width;

    float Top2 = shape2.getPosition().y;
    float Bottom2 = shape2.getPosition().y + shape2.getGlobalBounds().height;
    float Left2 = shape2.getPosition().x;
    float Right2 = shape2.getPosition().x + shape2.getGlobalBounds().width;
        
    if (Top1 + shape1Velocity.y < Bottom2 && Bottom1 > Bottom2
        && Right1 > Left2 && Left1 < Right2)
        return true;
    else return false;
}

bool ObjectTouchingLeft(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2)
{
    float Top1 = shape1.getPosition().y;
    float Bottom1 = shape1.getPosition().y + shape1.getGlobalBounds().height;
    float Left1 = shape1.getPosition().x;
    float Right1 = shape1.getPosition().x + shape1.getGlobalBounds().width;

    float Top2 = shape2.getPosition().y;
    float Bottom2 = shape2.getPosition().y + shape2.getGlobalBounds().height;
    float Left2 = shape2.getPosition().x;
    float Right2 = shape2.getPosition().x + shape2.getGlobalBounds().width;


    if (Right1 + shape1Velocity.x > Left2 && Left1 < Left2
        && Bottom1 > Top2 && Top1 < Bottom2)
        return true;
    else return false;
}

bool ObjectTouchingRight(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2)
{
    float Top1 = shape1.getPosition().y;
    float Bottom1 = shape1.getPosition().y + shape1.getGlobalBounds().height;
    float Left1 = shape1.getPosition().x;
    float Right1 = shape1.getPosition().x + shape1.getGlobalBounds().width;

    float Top2 = shape2.getPosition().y;
    float Bottom2 = shape2.getPosition().y + shape2.getGlobalBounds().height;
    float Left2 = shape2.getPosition().x;
    float Right2 = shape2.getPosition().x + shape2.getGlobalBounds().width;

    if (Left1 + shape1Velocity.x < Right2 && Right1 > Right2
        && Bottom1 > Top2 && Top1 < Bottom2)
        return true;
    else return false;
}

//Map Generation And Collsion

void SetBlocks(sf::Texture& Tmap, BlockManager& blockManager, int blocksWidth, int blocksHeight)
{
    //Generate map from image
    
    int blockIndex = 0;
    int lavaIndex = 0;

    for (size_t i = 0; i < Tmap.getSize().y; i++)
    {
        SetBlockStrip(Tmap, blockManager, blocksWidth, blocksWidth, i, blockIndex, lavaIndex);
    }
   
}

void SetBlockStrip(sf::Texture& Tmap, BlockManager& blockManager, int blocksWidth, int blocksHeight, int y, int& blockIndex, int& lavaIndex)
{
    sf::Image map = Tmap.copyToImage();
    const size_t length = map.getSize().x;

    for (size_t i = 0; i < length; i++)
    {
        auto color = map.getPixel(i, y);


        if (color == sf::Color::Black)
        {
            blockManager.blocks[blockIndex].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y);
            blockManager.blocks[blockIndex].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            blockManager.blocks[blockIndex].Bounds.setPosition(blockManager.blocks[blockIndex].Position);
            blockIndex++;
        }
        else if (color == sf::Color(255, 0, 0))
        {
            blockManager.ablocks[BlockManager::Red].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y);
            blockManager.ablocks[BlockManager::Red] .Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            blockManager.ablocks[BlockManager::Red].Bounds.setPosition(blockManager.ablocks[BlockManager::Red].Position);
        }
        else if (color == sf::Color(6, 134, 41))
        {
            blockManager.ablocks[BlockManager::Green].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y);
            blockManager.ablocks[BlockManager::Green].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            blockManager.ablocks[BlockManager::Green].Bounds.setPosition(blockManager.ablocks[BlockManager::Green].Position);
        }
        else if (color == sf::Color(0, 86, 255))
        {
            blockManager.ablocks[BlockManager::Blue].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y);
            blockManager.ablocks[BlockManager::Blue].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            blockManager.ablocks[BlockManager::Blue].Bounds.setPosition(blockManager.ablocks[BlockManager::Blue].Position);
        }
        else if (color == sf::Color(212, 36, 36))
        {
            blockManager.triggers[BlockManager::Red].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y - blocksHeight);
            blockManager.triggers[BlockManager::Red].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight * 2));
            blockManager.triggers[BlockManager::Red].Bounds.setPosition(blockManager.triggers[BlockManager::Red].Position);
        }
        else if (color == sf::Color(38, 136, 65))
        {
            blockManager.triggers[BlockManager::Green].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y - blocksHeight);
            blockManager.triggers[BlockManager::Green].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight * 2));
            blockManager.triggers[BlockManager::Green].Bounds.setPosition(blockManager.triggers[BlockManager::Green].Position);
        }
        else if (color == sf::Color(58, 125, 255))
        {
            blockManager.triggers[BlockManager::Blue].Position = sf::Vector2f(blocksWidth * i, blocksHeight * y - blocksHeight);
            blockManager.triggers[BlockManager::Blue].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight * 2));
            blockManager.triggers[BlockManager::Blue].Bounds.setPosition(blockManager.triggers[BlockManager::Blue].Position);
        }
        else if (color == sf::Color(222, 213, 22))
        {
            blockManager.door.Position = sf::Vector2f(blocksWidth * i, blocksWidth * y - blocksHeight * 2);
            blockManager.door.Shape.setPosition(blockManager.door.Position);
        }
        else if (color == sf::Color(240, 114, 24))
        {
            blockManager.lavaBlocks[lavaIndex].left = blocksWidth * i;
            blockManager.lavaBlocks[lavaIndex].top = blocksWidth * y;
            blockManager.lavaBlocks[lavaIndex].width = blocksWidth;
            blockManager.lavaBlocks[lavaIndex].height = blocksHeight;
            lavaIndex++;
        }
        else if (color == sf::Color(54, 202, 15))
        {
            blockManager.respawnPoint.height = blocksWidth;
            blockManager.respawnPoint.width = blocksHeight;
            blockManager.respawnPoint.left = i * blocksWidth;
            blockManager.respawnPoint.top = y * blocksHeight;
        }


    }
}


void BlockCollsion(Player& player, Block blocks[], const size_t blockArraySize, ABlock ablocks[], const size_t ablockArraySize)
{
    for (size_t i = 0; i < blockArraySize; i++)
    {
        auto block = blocks[i];
        
        if (PlayerTouchingTop(player, block.Bounds))
        {
            player.isGrounded = true;
            player.Veloctiy.y = 0;
        }
        if (PlayerTouchingBottom(player, block.Bounds))
            player.Veloctiy.y = 0;
        if (PlayerTouchingLeft(player, block.Bounds))
            player.Veloctiy.x = 0;
        if (PlayerTouchingRight(player, block.Bounds))
            player.Veloctiy.x = 0;

    }
   
    for (size_t i = 0; i < ablockArraySize; i++)
    {
        ABlock* ablock = &ablocks[i];

        if (PlayerTouchingLeft(player, ablock->Bounds))
        {
            ablock->Veloctiy.x += player.Veloctiy.x;
            player.Veloctiy.x = 0;
        }
        if (PlayerTouchingRight(player, ablock->Bounds))
        {
            ablock->Veloctiy.x += player.Veloctiy.x;
            player.Veloctiy.x = 0;
        }
        if (PlayerTouchingTop(player, ablock->Bounds))
        {
            player.isGrounded = true;
            player.Veloctiy.y = 0;
        }
        if (PlayerTouchingBottom(player, ablock->Bounds))
        {
            player.isGrounded = true;
            ablock->Veloctiy.y = 0;
            player.Veloctiy.y = 0;
        }


        for (size_t j = 0; j < blockArraySize; j++)
        {
            ABlock* ablock = &ablocks[i];
            auto block = blocks[j];

            if (ObjectTouchingTop(ablock->Bounds, ablock->Veloctiy, block.Bounds))
            {
                ablock->Veloctiy.y = 0;
            }

            if (ObjectTouchingBottom(ablock->Bounds, ablock->Veloctiy, block.Bounds))
            {
                ablock->Veloctiy.y = 0;
            }

            if (ObjectTouchingLeft(ablock->Bounds, ablock->Veloctiy, block.Bounds))
            {
                ablock->Veloctiy.x = 0;
            }
            else if (ObjectTouchingRight(ablock->Bounds, ablock->Veloctiy, block.Bounds))
            {
                ablock->Veloctiy.x = 0;
            }
            else
            {
                ABlockCollision(ablocks[BlockManager::Green], ablocks[BlockManager::Blue]);
                ABlockCollision(ablocks[BlockManager::Red], ablocks[BlockManager::Blue]);
                ABlockCollision(ablocks[BlockManager::Red], ablocks[BlockManager::Green]);
            }

        }
    }
  
}


void ABlockCollision(ABlock& ablock1, ABlock& ablock2)
{

    if (ObjectTouchingTop(ablock1.Bounds, ablock1.Veloctiy, ablock2.Bounds))
    {
        ablock1.Veloctiy.y = 0;
    }

    if (ObjectTouchingTop(ablock2.Bounds, ablock2.Veloctiy, ablock1.Bounds))
    {
        ablock2.Veloctiy.y = 0;
    }

    
    if (ObjectTouchingRight(ablock1.Bounds, ablock1.Veloctiy, ablock2.Bounds))
    {
        if (-ablock1.Veloctiy.x > ablock2.Veloctiy.x)
        {
            ablock1.Veloctiy.x = 0;
        }
        else 
        {
            ablock2.Veloctiy.x = 0;
        }

    }

    if (ObjectTouchingLeft(ablock1.Bounds, ablock1.Veloctiy, ablock2.Bounds))
    {
        if (ablock1.Veloctiy.x > -ablock2.Veloctiy.x)
        {
            ablock1.Veloctiy.x = 0;
        }
        else
        {
            ablock2.Veloctiy.x = 0;
        }

    }
}

void DoorCollision(BlockManager& blockManager, Player& player)
{
    if (PlayerTouchingTop(player, blockManager.door.Shape))
        player.Veloctiy.y = 0;

    if (PlayerTouchingBottom(player, blockManager.door.Shape))
        player.Veloctiy.y = 0;

    if (PlayerTouchingLeft(player, blockManager.door.Shape))
        player.Veloctiy.x = 0;

    if (PlayerTouchingRight(player, blockManager.door.Shape))
        player.Veloctiy.x = 0;

    for (size_t i = 0; i < blockManager.ABLOCK_SIZE; i++)
    {
        ABlock* ablock = &blockManager.ablocks[i];
        
        if (ObjectTouchingTop(ablock->Bounds, ablock->Veloctiy, blockManager.door.Shape))
            ablock->Veloctiy.y = 0;
        if (ObjectTouchingBottom(ablock->Bounds, ablock->Veloctiy, blockManager.door.Shape))
            ablock->Veloctiy.y = 0;
        if (ObjectTouchingRight(ablock->Bounds, ablock->Veloctiy, blockManager.door.Shape))
            ablock->Veloctiy.x = 0;
        if (ObjectTouchingLeft(ablock->Bounds, ablock->Veloctiy, blockManager.door.Shape))
            ablock->Veloctiy.x = 0;
    }
}

sf::Vector2f GetCenterBounds(sf::FloatRect rect)
{
    return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}


void ResetManager(BlockManager* manager)
{

    for (size_t i = 0; i < manager->BLOCKS_SIZE; i++)
        manager->blocks[i].Bounds.setPosition(-1000, -1000);

    for (size_t i = 0; i < manager->ABLOCK_SIZE; i++)
        manager->ablocks[i].Bounds.setPosition(-1000, -1000);

    for (size_t i = 0; i < manager->LAVA_SIZE; i++)
    {
        manager->lavaBlocks[i].top = -1000;
        manager->lavaBlocks[i].left = -1000;
    }

    for (size_t i = 0; i < manager->TRIGGER_SIZE; i++)
        manager->triggers[i].Bounds.setPosition(-1000, -1000);

    manager->door.Position = sf::Vector2f(-1000, -1000);

    manager->respawnPoint.top = -1000;
    manager->respawnPoint.left = -1000;
}


