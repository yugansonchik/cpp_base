#pragma once

#include <cstddef>
#include <functional>

struct Point {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

template <>
struct std::hash<Point> {
    std::size_t operator()(const Point& point) const {
        return (point.x + point.y * 132487) % 23489371;
    }
};