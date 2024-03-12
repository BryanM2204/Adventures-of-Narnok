#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.h"



// Constructor - Initialize the character
Player::Player(const sf::Texture& texture, sf::IntRect initialRect, sf::Vector2f position = {0.f, 0.f}, sf::Event event = sf::Event()) {
    // set texture of the sprite - MS SULLIVAN LOOKIN AAAA
    // Whatever happened to her??? 
    this->texture = texture;
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(initialRect);

    // initialize the player's position to the center of the screen
    this->position = position;
    this->event = event;
}

// Update the character's position
void Player::updatePosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}

// Set the character's position
void Player::move(sf::Vector2f direction) {
    position += direction;
    sprite.setPosition(position); // Update sprite position as well
}