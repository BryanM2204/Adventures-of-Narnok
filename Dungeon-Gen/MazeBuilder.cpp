#include "MazeBuilder.h"
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


MazeBuilder::MazeBuilder(int numRoomTries, int extraConnectorChance, int roomExtraSize, int windingPercent)
    : numRoomTries(numRoomTries), extraConnectorChance(extraConnectorChance), 
        roomExtraSize(roomExtraSize), windingPercent(windingPercent), 
        minEdgeLength(11 + roomExtraSize * 4),
        currentRegion(-1), bounds(0, 0, 0, 0) {}

void MazeBuilder::build(Maze& target) {
    if (target.getWidth() < minEdgeLength || target.getHeight() < minEdgeLength) {
        throw std::runtime_error("The maze must be at least " +
                                    std::to_string(minEdgeLength) + "x" +
                                    std::to_string(minEdgeLength));

    }
    if (target.getWidth() % 2 == 0 || target.getHeight() % 2 == 0) {
        throw std::runtime_error("The maze must have odd dimensions");
    }

    maze = &target;
    bounds = Rect(0, 0, maze->getWidth(), maze->getHeight());
    regions = Array2D<int>(maze->getWidth(), maze->getHeight());

    // start with a solid map
    maze->fill(Tile::SOLID);

    // carve out rooms randomly
    addRooms();

    // Fill in all of the empty space with mazes
    for (int y = 1; y < bounds.height; y += 2) {
        for (int x = 1; x < bounds.width; x += 2) {
            if (maze->getTile(x, y) == Tile::SOLID) {
                growMaze(Vec(x, y));
            }
        }
    }

    // carve out random openings between corridors
    connectRegions();

    // simplify the maze
    removeDeadEnds();
    
}


void MazeBuilder::addRooms() {
    for (int i = 0; i < numRoomTries; i++) {
        int size = (std::uniform_int_distribution<>(1, 3 + roomExtraSize)(random) * 2) + 1;
        int rectangularity = std::uniform_int_distribution<>(0, size / 2)(random) * 2;
        int width = size;
        int height = size;
        if (oneIn(2)) {
            width += rectangularity;
        } else {
            height += rectangularity;
        }

        int x = std::uniform_int_distribution<>(0, (bounds.width - width) / 2)(random) * 2 + 1;
        int y = std::uniform_int_distribution<>(0, (bounds.height - height) / 2)(random) * 2 + 1;

        Rect room(x, y, width, height);

        bool overlaps = std::any_of(rooms.begin(), rooms.end(), [&](const Rect& other) {
            return room.distanceTo(other) <= 0;
        });

        if (!overlaps) {
            rooms.push_back(room);
            startRegion();
            for(const Vec& cell : room) {
                carve(cell);
            }
        }
    }
}

// Implementation of the "growing tree" algorithm from here:
// http://www.astrolog.org/labyrnth/algrithm.htm.

void MazeBuilder::growMaze(const Vec& start) {
    startRegion();
    carve(start);

    std::vector<Vec> cells{start};
    Direction lastDirection = Direction::NONE;

    while (!cells.empty()) {
        Vec cell = cells.back();

        // See which adjacent cells are open.
        std::vector<Direction> possibleDirections;
        std::copy_if(CARDINALS.begin(), CARDINALS.end(), std::back_inserter(possibleDirections),
                    [&](Direction direction) { return canCarve(cell, direction); });

        if (!possibleDirections.empty()) {
            // based on how "windy" passages are, try to prefer carving in the same direction
            Direction direction;
            if (std::find(possibleDirections.begin(), possibleDirections.end(), lastDirection) != possibleDirections.end() && std::uniform_int_distribution<>(0, 99)(random) > windingPercent) {
                direction = lastDirection;
            } else {
                direction = possibleDirections[std::uniform_int_distribution<>(0, possibleDirections.size() - 1)(random)];
            }

            Vec nextCell = direction + cell;
            Vec destinationCell = direction * 2 + cell;

            // carve out two cells, with the second being the new point of reference
            carve(nextCell);
            carve(destinationCell);

            cells.push_back(destinationCell);

            // keep carving in same direction
            lastDirection = direction;
        } else {
            // no adjacent cells are open, so backtrack
            cells.pop_back();

            // no longer carving in the same direction
            lastDirection = Direction::NONE;
        }
    }
}

void MazeBuilder::connectRegions() {
    // Find all of the SOLID tiles that can connect two (or more) regions
    std::unordered_map<Vec, std::unordered_set<int>> connectorRegions = findRegionConnectors();

    // Keep track of which regions have been merged. This maps an original region to a new region
    // region index to the one it has been merged to
    // start with all regions being unmerged, i.e. map to themselves
    std::unordered_map<int, int> merged;
    for (int i = 0; i <= currentRegion; ++i) {
        merged[i] = i;
    }
    std::unordered_set<int> openRegions(merged.begin(), merged.end());

    auto mappedRegionsFor = [&](const Vec& connector) {
        std::unordered_set<int> mappedRegions;
        for (int region : connectorRegions[connector]) {
            mappedRegions.insert(merged[region]);
        }
        return mappedRegions;
    };

    // Keep connecting regions until there is only one region left
    std::vector<Vec> connectors;
    for (const auto& pair : connectorRegions) {
        connectors.push_back(pair.first);
    }
    while (openRegions.size() > 1 && !connectors.empty()) {
        Vec connector = connectors[std::uniform_int_distribution<>(0, connectors.size() - 1)(random)];

        // Carve the connection
        carve(connector);

        // Merge the connected regions. We'll pick one region (arbitrarily) and merge the other regions to its index
        std::unordered_set<int> mappedRegions = mappedRegionsFor(connector);
        int targetRegion = *mappedRegions.begin(); 
        std::vector<int> sources(mappedRegions.begin(), mappedRegions.end());
        sources.erase(sources.begin());

        // Merge all of the affected regions. We have to look at *all* of the
        // regions because other regions may have previously been merged with
        // some of the ones we're merging now.
        for (int region = 0; region <= currentRegion; ++region) {
            if (merged.count(region) > 0 && std::find(sources.begin(), sources.end(), merged[region]) != sources.end()) {
                merged[region] = targetRegion;
            }
        }

        // The sources are no longer open
        for (int source : sources) {
            openRegions.erase(source);
        }

        // Remove any connectors that are no longer valid
        connectors.erase(std::remove_if(connectors.begin(), connectors.end(), [&](const Vec& cell) {
            // Don't allow connectors right next to each other.
            if ((connector - cell).getLengthSquared() < 4) {
                return true;
            }

            // If the connector no longer spans different regions, we don't need it.
            if (mappedRegionsFor(cell).size() > 1) {
                return false;
            }

            // This connector isn't needed, but connect it occasionally so that the dungeon isn't singly-connected
            if (oneIn(extraConnectorChance)) {
                carve(cell);
            }
            return true;
        }), connectors.end());

    }
}

std::unordered_map<Vec, std::unordered_set<int>> MazeBuilder::findRegionConnectors() {
    std::unordered_map<Vec, std::unordered_set<int>> connectorRegions;
    for (const Vec& cell : bounds.inflate(-1)) {
        // Can't already be part of a region
        if (maze->getTile(cell.x, cell.y) == Tile::SOLID) {
            std::unordered_set<int> cellRegions;
            for (Direction direction : CARDINALS) {
                int region = regions[direction + cell];
                if (region != 0) {
                    cellRegions.insert(region);
                }
            }

            if (cellRegions.size() >= 2) {
                connectorRegions[cell] = cellRegions;
            }
        }
    }
    return connectorRegions;
}

void MazeBuilder::removeDeadEnds() {
    bool done = false;

    while (!done) {
        done = true;

        for (const Vec& cell : bounds.inflate(-1)) {
            if(maze->getTile(cell.x, cell.y) == Tile::SOLID) {
                continue;
            }

            // If it only has one exit, it's a dead end
            int exits = 0;
            for (Direction direction : CARDINALS) {
                Vec neighbor = cell + direction;
                if (maze->getTile(neighbor.x, neighbor.y) != Tile::SOLID) {
                    ++exits;
                }
            }

            if (exits != 1) {
                continue;
            }

            done = false;
            maze->setTile(cell.x, cell.y, Tile::SOLID);
        }
    }
}

// Gets whether or not an opening can be carved from the given starting
// cell to the adjacent cell facing direction. Returns `true`
// if the starting cell is in bounds and the destination cell is filled
// (or out of bounds).
bool MazeBuilder::canCarve(const Vec& cell, Direction direction) {
    // Must end in bounds
    if (!bounds.containsPoint(cell + direction * 3)) {
        return false;
    }

    // Destination must not be open
    Vec dest = cell + direction * 2;
    return maze->getTile(dest.x, dest.y) == Tile::SOLID;
}

void MazeBuilder::startRegion() {
    ++currentRegion;
}

void MazeBuilder::carve(const Vec& pos) {
    maze->setTile(pos.x, pos.y, Tile::OPEN);
    regions[pos] = currentRegion;
}

bool MazeBuilder::oneIn(int chance) {
    return chance > 0 && std::uniform_int_distribution<>(0, chance - 1)(random) == 0;
}






