#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#ifndef MAP_H
#define MAP_H

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    sf::Vector2u getTileSize() const {
        return m_tileSize;
    }

};

#endif