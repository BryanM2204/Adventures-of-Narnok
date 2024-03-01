#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

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
    if(!texture.loadFromFile("Textures\\New Piskel.png")){
        return 1;
    }
    
    // Initialize the Player - add texture and origin - and event
    // look into sf::Event() - I don't think that needs to be there but for now it breaks without it
    Player Player(texture, {float(window.getSize().x / 2), float(window.getSize().y / 2)}, sf::Event());
    Player.sprite.setScale(4, 4);

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
                }
            }

        }

        // clear the window with black color
        sf::Sprite sprite; // Declare and initialize the sprite variable
        window.clear(sf::Color::Black);

        // initialize the direction 
        sf::Vector2f direction = {0.f, 0.f};

        // for some reason if statements work better than switch case????
        // depending on keypressed - changes direction in the x or y direction to monitor's boundary
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(Player.sprite.getPosition().y >= 0.5){
                direction.y -= 5;
            }
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(Player.sprite.getPosition().y < (window.getSize().y - 30)){
                direction.y += 5;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if(Player.sprite.getPosition().x > -8){
                direction.x -= 5;
            }
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if(Player.sprite.getPosition().x < (window.getSize().x - 20)){
                direction.x += 5;
            }
        }

        // send updated direction to the move method in Player class
        Player.move(direction);

        // draw the Player sprite after updating position
        window.draw(Player.sprite);

        // end the current frame
        window.display();

        
    }

    return 0;
}