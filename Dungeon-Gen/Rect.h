#ifndef RECT_H
#define RECT_H

#include "Vec.h"
#include <algorithm>
#include <iterator>

class Rect {
public:
    int x;
    int y;
    int width;
    int height;

    Rect(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height),
          pos(x, y), size(width, height),
          left(std::min(x, x + width)),
          top(std::min(y, y + height)),
          right(std::max(x, x + width)),
          bottom(std::max(y, y + height)) {}

    bool containsPoint(const Vec& point) const {
        if (point.x < pos.x) return false;
        if (point.x >= pos.x + size.x) return false;
        if (point.y < pos.y) return false;
        if (point.y >= pos.y + size.y) return false;

        return true;
    }

    Rect inflate(int distance) const {
        return Rect(x - distance, y - distance, width + distance * 2, height + distance * 2);
    }

    int distanceTo(const Rect& other) const {
        int vertical = -1;
        if (top >= other.bottom) {
            vertical = top - other.bottom;
        } else if (bottom <= other.top) {
            vertical = other.top - bottom;
        }

        int horizontal = -1;
        if (left >= other.right) {
            horizontal = left - other.right;
        } else if (right <= other.left) {
            horizontal = other.left - right;
        }

        if ((vertical == -1) && (horizontal == -1)) return -1;
        if (vertical == -1) return horizontal;
        if (horizontal == -1) return vertical;
        return horizontal + vertical;
    }

    class RectIterator {
        public:
            RectIterator(const Rect& rect) : rect(rect), x(rect.x - 1), y(rect.y) {}

            bool operator!=(const RectIterator& other) const {
                return x != other.x || y != other.y;
            }

            Vec operator*() const {
                return Vec(x, y);
            }

            RectIterator& operator++() {
                x++;
                if (x >= rect.right) {
                    x = rect.x;
                    y++;
                }
                return *this;
            }
        private:
            const Rect& rect;
            int x;
            int y;
    };

    RectIterator begin() const {
        return RectIterator(*this);
    }

    RectIterator end() const {
        return RectIterator(Rect(x, bottom, width, 0));
    }

private:
    Vec pos;
    Vec size;  
    int left;
    int top;
    int right;
    int bottom;
};

#endif