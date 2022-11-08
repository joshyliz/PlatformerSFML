#include <SFML/Graphics.hpp>
#include <iostream>

//Defines
#define WINDOW_WIDTH 1280 //1280
#define WINDOW_HEIGHT 720 //720


//My Headers
#include "Global.h"
#include "Player.h"
#include "Block.h"
#include "ABlock.h"
#include "BlockManager.h"
#include "Animation.h"
#include "Triggers.h"
#include "Door.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Platformer");
    window.setFramerateLimit(60);

    float dt;
    sf::Clock dtClock;
    float allTimePassed = 0;
   
    //Fps Timer
    float timer = 1;


    sf::Shader fShader;
    fShader.setUniform("texture", sf::Shader::CurrentTexture);

    sf::FloatRect PlayBounds;
    PlayBounds.width = 64 * 50;
    PlayBounds.height = 64 * 25;
    bool levelComplete = false;
    bool isInLevel = false;


    Player player(sf::Vector2f(200, 100), sf::Vector2f(32, 32));
    sf::RectangleShape fakePlayerShape = player.Bounds;
    bool playerGrounded = false;

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
    sf::Texture BlockTex;
    BlockTex.loadFromFile("Textures\\Block.png");
    sf::Texture ABlockTex;
    ABlockTex.loadFromFile("Textures\\ABlock.png");
    sf::Texture TriggerTex;
    TriggerTex.loadFromFile("Textures\\Trigger.png");
    sf::Texture LavaTexture;
    LavaTexture.loadFromFile("Textures\\Lava.png");
    sf::Texture DoorTexture;
    DoorTexture.loadFromFile("Textures\\Door.png");

    //Animations
    Animation walkRightAnimation(walkSpriteSheet, 0.17f, 4);
    Animation walkLeftAnimation(walkSpriteSheet, 0.17f, 4);

    BlockManager blockManager(BlockTex, ABlockTex, TriggerTex, DoorTexture);
    bool triggersCheck = false;
    
    //Generate map from image
    SetBlocks(map, blockManager, 64, 64);
    

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

        allTimePassed += dt;

        fShader.setUniform("z", allTimePassed * 0.5f);

        timer -= dt;
        if (timer < 0)
        {
            timer = 1;
            std::cout << "FPS: " << ceil(1 / dt) << "\n";            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            zoom -= 1 * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            zoom += 1 * dt;

        camera.zoom(zoom);

        zoom = 1;

        if (!player.Bounds.getGlobalBounds().intersects(PlayBounds))
        {
            levelComplete = true;
        }

        for (size_t i = 0; i < blockManager.LAVA_SIZE; i++)
        {
            if (player.Bounds.getGlobalBounds().intersects(blockManager.lavaBlocks[i]))
                player.isAlive = false;
        }

        if (player.isAlive == false)
        {
            player.Position = sf::Vector2f(blockManager.respawnPoint.left, blockManager.respawnPoint.top);
            player.isAlive = true;
        }

        if (blockManager.triggers[BlockManager::Red].isTriggered == true && blockManager.triggers[BlockManager::Green].isTriggered == true
            && blockManager.triggers[BlockManager::Blue].isTriggered == true)
            blockManager.door.OpenDoor(true, dt);


        blockManager.Update(dt);
        BlockCollsion(player, blockManager.blocks, blockManager.BLOCKS_SIZE, blockManager.ablocks, blockManager.ABLOCK_SIZE);
        DoorCollision(blockManager, player);
        camera.setCenter(sf::Vector2f(player.Position.x + player.Bounds.getGlobalBounds().width / 2, player.Position.y + player.Bounds.getGlobalBounds().height / 2));

        playerGrounded = player.isGrounded;
        player.Update(dt);
        walkRightAnimation.Update(dt, player.Veloctiy.x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerGrounded == true, player.Position);
        walkLeftAnimation.Update(dt, player.Veloctiy.x < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerGrounded == true, player.Position);

        fakePlayerShape = player.Bounds;

        //Draw
        window.clear();
        window.setView(camera);
        blockManager.Draw(window, LavaTexture, fShader);
        walkLeftAnimation.Draw(window, true);
        walkRightAnimation.Draw(window, false);

        if (playerGrounded == false && player.Veloctiy.x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            fakePlayerShape.setTexture(&walkSpriteSheet);
            fakePlayerShape.setTextureRect(sf::IntRect(32, 0, 32, 32));
            window.draw(fakePlayerShape);
        }
        else if (playerGrounded == false && player.Veloctiy.x < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            fakePlayerShape.setTexture(&walkSpriteSheet);
            fakePlayerShape.setTextureRect(sf::IntRect(32, 0, 32, 32));
            fakePlayerShape.setScale(sf::Vector2f(-1, 1));
            fakePlayerShape.setPosition(sf::Vector2f(fakePlayerShape.getPosition().x + 32, fakePlayerShape.getPosition().y));

            window.draw(fakePlayerShape);
        }
        else if (playerGrounded == false && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
            && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            fakePlayerShape.setTexture(&playerIdle);
            window.draw(fakePlayerShape);
        }
        else if (playerGrounded == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
            && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            fakePlayerShape.setTexture(&playerIdle);
            window.draw(fakePlayerShape);
        }


        window.display();
    }

    return 0;
}
