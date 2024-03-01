#include <SFML/Graphics.hpp>
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    sf::Texture texture;
    sf::Vector2f position;
    // Add a variable to store movement speed - when did I add this??? -BM
    // Anyways - implement speed variable later on - will go well with speed boost upgrades
    float speed;

public:
    sf::Sprite sprite;
    sf::Event event;
    sf::RenderWindow window;
    // Constructor 
    Player(const sf::Texture &texture, sf::Vector2f position, sf::Event event);

    // updates the sprite's position
    void updatePosition(sf::Vector2f position);

    // Implement movement logic based on user input
    void move(sf::Vector2f direction);
};

#endif