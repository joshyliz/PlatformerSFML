#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

sf::Vector2f AddVectors(sf::Vector2f vector1, sf::Vector2f vector2);
sf::Vector2f VectorZero();

bool PlayerTouchingTop(Player player, sf::RectangleShape shape);
bool PlayerTouchingBottom(Player player, sf::RectangleShape shape);
bool PlayerTouchingLeft(Player player, sf::RectangleShape shape);
bool PlayerTouchingRight(Player player, sf::RectangleShape shape);
