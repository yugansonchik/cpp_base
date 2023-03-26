#pragma once

#include "topology.h"

class OverflowTopology : public Topology {
public:
    explicit OverflowTopology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetAllNeighbours(const Point& point) const override;

private:
    const int dd_[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
};