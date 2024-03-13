#include "Tile.cpp"
#ifndef MAZE_H
#define MAZE_H

class Maze {
    public:
        virtual ~Maze() = default;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual Tile getTile(int x, int y) const = 0;

        virtual void setTile(int x, int y, Tile tile) = 0;

        virtual void fill(Tile tile) = 0;

};

#endif