#ifndef MAZEBUILDER_H
#define MAZEBUILDER_H

#include "Maze.h"
#include "Rect.h"
#include "Array2D.h"
#include "Vec.h"
#include "Direction.h"
#include <vector>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class MazeBuilder {
public:
    MazeBuilder(int numRoomTries = 200, int extraConnectorChance = 0, int roomExtraSize = 0, int windingPercent = 0, bool removeDeadEnds = true);

    void build(Maze& target);

private:
    void addRooms();
    void growMaze(const Vec& start);
    void connectRegions();
    std::unordered_map<Vec, std::unordered_set<int>> findRegionConnectors();
    void removeDeadEnds();
    bool canCarve(const Vec& cell, Direction direction);
    void startRegion();
    void carve(const Vec& pos);
    bool oneIn(int chance);

private:
    int numRoomTries;
    int extraConnectorChance;
    int roomExtraSize;
    int windingPercent;
    int minEdgeLength;

    Maze* maze;
    Rect bounds;
    Array2D<int> regions;
    std::mt19937 random;
    std::vector<Rect> rooms;
    int currentRegion;
};

#endif // MAZEBUILDER_H