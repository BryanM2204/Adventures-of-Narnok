#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "map.h"

int main()
{

    // make window fullscreen compatible
    sf::RenderWindow window(sf::VideoMode(800, 600), "test");

    // match screen's frame rate
    window.setVerticalSyncEnabled(true);

    // create boolean for switching from windowed to fullscreen and back
    bool fullscreen = false;

    
    sf::Texture texture;

    // Ms. Sullivan - nuff said
    // I wonder if there is an easier way to do this? Make it portable - there probably is
    // look into this
    if(!texture.loadFromFile("Textures\\Narnok.png")){
        return 1;
    }

    // create the level with an array of integers
    const int level[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
    0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 0,
    0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0,
    0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    const unsigned int mapWidth = 20;
    const unsigned int mapHeight = 18;


    TileMap map;
    if(!map.load("Textures\\TEST.png", sf::Vector2u(32, 32), level, mapWidth, mapHeight)){
        return 1;

    };


    // resize the map 
    sf::Vector2u tileSize = map.getTileSize();
    sf::Vector2u mapSize(mapWidth * tileSize.x, mapHeight * tileSize.y);

    // sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);

    // create the four different faces of the sprite
    sf::IntRect rightFace(0, 0, 32, 32);
    sf::IntRect leftFace(32, 0, 32, 32);
    sf::IntRect towardsFace(0, 32, 32, 64);
    sf::IntRect awayFace(32, 32, 64, 64);


    // Initialize the Player - add texture and origin - and event
    // look into sf::Event() - I don't think that needs to be there but for now it breaks without it
    Player Player(texture, rightFace, {mapSize.x / 2.0f, mapSize.y / 2.0f}, sf::Event());
    
    //resize the player sprite
    Player.sprite.setScale(2, 2);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;


        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            // checks for keypress - F11
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F11) {
                    // switch boolean from false to true
                    fullscreen = !fullscreen;
                    // if true - go to fullscreen - else go to windowed mode
                    if (fullscreen) {
                        window.create(sf::VideoMode::getDesktopMode(), "Test", sf::Style::Fullscreen);
                    }
                    else {
                        window.create(sf::VideoMode(800, 600), "Test", sf::Style::Default);
                    }

                    // Update the view size and center whenever switching from windowed to fullscreen - keeps everything consistent
                    view.setSize(window.getSize().x, window.getSize().y);
                    view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                    window.setView(view);

                }
            }

        }


        // Declare and initialize the sprite variable
        sf::Sprite sprite;
        
        // clear the window 
        window.clear();

         // draw the map
        window.draw(map);
        
        // initialize the direction 
        sf::Vector2f direction = {0.f, 0.f};

        // for some reason if statements work better than switch case????
        // depending on keypressed - changes direction in the x or y direction to monitor's boundary
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                // this breaks my view - Player.sprite.setTextureRect(towardsFace);
                // I don't know why - for now I will comment this out
                direction.y -= 2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                // similar problem as above
                // Player.sprite.setTextureRect(awayFace);
                direction.y += 2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                Player.sprite.setTextureRect(leftFace);
                direction.x -= 2;
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                Player.sprite.setTextureRect(rightFace);
                direction.x += 2;
        }

        // update the position of the sprite based on boundaries of map
        sf::Vector2f newPosition = Player.sprite.getPosition() + direction;
        if(newPosition.x >= 0 && newPosition.x < mapSize.x - Player.sprite.getGlobalBounds().width && newPosition.y >= 0 && newPosition.y < mapSize.y - Player.sprite.getGlobalBounds().height) {
            Player.move(direction);
        } 

        // update the view to follow the player
        sf::Vector2f viewCenter(Player.sprite.getPosition().x + Player.sprite.getGlobalBounds().width / 2, Player.sprite.getPosition().y + Player.sprite.getGlobalBounds().height / 2);
        view.setCenter(viewCenter);
        window.setView(view);

        // draw the Player sprite after updating position
        window.draw(Player.sprite);

        // end the current frame
        window.display();
    }

    return 0;
}