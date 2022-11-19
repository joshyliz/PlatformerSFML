#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    //Game Stuff
    sf::FloatRect PlayBounds;
    PlayBounds.width = 64 * 50;
    PlayBounds.height = 64 * 25;
    bool levelComplete = false;

    
    enum GameState { Playing, StartMenu, LevelSelect };
    enum Level { One, Two, Three, Four, Five };

    GameState state = StartMenu;
    Level level;

    sf::Vector2f MousePos;


    Player player(sf::Vector2f(200, 100), sf::Vector2f(32, 32));
    sf::RectangleShape fakePlayerShape = player.Bounds;
    bool playerGrounded = false;

    fShader.loadFromFile("Shaders\\fShader.frag", sf::Shader::Fragment);
    fShader.setUniform("texture", sf::Shader::CurrentTexture);

    sf::View camera(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));


    //Level Textures
    sf::Texture map1;
    map1.loadFromFile("Textures\\map1.png");

    sf::Texture map2;
    map2.loadFromFile("Textures\\map2.png");


    sf::Texture map3;
    map3.loadFromFile("Textures\\map3.png");


    sf::Texture map4;
    map4.loadFromFile("Textures\\map4.png");


    sf::Texture map5;
    map5.loadFromFile("Textures\\map5.png");


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
    sf::Texture MainMenuTexture;
    MainMenuTexture.loadFromFile("Textures\\HomeScreen.png");
    sf::Texture SpinSpriteSheet;
    SpinSpriteSheet.loadFromFile("Textures\\SpinGuy.png");
    sf::Texture BackGround;
    BackGround.loadFromFile("Textures\\BackRound.png");
    sf::Texture LevelSelectTex;
    LevelSelectTex.loadFromFile("Textures\\LevelSelect.png");
    

    //Audio
    sf::SoundBuffer MushroomBuff;
    MushroomBuff.loadFromFile("Sounds\\Mushroom.wav");
    sf::Sound Mushroom;
    Mushroom.setBuffer(MushroomBuff);

    //UI
    sf::Sprite Back;
    Back.setTexture(BackGround);

    sf::Sprite MainMenu;
    MainMenu.setTexture(MainMenuTexture);
    MainMenu.setPosition(VectorZero());

    sf::Sprite Level;
    Level.setTexture(LevelSelectTex);
    Level.setPosition(VectorZero());

    sf::FloatRect CornerGuy;
    CornerGuy.width = 31;
    CornerGuy.height = 15;
    CornerGuy.left = window.getSize().x - 31;
    CornerGuy.top = window.getSize().y - 15;



    sf::FloatRect PlayButton;
    sf::FloatRect QuitButton;
    PlayButton.width = 64 * 2;
    PlayButton.height = 64;
    QuitButton.width = 64 * 2;
    QuitButton.height = 64;

    PlayButton.left = 555;
    PlayButton.top = 442;

    QuitButton.left = 555;
    QuitButton.top = 570;
    
    window.setMouseCursorVisible(false);

    sf::FloatRect SelectBlocks[5];
    sf::FloatRect BackButton;

    for (size_t i = 0; i < 5; i++)
    {
        SelectBlocks[i].width = 256;
        SelectBlocks[i].height = 256;
    }

    SelectBlocks[1].left = 256 * 2;

    SelectBlocks[2].left = 256 * 4;

    SelectBlocks[3].left = 256;
    SelectBlocks[3].top = 256;

    SelectBlocks[4].left = 256 * 3;
    SelectBlocks[4].top = 256;

    BackButton.width = 188;
    BackButton.height = 137;
    BackButton.top = window.getSize().y - BackButton.height;

    //Animations
    Animation walkRightAnimation(walkSpriteSheet, 0.17f, 4);
    Animation walkLeftAnimation(walkSpriteSheet, 0.17f, 4);
    Animation spinAnimation(SpinSpriteSheet, 0.06f, 14);

    BlockManager blockManager(BlockTex, ABlockTex, TriggerTex, DoorTexture);
    bool triggersCheck = false;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Update
        dt = dtClock.restart().asSeconds();
        allTimePassed += dt;

        //Caculates Mouse Position
        MousePos.x = sf::Mouse::getPosition(window).x + camera.getCenter().x - window.getSize().x / 2;
        MousePos.y = sf::Mouse::getPosition(window).y + camera.getCenter().y - window.getSize().y / 2;


        fShader.setUniform("z", allTimePassed * 0.5f);

        timer -= dt;
        if (timer < 0)
        {
            timer = 1;
            std::cout << "FPS: " << ceil(1 / dt) << "\n";            
        }



        // UI
        

        //Main Menu

        if (state == StartMenu)
        {
            camera = window.getDefaultView();

            if (QuitButton.contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                window.close();

            if (PlayButton.contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = LevelSelect;
            }
            
        }

        //Map Gen
        if (state == LevelSelect)
        {
            camera = window.getDefaultView();

            if (BackButton.contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                state = StartMenu;
            
            if (CornerGuy.contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                Mushroom.play();

            if (SelectBlocks[0].contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.isAlive = false;
                SetBlocks(map1, blockManager, 64, 64);
                state = Playing;
            }

            if (SelectBlocks[1].contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.isAlive = false;
                SetBlocks(map2, blockManager, 64, 64);
                state = Playing;
            }

            if (SelectBlocks[2].contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.isAlive = false;
                SetBlocks(map3, blockManager, 64, 64);
                state = Playing;
            }

            if (SelectBlocks[3].contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.isAlive = false;
                SetBlocks(map4, blockManager, 64, 64);
                state = Playing;
            }

            if (SelectBlocks[4].contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.isAlive = false;
                SetBlocks(map5, blockManager, 64, 64);
                state = Playing;
            }

        }
        
        //Main Game

        if (state == Playing)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                state = LevelSelect;


            if (!player.Bounds.getGlobalBounds().intersects(PlayBounds))
            {
                state = LevelSelect;
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
        }

        //Caculates Mouse Position
        MousePos.x = sf::Mouse::getPosition(window).x + camera.getCenter().x - window.getSize().x / 2;
        MousePos.y = sf::Mouse::getPosition(window).y + camera.getCenter().y - window.getSize().y / 2;

        //Update Funny Guy
        spinAnimation.Update(dt, true, sf::Vector2f(MousePos.x - 35 / 2, MousePos.y - 35 / 2));

        //Draw
        window.clear();
        window.setView(camera);

        //UI

        //Main Menu

        if (state == StartMenu)
        {
            window.draw(MainMenu);
        }

        //Level Select
        if (state == LevelSelect)
        {
            window.draw(Level);
        }

        //Game Elements

        if (state == Playing)
        {
            for (size_t i = 0; i < 100; i++)
            {
                for (size_t j = 0; j < 50; j++)
                {
                    Back.setPosition(32 * i, 32 * j);
                    window.draw(Back);
                }
            }

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

        }


        //Draw Funny Guy
        spinAnimation.Draw(window, false);

        window.display();
    }

    return 0;
}





