#include "planar_topology.h"
PlanarTopology::PlanarTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
std::vector<Point> PlanarTopology::GetAllNeighbours(const Point& point) const {
    std::vector<Point> result;
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (auto [dx, dy] : dd_) {
        if (!IsInField(ix + dx, iy + dy)) {
            continue;
        }
        result.emplace_back(MovedPoint(point, dx, dy));
    }

    return result;
}