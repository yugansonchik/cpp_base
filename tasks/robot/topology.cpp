#include <queue>
#include "topology.h"
Field::Field(const std::vector<std::vector<bool>>& field) : field_(field) {
}
bool Field::IsAvailable(const Point& point) const {
    return !field_[point.y][point.x];
}
size_t Field::GetFieldWidth() const {
    return field_.empty() ? 0 : field_[0].size();
}
size_t Field::GetFieldHigh() const {
    return field_.size();
}
bool Field::IsInField(int x, int y) const {
    return x >= 0 && x < GetFieldWidth() && y >= 0 && y < GetFieldHigh();
}
std::vector<Point> Topology::GetNeighbours(const Point& point) const {
    std::vector<Point> result;
    for (const Point& next : GetAllNeighbours(point)) {
        if (IsAvailable(next)) {
            result.emplace_back(next);
        }
    }
    return result;
}
Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    std::unordered_map<Point, Distance> dist;

    std::queue<Point> q;
    q.push(from);
    dist[from] = 0;
    while (!q.empty()) {
        Point cur_point = q.front();
        q.pop();
        if (cur_point == to) {
            return dist[cur_point];
        }
        for (const Point& next : GetNeighbours(cur_point)) {
            if (dist.contains(next)) {
                continue;
            }
            dist[next] = dist[cur_point] + 1;
            q.push(next);
        }
    }
    return UNREACHABLE;
}
Topology::Topology(const std::vector<std::vector<bool>>& field) : Field(field) {
}
Point Topology::MovedPoint(const Point& point, int dx, int dy) const {
    return Point{static_cast<size_t>(static_cast<int>(point.x) + dx),
                 static_cast<size_t>(static_cast<int>(point.y) + dy)};
}
std::vector<Point> Topology::GetAllNeighbours(const Point& point) const {
    return std::vector<Point>();
}