#include <SFML/Graphics.hpp>
#include <iostream>

//My Headers
#include "Global.h"
#include "Player.h"
#include "Block.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Platformer");
    window.setFramerateLimit(60);

    float dt;
    sf::Clock dtClock;

    Player player(sf::Vector2f(100, 100), sf::Vector2f(50, 50));

    Block block(sf::Vector2f(0, 500), sf::Vector2f(500, 100));
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        //Update
        dt = dtClock.restart().asSeconds();
        
        /* 
        
        Poopy Shitty Code

        if (Bottom + playerVelocity.y * dt > floor.getGlobalBounds().top && Right > floor.getGlobalBounds().left && Left < floor.getGlobalBounds().left + floor.getGlobalBounds().width
            && Top <= floor.getGlobalBounds().top)
        {
                   playerVelocity.y = 0;
        }

        if (Top + playerVelocity.y * dt < fBottom && Bottom > fBottom
            && Right > floor.getGlobalBounds().left && Left < floor.getGlobalBounds().left + floor.getGlobalBounds().width)
            playerVelocity.y = 0;

        if (Right + playerVelocity.x * dt > fLeft && Left < fLeft
            && Bottom > fTop && Top < fBottom)
            playerVelocity.x = 0;

        if (Left + playerVelocity.x * dt < fRight && Right > fRight 
            && Bottom > fTop && Top < fBottom)
            playerVelocity.x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded == true)
        {
            playerVelocity.y = -1100;
        }

        */

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
        


        player.Update(dt);
        //Draw
        window.clear();
           
        window.draw(player.Bounds);
        window.draw(block.Bounds);

        window.display();
    }

    return 0;
}

