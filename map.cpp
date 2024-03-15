#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"


bool TileMap::load(const sf::Texture& tileset, const std::vector<std::vector<int>>& dungeonData, sf::Vector2u tileSize) {
    // Set the tileset texture
    m_tileset = tileset;

    // Clear existing vertex array
    m_vertices.clear();

    // Set the tile size
    m_tileSize = tileSize;

    // Resize the vertex array based on dungeon dimensions
    unsigned int width = dungeonData[0].size();
    unsigned int height = dungeonData.size();
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    // Iterate over the dungeon data and populate the vertex array
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            // Get the tile type from the dungeon data
            int tileType = dungeonData[j][i];

            // Calculate texture coordinates based on tile type
            int tu = tileType % (m_tileset.getSize().x / tileSize.x);
            int tv = tileType / (m_tileset.getSize().x / tileSize.x);

            // Get a pointer to the current tile's vertices
            sf::Vertex* quad = &m_vertices[(i + j * width) * 6];

            // Set vertex positions and texture coordinates
            // ...
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[4].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[5].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[5].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

sf::Vector2u m_tileSize; // Declare m_tileSize member variable

