#include "scorer.h"
#include <unordered_map>

bool CompareTime(const Event* event_1, const Event* event_2) {
    return event_1->time < event_2->time;
}

struct TaskStatus {
    bool merge_closed = true;
    bool check_success = false;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::unordered_map<std::string, std::unordered_map<std::string, TaskStatus>> students_tasks_status;
    std::vector<const Event*> pointers_on_events;

    ScoreTable score_table;

    for (const auto& event : events) {
        pointers_on_events.push_back(&event);
    }

    std::sort(pointers_on_events.begin(), pointers_on_events.end(), CompareTime);

    for (auto it : pointers_on_events) {
        if (it->time > score_time) {
            break;
        }
        switch (it->event_type) {
            case EventType::CheckFailed:
                students_tasks_status[it->student_name][it->task_name].check_success = false;
                break;
            case EventType::CheckSuccess:
                students_tasks_status[it->student_name][it->task_name].check_success = true;
                break;
            case EventType::MergeRequestOpen:
                students_tasks_status[it->student_name][it->task_name].merge_closed = false;
                break;
            case EventType::MergeRequestClosed:
                students_tasks_status[it->student_name][it->task_name].merge_closed = true;
                break;
        }
    }
    for (const auto& student : students_tasks_status) {
        for (const auto& task : student.second) {
            if (task.second.merge_closed && task.second.check_success) {
                score_table[student.first].insert(task.first);
            }
        }
    }
    return score_table;
}