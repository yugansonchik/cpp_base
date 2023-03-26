#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    explicit KnightTopology(const std::vector<std::vector<bool>>& field);

    std::vector<Point> GetAllNeighbours(const Point& point) const override;
};