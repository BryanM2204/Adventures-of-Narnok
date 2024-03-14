#ifndef VEC_H
#define VEC_H

class Vec {
public:
    int x;
    int y;

    Vec(int x, int y) : x(x), y(y) {}

    int getLengthSquared() const {
        return x * x + y * y;
    }

    Vec operator+(const Vec& other) const {
        return Vec(x + other.x, y + other.y);
    }

    Vec operator+(int other) const {
        return Vec(x + other, y + other);
    }

    Vec operator-(const Vec& other) const {
        return Vec(x - other.x, y - other.y);
    }

    Vec operator-(int other) const {
        return Vec(x - other, y - other);
    }

    bool lessThan(int other) const {
        return getLengthSquared() < other * other;
    }

    Vec operator*(int other) const {
        return Vec(x * other, y * other);
    }

    bool operator==(const Vec& other) const {
        return x == other.x && y == other.y;
    }

};

namespace std {
template <>
struct hash<Vec> {
    std::size_t operator()(const Vec& vec) const {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};
}

#endif
