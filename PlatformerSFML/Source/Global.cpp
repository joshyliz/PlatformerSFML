#include "Global.h"
#include "Block.h"
#include "ABlock.h"
#include "BlockManager.h"
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

void SetBlocks(sf::Texture& Tmap, Block blocks[], ABlock ablocks[])
{
    //Generate map from image
    int y = 0;
    int x = 0;
    int wrapTimes = 1;

    int blocksWidth = 64;//64
    int blocksHeight = 64;//64
    
    int blockIndex = 0;

    int debugCount = 0;

    sf::Color color;
    
    sf::Image map = Tmap.copyToImage();

    size_t length = map.getSize().x * map.getSize().y;
    for (size_t i = 0; i < length; i++)
    {
        color = map.getPixel(x, y);

        if (i == map.getSize().x * wrapTimes)
        {
            x = 0;
            y++;
            wrapTimes++;
        }
        else
        {
            x++;
        }

        if (color == sf::Color::Black)
        {
            blocks[blockIndex].Position = sf::Vector2f(blocksWidth * x - blocksWidth, blocksHeight * y);
            blocks[blockIndex].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            blocks[blockIndex].Bounds.setPosition(blocks[blockIndex].Position);
            blockIndex++;
        }
        else if (color == sf::Color(255, 0, 0))
        {
            ablocks[BlockManager::Red].Position = sf::Vector2f(blocksWidth * x - blocksWidth, blocksHeight * y);
            ablocks[BlockManager::Red].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            ablocks[BlockManager::Red].Bounds.setPosition(ablocks[BlockManager::Red].Position);
        }
        else if (color == sf::Color(6, 134, 41))
        {
            ablocks[BlockManager::Green].Position = sf::Vector2f(blocksWidth * x - blocksWidth, blocksHeight * y);
            ablocks[BlockManager::Green].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            ablocks[BlockManager::Green].Bounds.setPosition(ablocks[BlockManager::Green].Position);
        }
        else if (color == sf::Color(0, 86, 255))
        {
            ablocks[BlockManager::Blue].Position = sf::Vector2f(blocksWidth * x - blocksWidth, blocksHeight * y);
            ablocks[BlockManager::Blue].Bounds.setSize(sf::Vector2f(blocksWidth, blocksHeight));
            ablocks[BlockManager::Blue].Bounds.setPosition(ablocks[BlockManager::Blue].Position);
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


