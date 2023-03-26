#include <queue>
#include "robot.h"

namespace robot {

Path FindPath(World& world) {
    Path result;
    Point cur_point = world.GetStart();
    Point end_point = world.GetEnd();

    result.emplace_back(cur_point);

    while (cur_point != end_point) {
        Point best_next = cur_point;
        Topology::Distance min_dist(0);
        for (const auto& [next, dist_to_end] : world.Lookup()) {
            if (dist_to_end == Topology::UNREACHABLE) {
                continue;
            }
            if (best_next == cur_point || dist_to_end < min_dist) {
                best_next = next;
                min_dist = dist_to_end;
            }
        }
        if (cur_point == best_next) {
            result.clear();
            break;
        }
        cur_point = best_next;
        world.Move(cur_point);
        result.emplace_back(cur_point);
    }
    return result;
}
}  // namespace robot