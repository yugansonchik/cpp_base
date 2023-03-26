#pragma once

#include "point.h"

#include <vector>

class Field {
protected:
    explicit Field(const std::vector<std::vector<bool>>& field);

    bool IsAvailable(const Point& point) const;

    size_t GetFieldWidth() const;
    size_t GetFieldHigh() const;

    bool IsInField(int x, int y) const;

    std::vector<std::vector<bool>> field_;
};

class Topology : public Field {
public:
    using Distance = ssize_t;

    explicit Topology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetNeighbours(const Point& point) const;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    Point MovedPoint(const Point& point, int dx, int dy) const;

    virtual std::vector<Point> GetAllNeighbours(const Point& point) const;

    inline static const Distance UNREACHABLE = -1;
};