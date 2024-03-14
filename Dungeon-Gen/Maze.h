#include "Tile.h"
#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
public:
    Maze(int width,  int height)
        : width(width), height(height), tiles(height, std::vector<Tile>(width, Tile::SOLID)) {}

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    Tile getTile(int x, int y) const {
        return tiles[y][x];
    }

    void setTile(int x, int y, Tile tile) {
        tiles[y][x] = tile;
    }

    void fill(Tile tile) {
        for (auto& row : tiles) {
            std::fill(row.begin(), row.end(), tile);
        }
    }

private:
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;

};

#endif