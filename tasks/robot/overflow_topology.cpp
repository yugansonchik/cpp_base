#include "overflow_topology.h"
OverflowTopology::OverflowTopology(const std::vector<std::vector<bool>>& field) : Topology(field) {
}
std::vector<Point> OverflowTopology::GetAllNeighbours(const Point& point) const {
    std::vector<Point> result;
    int ix = static_cast<int>(point.x);
    int iy = static_cast<int>(point.y);

    for (auto [dx, dy] : dd_) {
        Point cur_point(point);
        if (ix + dx < 0) {
            cur_point.x = GetFieldWidth() - 1u;
        } else if (ix + dx >= GetFieldWidth()) {
            cur_point.x = 0u;
        }

        if (iy + dy < 0) {
            cur_point.y = GetFieldHigh() - 1u;
        } else if (iy + dy >= GetFieldHigh()) {
            cur_point.y = 0u;
        }
        result.emplace_back(cur_point);
    }

    return result;
}