#ifndef DIRECTION_H
#define DIRECTION_H

#include "Vec.h"
#include <array>

enum class Direction {
    NONE, N, E, S, W  
};

const std::array<Direction, 4> CARDINALS = {Direction::N, Direction::E, Direction::S, Direction::W};

inline Vec operator+(Direction direction, const Vec& vec) {
    switch (direction) {
        case Direction::NONE:
            return vec;
        case Direction::N:
            return {vec.x, vec.y - 1};
        case Direction::E:
            return {vec.x + 1, vec.y};
        case Direction::S:
            return {vec.x, vec.y + 1};
        case Direction::W:
            return {vec.x - 1, vec.y};
        
    }
}

inline Vec operator+(const Vec& vec, Direction direction) {
    return direction + vec;
}

inline Vec operator*(Direction direction, int scalar) {
    switch (direction) {
        case Direction::NONE:
            return {0, 0};
        case Direction::N:
            return {0, -scalar};
        case Direction::E:
            return {scalar, 0};
        case Direction::S:
            return {0, scalar};
        case Direction::W:
            return {-scalar, 0};
    }
}

inline Vec operator*(int scalar, Direction direction) {
    return direction * scalar;
}

#endif