#include "Global.h"
#include <SFML/Graphics.hpp>

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
