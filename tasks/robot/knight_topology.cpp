#include "knight_topology.h"
KnightTopology::KnightTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
std::vector<Point> KnightTopology::GetAllNeighbours(const Point& point) const {
    std::vector<Point> result;
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (abs(dx * dy) != 2) {
                continue;
            }
            if (!IsInField(ix + dx, iy + dy)) {
                continue;
            }
            result.emplace_back(MovedPoint(point, dx, dy));
        }
    }
    return result;
}