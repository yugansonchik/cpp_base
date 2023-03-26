#include "world.h"
World::World(const Topology& topology, Point start, Point end) : start_(start), end_(end), topology_(topology) {
}
std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> result;
    for (const Point& next : topology_.GetNeighbours(current_point_)) {
        result[next] = topology_.MeasureDistance(next, end_);
    }
    return result;
}
const Point& World::GetStart() const {
    return start_;
}
const Point& World::GetEnd() const {
    return end_;
}
const Point& World::GetCurrentPosition() const {
    return current_point_;
}
void World::Move(const Point& to) {
    if (topology_.MeasureDistance(current_point_, to) != 1) {
        throw IllegalMoveException();
    }
    current_point_ = to;
}