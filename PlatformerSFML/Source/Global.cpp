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
