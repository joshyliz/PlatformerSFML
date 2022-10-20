#include <SFML/Graphics.hpp>
#include <iostream>

//My Headers
#include "Global.h"
#include "Player.h"
#include "Block.h"
#include "ABlock.h"
#include "BlockManager.h"
#include "Animation.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Platformer");
    window.setFramerateLimit(60);

    float dt;
    sf::Clock dtClock;
   
    //Fps Timer
    float timer = 1;


    sf::Shader fShader;

    Player player(sf::Vector2f(0, 0), sf::Vector2f(32, 32));

    fShader.loadFromFile("Shaders\\fShader.frag", sf::Shader::Fragment);
    fShader.setUniform("texture", sf::Shader::CurrentTexture);

    sf::View camera(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
    float zoom = 1;

    sf::Texture map;
    map.loadFromFile("Textures\\map.png");

    //Textures
    sf::Texture playerIdle;
    playerIdle.loadFromFile("Textures\\LittleGuyIdle.png");
    sf::Texture walkSpriteSheet;
    walkSpriteSheet.loadFromFile("Textures\\LittleWalkAnim.png");

    //Animations
    Animation walkAnimation(walkSpriteSheet, 1, 4);

    BlockManager blockManager;

    //Generate map from image
    SetBlocks(map, blockManager.blocks, blockManager.ablocks, 64, 64);

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

        timer -= dt;
        if (timer < 0)
        {
            timer = 1;
            std::cout << "FPS: " << ceil(1 / dt) << "\n";
        }

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            zoom -= 1 * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            zoom += 1 * dt;

        camera.zoom(zoom);

        zoom = 1;
    
        camera.setCenter(sf::Vector2f(player.Position.x, player.Position.y));
        BlockCollsion(player, blockManager.blocks, blockManager.BLOCKS_SIZE, blockManager.ablocks, blockManager.ABLOCK_SIZE);
        blockManager.Update(dt);
        player.Update(dt);
        walkAnimation.Update(dt, true, player.Position);

        //Draw
        window.clear();
        window.setView(camera);
        blockManager.Draw(window);
        walkAnimation.Draw(window, false);

        window.display();
    }

    return 0;
}
