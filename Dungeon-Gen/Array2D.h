#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <vector>
#include "Vec.h"

template <typename T>
class Array2D {
public:
    Array2D() : width(0), height(0) {}
    Array2D(int width, int height)
        : width(width), height(height), elements(width * height) {}

    T& operator[](const Vec& pos) {
        return elements[pos.y * width + pos.x];
    }

    const T& operator[](const Vec& pos) const {
        return elements[pos.y * width + pos.x];
    }

    T& get(const Vec& pos) {
        return elements[pos.y * width + pos.x];
    }

    const T& get(const Vec& pos) const {
        return elements[pos.y * width + pos.x];
    }

    void set(const Vec& pos, const T& value) {
        elements[pos.y * width + pos.x] = value;
    }

    class Array2DIterator {
    public:
        Array2DIterator(Array2D<T>& array, int index)
            : array(array), index(index) {}

        bool operator!=(const Array2DIterator& other) const {
            return index != other.index;
        }

        T& operator*() {
            return array.elements[index];
        }

        Array2DIterator& operator++() {
            ++index;
            return *this;
        }
    private:
        Array2D<T>& array;
        int index;
    };

    Array2DIterator begin() {
        return Array2DIterator(*this, 0);
    }

    Array2DIterator end() {
        return Array2DIterator(*this, width * height);
    }

public:
    int width;
    int height;

private:
    std::vector<T> elements;
};

#endif
