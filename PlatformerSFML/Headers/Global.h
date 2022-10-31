#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Block.h"
#include "ABlock.h"
#include "Triggers.h"
#include "BlockManager.h"

sf::Vector2f AddVectors(sf::Vector2f vector1, sf::Vector2f vector2);
sf::Vector2f VectorZero();

bool PlayerTouchingTop(Player player, sf::RectangleShape shape);
bool PlayerTouchingBottom(Player player, sf::RectangleShape shape);
bool PlayerTouchingLeft(Player player, sf::RectangleShape shape);
bool PlayerTouchingRight(Player player, sf::RectangleShape shape);

bool ObjectTouchingTop(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2);
bool ObjectTouchingBottom(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2);
bool ObjectTouchingLeft(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2);
bool ObjectTouchingRight(sf::RectangleShape shape1, sf::Vector2f shape1Velocity, sf::RectangleShape shape2);

void SetBlocks(sf::Texture& Tmap, BlockManager& blockManager, int blocksWidth, int blocksHeight);

void SetBlockStrip(sf::Texture& Tmap, BlockManager& blockManager, int blocksWidth, int blocksHeight, int y, int& blockIndex, int& lavaIndex);

void BlockCollsion(Player& player, Block blocks[], const size_t blockArraySize, ABlock ablocks[], const size_t ablockArraySize);

void ABlockCollision(ABlock& ablock1, ABlock& ablock2);

void DoorCollision(BlockManager& blockManager, Player& player);

sf::Vector2f GetCenterBounds(sf::FloatRect rect);

