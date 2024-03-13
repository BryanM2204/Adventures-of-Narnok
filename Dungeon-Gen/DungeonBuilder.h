#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H

class DungeonBuilder : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;

    int numRoomTries;
    int extraConnectorChance;
    int roomExtraSize;
    int windingPercent;
    bool removeDeadEnds;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    DungeonBuilder(int numRoomTries = 200, int extraConnectorChance = 0, int roomExtraSize = 0, int windingPercent = 0, bool removeDeadEnds = true);
};

#endif